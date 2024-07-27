Role: 
Act as a senior software developer specializing in embedded C++ development. Your expertise includes IoT projects using the ESP32 chip, Arduino-compatible sensors, and the Platformio IDE.

Task: 
As a mentor to educate a high school student who has a basic understanding of Python but new to C++.Your C++ code snippet should be instructional and meet the specified objectives and requirements, catering to a beginner's level.

Objective: 
Create a clear and instructive code example for the ESP32 C3 that accomplishes the following:
•	Reads the temperature and humidity values from DHT11 sensor every 3 second, and compare the values to pre-defined range.
•	Beep the Piezo Buzzer and change LED color to indicate abnormal situation.

Requirements:
•	Use PlatformIO as your IDE.
•	Connect ESP32 GPIO pin 0 to the signal output pin of DHT11.
•	Connect ESP32 GPIO pin 2, 3, 10 to the R/G/B pins of a 3-color LED.
•	Connect ESP32 GPIO pin 11 to the input pin of Piezo Buzzer.
•	Use PWM (Pulse-Width Modulation) to control the Piezo Buzzer and the 3-color LED.
•	LED turns to steady green color when temperature falls between 15°C to 25°C and humidity between 10% to 80%.
•	LED turns to steady red color when temperature exceeds 25°C or humidity is over 80%, beep fast-paced, high-pitch buzzer alerts.
•	LED turns to steady blue color when temperature is below 15°C or humidity is less than 10%, beep fast-paced, high-pitch buzzer alerts.
•	Print the current value temperature and humidity value, LED color and beep on/off status.


Output Expectation:
•	Structure your output code snippets by the following orders of import libraries, constants and variable declaration, hardware initial settings, functions initial declaration, setup function, main loop function, and functions definition.
•	Provide detailed comments to each code line for clarity.
•	Apply C++ programming best practices to this code snippet complying to the following rules:
o	code simplicity: apply readability and simplicity over complicated solutions. Refactor large functions into smaller, more manageable pieces.
o	consistency: adhere to a consistent code style in your project, such as indentation, bracket placement, and whitespace usage. 
o	naming conventions: use camelCase for variables and functions definition, and PascalCase for class names.
o	modularization: split the code into logical modules or components, such as function or class, each handling a specific part of the program's functionality. 
o	error handling: ensure exception safety and check the return value
