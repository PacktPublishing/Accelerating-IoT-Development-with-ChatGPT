*Hi, ChatGPT,*

***Role:*** 

*You act as a senior software developer with expertise in embedded development, specifically with IoT projects using the ESP32, Arduino-compatible sensors, and AWS Cloud.*

***Task:*** 

*Your task is to mentor a high school student (like me) who has a basic understanding of Python and is new to C++. I need you to develop a comprehensive code snippet that fulfills the following objective, detailed requirements, implementation guidance, and output format.*

***Objective:*** 

*Create an educational code snippet that runs on the Platformio IDE, following the requirements below.*

***Requirements:***

1. ***Pin Wire Connections:*** 
    1. *Connect the DHT11 data pin to IO2 on the ESP32-C3.*
    2. *Connect the Piezo Buzzer signal pin to IO11 on the ESP32-C3.*
    3. *Connect the RGB LED to IO8 for Red, IO4 for Blue, and IO9 for Green on the ESP32-C3.*
    4. *Use IO13 to control the ESP32-C3’s built-in LED D5, designated as the System LED.*
2. ***Data Retrieve Operation:** Periodically read the DHT11 sensor's temperature and humidity data, and print it out locally in both Celsius and Fahrenheit.*
3. ***Normal Condition:** The retrieved data falls within the pre-defined normal range.*
4. ***Abnormal Condition:** The retrieved data falls out of the pre-defined normal range.*
5. ***Error Condition:** Data retrieval fails, and the system will then attempt to read the data three times. If all three attempts fail, the system will initiate a reboot.*
6. ***Visual and Sound Indication:*** 
    1. ***Normal Condition:** RGB LED turns solid on, and mute the buzzer.*
    2. ***Abnormal Condition:** If the data exceeds the normal range, the RGB LED will blink red, and the buzzer will beep in sync; If the data falls below the normal range, the RGB LED will blink blue, and the buzzer will beep in sync.*
    3. ***Error Condition:** Turns the system LED on solidly, and triggers the buzzer to beep continuously.*

***Must to Apply:***

- *Adopt C++ programming best practices.*
- *Use “constexpr” to declare hardware related variables.*
- *Uses the **`millis()`** function to manage timing without blocking other code execution*
- *Favor functions over classes.*
- *Implement PWM control for both the System LED and buzzer using ledcSetup and ledcAttachPin.*
- *Avoid using magic numbers when defining constant variables.*
- *Use a non-blocking approach to blink the LED independently.*
- *Include necessary dependency libraries.*
- *Provide line-by-line comments for clarity.*

***Format:***

// **********************************
// Created by: ESP32 Coding Assistant
// Creation Date: [Current Date]
// **********************************
// Code Explanation
// **********************************
// Code Purpose:
// ......
// Requirement Summary:
// ......
// Hardware Connection:
// ......
// New Created Function/Class:
// ......
// Security Considerations:
// ......
// Testing and Validation Approach:
// ......
// **********************************
// Libraries Import
// **********************************
// ......
// **********************************
// Constants Declaration
// **********************************
// ......
// **********************************
// Variables Declaration
// **********************************
// ......
// **********************************
// Functions or Class Declaration
// **********************************
// ......
// **********************************
// Setup Function
// **********************************
// ......
// **********************************
// Main loop
// **********************************
// ......

***Platformio.ini File:***

- *Create a new file that incorporates the required library dependencies and environment settings.*
- *Ensure the following information is included.*

```
[env:esp32-c3-devkitc-02]
platform = espressif32
board = esp32-c3-devkitc-02
framework = arduino
monitor_filters = esp32_exception_decoder, colorize
monitor_speed = 115200
board_build.flash_mode = dio
build_flags = 
	-DARDUINO_USB_MODE=1
	-DARDUINO_USB_CDC_ON_BOOT=1
	-w
```
