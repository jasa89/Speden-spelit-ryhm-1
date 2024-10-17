# Speden Sepelit

Speden Sepelit is an Arduino-based game project that starts when player pushes a button. The project controls a set of 4 LEDs using analog pins 0 to 3  and player must press correct button when led is turned on and it is possible to palyer to follow behind if the order is the same as lighted leds. There is also two sevensegment displays to show countdownt to start the game and to display current score. 

## Table of contents

* [Project Description](#project-description)
* [Features](features)
* [Hardware Requirements](#hardware-reguirements)
* [Software Requirements](#softtware-reguirements)
* [Circuit Diagram](https://github.com/jasa89/Speden-spelit-ryhm-1/blob/main/Project%20Documents/Circuit%20Diagram/CircuitDiagram.png)
* [Installation](#installation)
* [Usage]()




## Project Description 

The Speden Sepelit projectis a game made using an Arduino. It has several parts as follows:

* Speden spelit.ino to control the game
* buttons files  where buttons are handled
* leds files where leds are handled 
* display files where dispays are handled 
* The code is written in C++ for the Arduino platform.

## Features

* Sequential LED Blinking: LEDs light up in a predefined sequence and the game will speed up after 10 rounds.
* Count down feature on sevensegment displays to show the palyer when the game starts
* 
* 

## Hardware Requirements

To recreate this project, you'll need the following hardware components:

* Arduino (Uno, Nano, or any compatible board)
* 4 LEDs (any color)
* 4 push buttons
* 5 Resistors ( 470Ω recommended)
* 2 sevensegment displays
* 2 Breadboards 
* Jumper wires
* USB Cable to connect the Arduino to your computer


## Software Requirements

Arduino IDE: Download and install the Arduino IDE from [Arduino's official website](https://www.arduino.cc/).
Speden Sepelit Code: Clone or download the project from this repository.

## Circuit Diagram

Here’s how to wire your components:
see this from [Circuit Diagram](https://github.com/jasa89/Speden-spelit-ryhm-1/blob/main/Project%20Documents/Circuit%20Diagram/CircuitDiagram.png): 


## Installation

1. Clone the Repository
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

## Usage

Player starts tehe game by pressing any of the four pushbuttons and this will start the count on one sevensegment display and the leds will go off when the game starts. Ledst start to blink randomly and the palyer has to push the correct button connected to specific led while game is active the sevensegment displays will display the current score. Game stops when palyer makes wrong choise and presses incorrect button and the game will go back to starting position where all led are lit on.  





