Speden Sepelit
Speden Sepelit is an Arduino-based LED project that simulates various lighting patterns. The project controls a set of 4 LEDs using digital pins 2 to 5 and demonstrates sequential, random, and binary LED lighting effects. This project serves as a fun way to learn how to control LEDs via microcontrollers like Arduino.

Table of Contents
Project Description
Features
Hardware Requirements
Software Requirements
Circuit Diagram
Installation
Usage
Contributing
License
Project Description
The Speden Sepelit project simulates multiple LED lighting effects using an Arduino. It demonstrates various lighting patterns such as:

Sequential LED blinking
Random LED selection
Binary counting representation with LEDs
Adjustable lighting speed with decreasing delays
The code is written in C++ for the Arduino platform and uses 4 digital pins (2 to 5) to control LEDs.

Features
Sequential LED Blinking: LEDs light up in a predefined sequence.
Random LED Lighting: LEDs are chosen randomly to light up, adding unpredictability to the pattern.
Binary Number Display: The LEDs represent numbers from 0 to 15 in binary.
Adjustable Delay: Lighting speed can decrease over time for dynamic visual effects.
Hardware Requirements
To recreate this project, you'll need the following hardware components:

Arduino (Uno, Nano, or any compatible board)
4 LEDs (any color)
4 Resistors (220Ω or 330Ω recommended)
Breadboard
Jumper wires
USB Cable to connect the Arduino to your computer
Software Requirements
Arduino IDE: Download and install the Arduino IDE from Arduino's official website.
Speden Sepelit Code: Clone or download the project from the repository.
Circuit Diagram
Here’s how to wire your components:

Pin on Arduino	Component
Pin 2	LED 1
Pin 3	LED 2
Pin 4	LED 3
Pin 5	LED 4
GND	Common Ground (through resistors to the LEDs)
Each LED should have a current-limiting resistor (220Ω or 330Ω) connected in series to ground (GND).

Example Diagram:
rust
Copy code
Arduino Pin 2 ----> (long leg) LED 1 (short leg) ----> Resistor ----> GND
Arduino Pin 3 ----> (long leg) LED 2 (short leg) ----> Resistor ----> GND
Arduino Pin 4 ----> (long leg) LED 3 (short leg) ----> Resistor ----> GND
Arduino Pin 5 ----> (long leg) LED 4 (short leg) ----> Resistor ----> GND
Installation
1. Clone the Repository
bash
Copy code
git clone https://github.com/your-repository/speden-sepelit.git
cd speden-sepelit
2. Open in Arduino IDE
Open the Arduino IDE.
Load the project .ino file or the project folder in the IDE.
3. Upload the Code
Select your Arduino board from Tools > Board.
Select the appropriate port from Tools > Port.
Click Upload to compile and upload the code to your Arduino.
Usage
After uploading the code, the LEDs will start demonstrating various lighting patterns:

Sequential Lighting: LEDs light up in sequence.
Random LED Lighting: LEDs light up randomly with adjustable speeds.
Binary Display: LEDs represent binary numbers (0-15).
Speed Control: The speed of the lighting sequence increases with each cycle.
Functions
initializeLeds(): Initializes the LED pins as output.
setLed(byte ledNumber): Lights up a specific LED (0-3).
clearAllLeds(): Turns off all LEDs.
setAllLeds(): Turns on all LEDs.
show1(): Displays binary numbers (0-15) on the LEDs.
show2(int rounds): Lights up LEDs in random or sequential order with decreasing delay between each light-up.
Customization
You can modify the lighting patterns, the number of LEDs, or even the delay timing by adjusting the code in the show1() and show2() functions in leds.cpp. The random() function can be used to make the LED lighting completely unpredictable.

Contributing
If you'd like to contribute to the project:

Fork the repository.
Create a new branch for your feature (git checkout -b feature/my-feature).
Commit your changes (git commit -am 'Add some feature').
Push to the branch (git push origin feature/my-feature).
Create a Pull Request.
We welcome bug reports, feature requests, and general improvements.

License
This project is licensed under the MIT License. See the LICENSE file for details.


