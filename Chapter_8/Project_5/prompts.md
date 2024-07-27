Role: 
Act as a senior software developer specializing in embedded C++ development. Your expertise includes IoT projects using the ESP32 chip, Arduino-compatible sensors, and the Platformio IDE.

Task: 
As a mentor to educate a high school student who has a basic understanding of Python but new to C++.Your C++ code snippet should be instructional and meet the specified objectives and requirements, catering to a beginner's level.

Objective: 
Create a clear and instructive code example for the ESP32 C3 that accomplishes the following:
•	Reads the output values from HC-SR04 every 100 millisecond.
•	Beep the Piezo Buzzer and change LED color to indicate abnormal distance range.

Requirements:
•	Use PlatformIO as your IDE.
•	Connect ESP32 GPIO pin 0 to the Trig pin and pin 1 to the Echo pin of HC-SR04.
•	Connect ESP32 GPIO pin 2, 3, 10 to the R/G/B pins of a 3-color LED.
•	Connect ESP32 GPIO pin 11 to the input pin of Piezo Buzzer.
•	Use PWM (Pulse-Width Modulation) to control the Piezo Buzzer and the 3-color LED.
•	If the distance value is within 10 cm, beep the Piezo Buzzer and change the LED color to red.
•	If the distance value is between 10cm to 30 cm, beep the Piezo Buzzer and change the LED color to blue.
•	If the distance value is beyond 30 cm, mute the Piezo Buzzer and maintain the LED color to green.
•	Print the current value, beep on/off status, and LED color.


Output Expectation:
•	Structure your output code snippets by the following orders of import libraries, constants and variable declaration, hardware initial settings, functions initial declaration, setup function, main loop function, and functions definition.
•	Provide detailed comments to each code line for clarity.
•	Apply C++ programming best practices to this code snippet complying to the following rules:
o	code simplicity: apply readability and simplicity over complicated solutions. Refactor large functions into smaller, more manageable pieces.
o	consistency: adhere to a consistent code style in your project, such as indentation, bracket placement, and whitespace usage. 
o	naming conventions: use camelCase for variables and functions definition, and PascalCase for class names.
o	modularization: split the code into logical modules or components, such as function or class, each handling a specific part of the program's functionality. 
o	error handling: ensure exception safety and check the return value
