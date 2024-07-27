// **********************************
// Project 2: Flame Detection System
// Creation Date: 2024-05-02
// **********************************
// Code Explanation
// **********************************
// Code Purpose:
// This code is designed to detect flame presence using a KY-026 flame sensor connected to an ESP32 C3.
// It utilizes an RGB LED and a Piezo Buzzer to provide visual and auditory alerts based on flame detection.
// Hardware Connection:
// - Flame sensor D0 pin -> GPIO0
// - RGB LED Red -> GPIO2, Green -> GPIO3, Blue -> GPIO10
// - Piezo Buzzer -> GPIO11
// **********************************
// Libraries Import
// **********************************
#include <Arduino.h>

// **********************************
// Constants and Variables Declaration
// **********************************
constexpr int FLAME_PIN = 0; // Pin connected to the Flame sensor

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

constexpr unsigned long SENSOR_READ_INTERVAL = 3000; // Read interval in milliseconds
unsigned long lastCheckTime = 0;                     // Last time the sensor was checked

int currentRedState = 0; // 0 means off, values > 0 mean on (at various intensities)
int currentGreenState = 0;
int currentBlueState = 0;

bool isBuzzerOn = false; // Track whether the buzzer should be considered ON or OFF

// **********************************
// Function Declaration
// **********************************
bool isFlameOn();                         // Function to read the flame sensor
void updateIndicatorStatus(bool flameDetected); // Function to control outputs based on sensor readings
void beepBuzzerAlert(bool flameDetected);            // Function to activate buzzer
void printSystemStatus(bool flameDetected); // Function to print system status

// **********************************
// Setup Function
// **********************************

void setup()
{
    Serial.begin(115200);
    pinMode(FLAME_PIN, INPUT);

    // * LED PWM setup
    ledcSetup(PWM_LED_RED_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);   // Setup PWM channel for Red LED
    ledcAttachPin(LED_RED_PIN, PWM_LED_RED_CHANNEL);                         // Attach Red LED to PWM channel
    ledcSetup(PWM_LED_GREEN_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION); // Setup PWM channel for Green LED
    ledcAttachPin(LED_GREEN_PIN, PWM_LED_GREEN_CHANNEL);                     // Attach Green LED to PWM channel
    ledcSetup(PWM_LED_BLUE_CHANNEL, PWM_LED_FREQUENCY, PWM_LED_RESOLUTION);  // Setup PWM channel for Blue LED
    ledcAttachPin(LED_BLUE_PIN, PWM_LED_BLUE_CHANNEL);                       // Attach Blue LED to PWM channel

    // * Buzzer PWM setup
    ledcSetup(PWM_BUZZER_CHANNEL, PWM_BUZZER_FREQUENCY, PWM_BUZZER_RESOLUTION); // Setup PWM channel for Buzzer
    ledcAttachPin(BUZZER_PIN, PWM_BUZZER_CHANNEL);                              // Attach Buzzer to PWM channel

    // * Initial LED state setup based on initial sensor read
    bool initialFlameDetected = isFlameOn(); // Read the flame sensor
    updateIndicatorStatus(initialFlameDetected);  // Update the LED status based on sensor reading
    beepBuzzerAlert(initialFlameDetected);        // Activate buzzer based on sensor reading
}

// **********************************
// Main Loop
// **********************************
void loop()
{
    if (millis() - lastCheckTime >= SENSOR_READ_INTERVAL)
    {
        lastCheckTime = millis();
        bool flameDetected = isFlameOn(); // Read the flame sensor
        updateIndicatorStatus(flameDetected);   // Update the LED status based on sensor reading
        beepBuzzerAlert(flameDetected);         // Activate buzzer if flame is detected
        printSystemStatus(flameDetected);       // Print the system status
    }
}

// **********************************
// Function Definitions
// **********************************
bool isFlameOn() // Function to read the flame sensor
{
    int flameState = digitalRead(FLAME_PIN); // Read the sensor value
    return (flameState == HIGH); // Return true if the sensor DO status is high
}

void updateIndicatorStatus(bool flameDetected) // Function to control outputs based on sensor readings
{
    if (flameDetected) // If flame is detected
    {
        ledcWrite(PWM_LED_RED_CHANNEL, 255); // Set to full brightness
        currentRedState = 255;               // Update the red state
        ledcWrite(PWM_LED_GREEN_CHANNEL, 0); // Set to off
        currentGreenState = 0;               // Update the green state
        ledcWrite(PWM_LED_BLUE_CHANNEL, 0);  // Set to off
        currentBlueState = 0;                // Update the blue state
    }
    else
    {
        ledcWrite(PWM_LED_RED_CHANNEL, 0);     // Set to off
        currentRedState = 0;                   // Update the red state
        ledcWrite(PWM_LED_GREEN_CHANNEL, 255); // Set to full brightness
        currentGreenState = 255;               // Update the green state
        ledcWrite(PWM_LED_BLUE_CHANNEL, 0);    // Set to off
        currentBlueState = 0;                  // Update the blue state
    }
}

void beepBuzzerAlert(bool flameDetected) // Function to activate or deactivate the buzzer based on flame detection
{
    if (flameDetected) // If true, activate the buzzer
    {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_VOLUME_HALF); // Set to half volume
        isBuzzerOn = true;                                     // Update the buzzer state
    }
    else // If false, deactivate the buzzer
    {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_OFF); // Turn off the buzzer
        isBuzzerOn = false;                            // Update the buzzer state
    }
}

void printSystemStatus(bool flameDetected) // Function to print system status
{
    Serial.print("PIN Value - "); 
    Serial.println(digitalRead(FLAME_PIN));
    Serial.print("Flame Detected: ");
    Serial.println(flameDetected ? "YES" : "NO");
    Serial.print("Red LED State: ");
    Serial.println(currentRedState > 0 ? "ON" : "OFF");
    Serial.print("Green LED State: ");
    Serial.println(currentGreenState > 0 ? "ON" : "OFF");
    Serial.print("Blue LED State: ");
    Serial.println(currentBlueState > 0 ? "ON" : "OFF");
    Serial.print("Buzzer State: ");
    Serial.println(isBuzzerOn ? "ON" : "OFF");
}
