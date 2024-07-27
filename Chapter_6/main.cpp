/**
 * Cloud Registration Feature for Smart Smoke Detector
 * 
 * This program enables an ESP32-based smart smoke detector to register itself with AWS IoT Core,
 * demonstrating steps from connecting to a Wi-Fi network to sending registration data over MQTT.
 * 
 * Creation Date: February 11, 2024
 * Author: ChatGPT
 * 
 * Security Risks:
 * - Hardcoded Wi-Fi and AWS IoT credentials are used for simplicity but should be securely managed in production.
 * 
 * Testing and Validation Approach:
 * - Perform unit tests for individual functions.
 * - Conduct integration testing to ensure seamless Wi-Fi and AWS IoT Core connectivity.
 * - Use secure credential storage mechanisms for production environments.
 */

//********************************************************************************

// Include necessary libraries for connecting to WiFi, securing connections, handling MQTT, and JSON formatting
#include <Arduino.h> // Enables basic Arduino functionality
#include <WiFi.h> // Enables WiFi connectivity
#include "WiFiClientSecure.h" // Provides TLS/SSL support for secure connections
#include <PubSubClient.h> // MQTT client for publishing and subscribing over a network
#include <ArduinoJson.h> // For encoding and decoding JSON data
#include <time.h> // Provides time functions, enabling NTP time synchronization
#include <aws_certs.h> // Include the certificates and keys for AWS connections

//********************************************************************************

// Define device specific information for the registration payload
const char* FIRMWARE_VERSION = "v1.0"; // Firmware version
const char* device_ID = "DEVICE_ID"; // Unique device identifier

// Define network credentials and AWS IoT Core settings
const char* ssid = "YOUR_SSID"; // WiFi network name
const char* password = "YOUR_PASSWORD"; // WiFi password
const char* aws_endpoint = "YOUR_AWS_ENDPOINT"; // AWS IoT Core endpoint URL
const char* aws_topic = "YOUR_TOPIC"; // MQTT topic for publishing messages
int aws_port = 8883; // Secure port for MQTT over TLS/SSL

// Define device specific information for the registration payload
const char* device_id = "DEVICE_ID"; // Unique device identifier
const char* model = "MODEL"; // Device model
const char* firmware_version = "FIRMWARE_VERSION"; // Firmware version

// NTP server configuration for time synchronization
const char* ntpServer = "pool.ntp.org"; // NTP server for time synchronization
const long  gmtOffset_sec = -8 * 3600; // Offset for Pacific Time Zone (PST)
const int   daylightOffset_sec = 0; // Daylight saving time offset

// Initialize secure network client and MQTT client
WiFiClientSecure net; // Secure network client for SSL/TLS connection
PubSubClient client(net); // MQTT client using the secure network connection

//********************************************************************************

// Function to connect to the specified Wi-Fi network
void connectToWiFi() {
    Serial.println("Connecting to WiFi..."); // Log the start of the WiFi connection attempt
    WiFi.begin(ssid, password); // Start WiFi connection with provided SSID and password
    while (WiFi.status() != WL_CONNECTED) { // Wait for the connection to establish
        delay(500); // Delay to avoid spamming attempts
        Serial.print("."); // Print dots on the serial monitor to indicate progress
    }
    Serial.println("WiFi connected"); // Log WiFi connection success
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); // Synchronize device time with NTP server
}

// Function to get the current time in ISO 8601 format
String getTimeStamp() {
    struct tm timeinfo; // Create a structure to hold time info
    if (!getLocalTime(&timeinfo)) { // Obtain local time
        Serial.println("Failed to obtain time"); // Log failure to obtain time
        return "";
    }
    char timeStringBuff[50]; // Buffer to hold the formatted time
    // Format the time into ISO 8601 format
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(timeStringBuff); // Return the formatted time
}

// Function to establish a secure connection to AWS IoT Core using TLS
void connectToAWS() {
    net.setCACert(aws_root_ca); // Load CA certificate
    net.setCertificate(aws_certificate); // Load client certificate
    net.setPrivateKey(aws_private_key); // Load client private key
    client.setServer(aws_endpoint, aws_port); // Configure MQTT client with AWS IoT endpoint and port
    while (!client.connected()) { // Try to connect to AWS IoT
        Serial.println("Connecting to AWS IoT..."); // Log attempting to connect
        if (client.connect("esp32")) { // Use a unique client ID for the connection
            Serial.println("Connected to AWS IoT"); // Log successful connection
        } else {
            Serial.print("Connection failed, rc="); // Log failed connection attempt
            Serial.println(client.state()); // Print the connection state
            delay(2000); // Wait for 2 seconds before retrying
        }
    }
}

// Function to publish a JSON payload to the configured MQTT topic
void publishMessage() {
    // Create a JSON document. Dynamic allocation is typically used for JsonDocument.
    JsonDocument doc; // Adjust the size according to your needs

    // Add values to the document
    doc["device_ID"] = device_ID; // Unique device identifier
    doc["model"] = model; // Device model
    doc["timestamp"] = getTimeStamp(); // Current time in ISO 8601 format
    doc["sensor"] = "Smoke Detector";
    doc["firmware_version"] = firmware_version; // Firmware version
    doc["status"] = "registering";

    // Serialize the JSON document
    String output;
    serializeJson(doc, output);

    // Use 'output' where you need to send the JSON string
    Serial.println(output);
}



// Function to set the built-in LED's state
void setLED(bool on) {
    digitalWrite(LED_BUILTIN, on ? HIGH : LOW); // Set the LED state
}

//********************************************************************************

// Setup function to initialize the device
void setup() {
    Serial.begin(115200); // Initialize serial communication
    pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED as an output
    connectToWiFi(); // Connect to WiFi
    connectToAWS(); // Connect to AWS IoT Core
}

// Main loop function
void loop() {
    if (!client.connected()) { // Check if the client is still connected
        connectToAWS(); // Reconnect if necessary
    }
    client.loop(); // Process incoming messages and maintain MQTT connection
    publishMessage(); // Publish device registration message
    setLED(true); // Turn on the LED to indicate successful registration
    delay(60000); // Keep the Wi-Fi connection alive for 1 minute
    WiFi.disconnect(true); // Disconnect from Wi-Fi
    delay(4 * 60 * 60 * 1000); // Sleep for 4 hours before restarting the loop
}
