// **********************************
// Project 1
// Creation Date: 2024-05-01
// **********************************
// Code Explanation
// **********************************
// Code Purpose:
// This code is designed to monitor temperature and humidity using a DHT11 sensor.
// It provides visual and audible alerts using an RGB LED and a Piezo Buzzer based on sensor readings.
// Requirement Summary:
// - Periodically read from DHT11 sensor every 3 seconds.
// - Use LEDs and Piezo Buzzer for indication based on predefined thresholds.
// Hardware Connection:
// - DHT11 data pin -> GPIO0
// - RGB LED Red -> GPIO2, Green -> GPIO3, Blue -> GPIO10
// - Piezo Buzzer -> GPIO11
// **********************************
// Libraries Import
// **********************************
#include <Arduino.h>
#include "DHT.h"

// **********************************
// Constants and Variables Declaration
// **********************************
constexpr int DHT_PIN = 0;               // Pin connected to the DHT11 data pin
constexpr int DHT_TYPE = DHT11;          // Specify DHT11 type
DHT dht(DHT_PIN, DHT_TYPE);              // Initialize DHT sensor
constexpr float TEMP_NORMAL_LOW = 15.0;  // Lower boundary for normal temperature
constexpr float TEMP_NORMAL_HIGH = 30.0; // Upper boundary for normal temperature
constexpr float HUM_NORMAL_LOW = 10.0;   // Lower boundary for normal humidity
constexpr float HUM_NORMAL_HIGH = 80.0;  // Upper boundary for normal humidity

// * LED PINs and PWM settings
constexpr int LED_RED_PIN = 2;   // Red LED pin
constexpr int LED_GREEN_PIN = 3; // Green LED pin
constexpr int LED_BLUE_PIN = 10; // Blue LED pin

constexpr int PWM_LED_RED_CHANNEL = 1;   // PWM channel for Red LED
constexpr int PWM_LED_GREEN_CHANNEL = 2; // PWM channel for Green LED
constexpr int PWM_LED_BLUE_CHANNEL = 3;  // PWM channel for Blue LED

constexpr int PWM_LED_FREQUENCY = 5000; // Suitable frequency for LEDs
constexpr int PWM_LED_RESOLUTION = 8;   // 8-bit resolution (0-255)

// * Buzzer Pins and PWM settings
constexpr int BUZZER_PIN = 11;              // Pin connected to the Piezo Buzzer
constexpr int PWM_BUZZER_CHANNEL = 0;       // PWM channel for Piezo Buzzer
constexpr int PWM_BUZZER_FREQUENCY = 2000;  // Frequency for Buzzer PWM
constexpr int PWM_BUZZER_RESOLUTION = 10;   // Resolution for Buzzer PWM (10-bit = 0-1023)
constexpr int PWM_BUZZER_VOLUME_HALF = 512; // Half volume for the buzzer
constexpr int PWM_BUZZER_OFF = 0;           // Turn off the buzzer

constexpr unsigned long SENSOR_READ_INTERVAL = 1000; // Read interval in milliseconds
unsigned long lastCheckTime = 0;                     // Last time the sensor was checked

int currentRedState = 0; // 0 means off, values > 0 mean on (at various intensities)
int currentGreenState = 0;
int currentBlueState = 0;

bool isBuzzerOn = false; // Track whether the buzzer should be considered ON or OFF

void readDHTSensor(float &humidity, float &temperatureC, float &temperatureF);
void updateIndicatorStatus(float humidity, float temperatureC);
void beepBuzzerAlert(bool activate);
void printSystemStatus(float temperatureC, float temperatureF, float humidity);

