#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

//**********************************
//          Global vars
//**********************************


volatile int score = 0;                   //  Track Score

//for random LED
int randomNumbers[100];                   //  Array for random integers (leds)
int currentLedIndex = 0;                  //  For saving to array

//for buttons
int currentButtonIndex = 0;               //  For getting the array history
int userNumbers[100];                     //  Array for button presses
volatile int correctPresses = 0;          //  For tracking correct presses to speed up the leds
volatile int buttonNumber = -1;           //  For buttons interrupt handler

volatile bool newTimerInterrupt = false;  //  For timer interrupt handler
volatile bool checkGameStatus = false;
volatile bool isRunning = false;          //  For setting if the game is running or not


//**********************************
//          Known bugs
//**********************************
/*
BUG: If two of the same numbers are generated after each other the led does not turn off making the game confusing on what to press
BUG: Cannot speed up everytime button is pressed the press doesn't always get registered probably a timer issue?
BUG: NOT TESTED! Most likely array comparison will end the game everytime if the player is slower than the leds which is how it should not work since it's okay for the player to be slower as long as the button presses are correct
BUG: NOT TESTED! Led effect cycleRandomLeds() probably won't play correctly when starting the game
*/
//**********************************
//            Setup
//**********************************

void setup()
{
  //  Initialize all modules
  Serial.begin(9600); //TEST

 // void initButtonsAndButtonInterrupts(void); Defined in leds.h
  void initializeDisplay(void);
  void initializeLeds();
  pinMode(13,INPUT);
  
}


//**********************************
//          Main loop
//**********************************
void loop() {

//This is supposed to be true when (undecided) two buttons are pressed
  byte buttonPress = digitalRead(4);  //TEST
  byte buttonPress2 = digitalRead(7);  //TEST

  while (isRunning==false) {            //start the game if ports 4 and 7 are pressed     
    if(buttonState > 8) {
      startGame();
    }
    
  }

  if(newTimerInterrupt) {
    newTimerInterrupt = false;
     // new random number must be generated and corresponding led must be activated

    //Generate random number for ledNumber
    byte ledNumber = random(0,4);             //Generate number for ledNumber
    randomNumbers[currentLedIndex] = ledNumber; //Assign ledNumber to array
    currentLedIndex++;                        //Increment currentIndex to change array "save slot"
    setLed(ledNumber);                        //Call function setLed from leds.cpp to light the led
  }

  if (checkGameStatus == true) {
    checkGame();
  }
}



//**********************************
//        Timer/Interrupt
//**********************************

void initializeTimer(void)  {

  cli(); //stop interrupts "clear interrupts"
  TCCR1A = 0;         //WGM11 ja WGM10 = 0
  TCCR1B = 12;      //WGM12 => CTC mode ja CS11 ja CS10 => prescaler. this is now 256  -> 16/256 = (not calculated) kHz which means Y microseconds until increment happens
  //^ B:n prescaleriksi arvo 256. Kello pyörii 16MHz taajuudella, montako pulssia (prescaler) mennään, että tulee yhden timer counter arvo isommaksi. 
  OCR1A = 250000;      // OCIE1A = Output Compare Interrupt Enable 1A 
  //^ When the counter reaches 250,000, it triggers an interrupt on TCCR1A, then resets to 0 and starts counting again. 250000 / X = Y so interrupt happens every F seconds
  TIMSK1 = 2;         
  //^ Kun arvo ylittyy tulee keskeytys(?) hämmentävä setti.
}


ISR(TIMER1_COMPA_vect)  {
  //  Communicate to loop() that it's time to make new random number. Increase timer interrupt rate after 10 interrupts.

  //set newTimerInterrupt to true to generate a new number in loop()
  newTimerInterrupt = true;
}

ISR(PCINT2_vect) { //Button interrupt handler

  for(int k=4; k<=7;k++) {
    if (digitalRead(PINS[k]) == LOW) {                //Check PINS from 4 to 7 if some of them are low
      int buttonNumber = digitalRead(PINS[k]);            //Save the PIN value to variable
      userNumbers[currentButtonIndex] = buttonNumber; //Save the PIN value to array
      currentButtonIndex++;                           //Increment currentIndex to change array "save slot"
      checkGameStatus = true;                         //set checkGameStatus to true to check if the press was correct
    }
  }
}


//**********************************
//          Check game
//**********************************

void checkGame()  {
	/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/

//compare arrays to currentLedIndex (i), if userNumbers wont match randomNumbers then end the game
for (int i=0; i<=currentLedIndex;i++) {
  if (userNumbers[i] != randomNumbers[i] ) {
    endGame();
  }

    else {
      checkGameStatus = false;
      correctPresses++;
    }
//Only get faster after 10 correct button presses, probably need a better solution for speeding up instead of correctPresses >=10
  if (correctPresses >=10) {
      OCR1A = OCR1A / 1.2;
      correctPresses = 0;
    }
  }
}



//**********************************
//         Initialize Game
//**********************************
void initializeGame() {

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
}




//**********************************
//          Start the game
//**********************************
void startGame() {
   // see requirements for the function from SpedenSpelit.h
  if (isRunning == false) {
  cycleRandomLeds(); //Needs delay?
  initializeTimer(); //Activate timer
  initializeGame();

  sei(); //Activate interrupts
  isRunning = true;
//--------TEST CODE--------------------------
 // Serial.println("Interrupts enabled");
//--------END OF TEST CODE---------------------
  }
}

//**********************************
//           End the game
//**********************************
void endGame() {
  cli();          //disable interrupts
  isRunning = false;
    for(int j=0;j<3;j++) {  //do something cool
      setAllLeds();
      delay(1000);
    }

  Serial.println("REBOOTING");
  delay(50);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

//**********************************
//           Sources
//**********************************
// https://www.w3schools.com/
// https://stackoverflow.com/questions/24153883/comparing-two-arrays-in-c-element-by-element
