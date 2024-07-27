// **********************************
// Project 5: Distance Measurement
// Creation Date: 2024-05-02
// **********************************
// Code Explanation
// **********************************
// Code Purpose:
// This code demonstrates how to use the HC-SR04 ultrasonic sensor with an ESP32 C3 to measure distance.
// It uses an RGB LED and a Piezo Buzzer to provide feedback based on the measured distance.
// Hardware Connection:
// - Ultrasonic sensor trig pin -> GPIO0, echo pin -> GPIO1
// - RGB LED Red -> GPIO2, Green -> GPIO3, Blue -> GPIO10
// - Piezo Buzzer -> GPIO11
// **********************************
// Libraries Import
// **********************************
#include <Arduino.h>

// **********************************
// Constants and Variables Declaration
// **********************************
constexpr int TRIG_PIN = 0; // Ultrasonic sensor trig pin
constexpr int ECHO_PIN = 1; // Ultrasonic sensor echo pin

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


// Distance thresholds
constexpr float CLOSE_RANGE = 10.0;
constexpr float MID_RANGE = 30.0;

// Speed of sound constant (cm/µs) / 2
constexpr float SOUND_SPEED_CM_PER_US = 0.017;

int lastRedState = 0; 
int lastGreenState = 0;
int lastBlueState = 0;

bool isBuzzerOn = false; // Track whether the buzzer should be considered ON or OFF

// **********************************
// Funcion Declaration
// **********************************
void readUltrasoundSensor(float &distance); // Function to measure distance using HC-SR04
void updateIndicatorStatus(float distance); // Function to update LED indicators based on the distance
void beepBuzzerAlert(bool active);          // Function to control buzzer activity
void setLEDState(bool red, bool green, bool blue);

// **********************************
// Setup Function
// **********************************
void setup() {
    Serial.begin(115200);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

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
void loop() {
    if (millis() - lastCheckTime >= SENSOR_READ_INTERVAL) {
        lastCheckTime = millis();
        float currentDistance = 0.0;
        readUltrasoundSensor(currentDistance);
        updateIndicatorStatus(currentDistance);
    }
}

// **********************************
// Function Definitions
// **********************************

void readUltrasoundSensor(float &distance) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if (duration > 0) {
        distance = duration * SOUND_SPEED_CM_PER_US;
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    } else {
        Serial.println("Error: No echo received");
    }
}

void updateIndicatorStatus(float distance) {
    bool currentRedState = (distance < CLOSE_RANGE);
    bool currentGreenState = (distance > MID_RANGE);
    bool currentBlueState = (distance >= CLOSE_RANGE && distance <= MID_RANGE);

    setLEDState(currentRedState, currentGreenState, currentBlueState);
    beepBuzzerAlert(distance < MID_RANGE);
}
void beepBuzzerAlert(bool active) {
    if (active) {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_VOLUME_HALF);
        isBuzzerOn = true;
    } else {
        ledcWrite(PWM_BUZZER_CHANNEL, PWM_BUZZER_OFF);
        isBuzzerOn = false;
    }
}

void setLEDState(bool red, bool green, bool blue) {
    ledcWrite(PWM_LED_RED_CHANNEL, red ? 255 : 0);
    ledcWrite(PWM_LED_GREEN_CHANNEL, green ? 255 : 0);
    ledcWrite(PWM_LED_BLUE_CHANNEL, blue ? 255 : 0);

    lastRedState = red;
    lastGreenState = green;
    lastBlueState = blue;
}