// **********************************
// Setup Function
// **********************************
void setup()
{
    Serial.begin(115200);
    dht.begin();

    ledcSetup(PWM_LED_RED_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
    ledcAttachPin(LED_RED_PIN, PWM_LED_RED_CHANNEL);

    ledcSetup(PWM_LED_GREEN_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
    ledcAttachPin(LED_GREEN_PIN, PWM_LED_GREEN_CHANNEL);

    ledcSetup(PWM_LED_BLUE_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);
    ledcAttachPin(LED_BLUE_PIN, PWM_LED_BLUE_CHANNEL);

    ledcSetup(PWM_BUZZER_CHANNEL, PWM_BUZZER_FREQUENCY, PWM_BUZZER_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, PWM_BUZZER_CHANNEL);
}

// **********************************
// Main Loop
// **********************************
void loop()
{
    if (millis() - lastCheckTime >= SENSOR_READ_INTERVAL)
    {
        lastCheckTime = millis();
        float humidity = 0.0;
        float temperatureC = 0.0;
        float temperatureF = 0.0;

        readDHTSensor(humidity, temperatureC, temperatureF);
        updateIndicatorStatus(humidity, temperatureC);
        printSystemStatus(temperatureC, temperatureF, humidity);
    }
}

// **********************************
// Function Definitions
// **********************************

void readDHTSensor(float &humidity, float &temperatureC, float &temperatureF)
{
    humidity = dht.readHumidity();
    temperatureC = dht.readTemperature();
    temperatureF = dht.readTemperature(true);

    if (isnan(humidity) || isnan(temperatureC))
    {
        Serial.println("Failed to read from DHT sensor!");
    }
}

void updateIndicatorStatus(float humidity, float temperatureC)
{
    bool tempHighAlert = temperatureC > TEMP_NORMAL_HIGH;
    bool humHighAlert = humidity > HUM_NORMAL_HIGH;
    bool tempLowAlert = temperatureC < TEMP_NORMAL_LOW;
    bool humLowAlert = humidity < HUM_NORMAL_LOW;

    if (tempHighAlert || humHighAlert)
    {
        // Set Red LED on if temperature or humidity is too high
        ledcWrite(PWM_LED_RED_CHANNEL, 255);
        ledcWrite(PWM_LED_GREEN_CHANNEL, 0);
        ledcWrite(PWM_LED_BLUE_CHANNEL, 0);
        currentRedState = 255;
        currentGreenState = 0;
        currentBlueState = 0;
    }
    else if (tempLowAlert || humLowAlert)
    {
        // Set Blue LED on if temperature or humidity is too low
        ledcWrite(PWM_LED_RED_CHANNEL, 0);
        ledcWrite(PWM_LED_GREEN_CHANNEL, 0);
        ledcWrite(PWM_LED_BLUE_CHANNEL, 255);
        currentRedState = 0;
        currentGreenState = 0;
        currentBlueState = 255;
    }
    else
    {
        // Set Green LED on if conditions are normal
        ledcWrite(PWM_LED_RED_CHANNEL, 0);
        ledcWrite(PWM_LED_GREEN_CHANNEL, 255);
        ledcWrite(PWM_LED_BLUE_CHANNEL, 0);
        currentRedState = 0;
        currentGreenState = 255;
        currentBlueState = 0;
    }

    // Alert with the buzzer if any alert condition is met
    beepBuzzerAlert(tempHighAlert || humHighAlert || tempLowAlert || humLowAlert);
}

void beepBuzzerAlert(bool activate)
{
    if (activate)
    {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_VOLUME_HALF); // Set to half volume
        isBuzzerOn = true;                                     // Correctly updating the status when the buzzer is active
    }
    else
    {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_OFF); // Turn off the buzzer
        isBuzzerOn = false;                            // Correctly updating the status when the buzzer is not active
    }
}

void printSystemStatus(float temperatureC, float temperatureF, float humidity)
{
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.print("C / ");
    Serial.print(temperatureF);
    Serial.print("F, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Adding current status of the LEDs
    Serial.print("Red LED State: ");
    Serial.println(currentRedState > 0 ? "ON" : "OFF");
    Serial.print("Green LED State: ");
    Serial.println(currentGreenState > 0 ? "ON" : "OFF");
    Serial.print("Blue LED State: ");
    Serial.println(currentBlueState > 0 ? "ON" : "OFF");

    // Adding current status of the Buzzer
    Serial.print("Buzzer State: ");
    Serial.println(isBuzzerOn ? "ON" : "OFF");
}
