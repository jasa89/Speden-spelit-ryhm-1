#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

//**********************************
//          Global vars
//**********************************

volatile int buttonNumber = -1;           //  For buttons interrupt handler
volatile int buttonNumber2 = -1;          //  For buttons interrupt handler 
volatile int correctPresses = 0;
volatile int score = 0;                   //  Track Score

//for random LED
int userNumbers[100];                     //  Array for random integers (leds)
int currentLedIndex = 0;                  //  For saving to array
int currentButtonIndex = 0;               //  For getting the array history

volatile bool newTimerInterrupt = false;  //  For timer interrupt handler
volatile bool isRunning = false;          //  For setting if the game is running or not


//**********************************
//          Known bugs
//**********************************
/*
BUG: If two of the same numbers are generated after each other the led does not turn off making the game confusing on what to press
BUG: Cannot speed up everytime button is pressed the press doesn't always get registered probably a timer issue?


*/
//**********************************
//            Setup
//**********************************

void setup()
{
  //  Initialize all modules
  Serial.begin(9600); //TEST
  pinMode(12,INPUT_PULLUP); //TEST

  void initButtonsAndButtonInterrupts(void);
  void initializeDisplay(void);
  void initializeLeds();
  
}


//**********************************
//          Main loop
//**********************************
void loop() {
//--------TEST CODE---------------
    byte buttonPress = digitalRead(12);  //TEST
  if (buttonPress==LOW) {               
    buttonNumber++;        
  //Serial.print("ButtonNumber: "); 
  //Serial.println(buttonNumber);   
  }
//--------END OF TEST CODE---------

//This is supposed to be true when (undecided) two buttons are pressed
  if(buttonNumber>=0) {
     // start the game if buttonNumber == 4
      
      
//--------TEST CODE----------------
      buttonPress = 0;
      buttonNumber=-1;
//--------END OF TEST CODE---------

      startTheGame(); //START


     // check the game if 0<=buttonNumber<4
  }

  if(newTimerInterrupt) {
    newTimerInterrupt = false;
     // new random number must be generated and corresponding led must be activated

    //Generate random number for ledNumber
    byte ledNumber = random(0,4);             //Generate number for ledNumber
    userNumbers[currentLedIndex] = ledNumber; //Assign ledNumber to array
    currentLedIndex++;                        //Increment currentIndex to change array "save slot"
    setLed(ledNumber);                        //Call function setLed from leds.cpp to light the led

//--------TEST CODE-------------
    Serial.print("LED: ");  
    Serial.println(ledNumber);
//--------END OF TEST CODE------
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
//--------TEST CODE-----------------------
 // Serial.println("interrupt happened"); 
   byte buttonPress = digitalRead(12);
//--------END OF TEST CODE---------------


//Only get faster after 10 correct button presses (not implemented yet) only works with a regular button press ignoring whether press was correct or not
//This IF probably belongs in function checkGame()

  if (buttonPress==LOW) {

    int correctLed = userNumbers[currentButtonIndex]; //Store corresponding array value to correctLed determined by currentButtonIndex to get the history of leds
      
    if (correctLed == nbrOfButtonPush) {  //if led is the same as the button that was pressed do increment    ! Implement nbrOfButtonPush !
        correctPresses++;
        currentButtonIndex++;         //Increment currentButtonIndex by one to get the next led value
    }

    while(correctPresses>=10) {   //after 10 correct button presses, increase interrupt rate
      OCR1A = OCR1A / 1.2;        //Divide OCR1A value to speed up
      correctPresses = 0;
    }
    
//--------TEST CODE-----------------------
    Serial.print("LED history:");
    Serial.println(correctLed);
//--------END OF TEST CODE---------------
  }

  //set newTimerInterrupt to true to generate a new number in loop()
  newTimerInterrupt = true;
}




//**********************************
//          Check game
//**********************************

void checkGame(byte nbrOfButtonPush)  {
	/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/

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
void startTheGame() {
   // see requirements for the function from SpedenSpelit.h
  if (isRunning == false) {
  initializeTimer(); //Activate timer
  initializeGame();

  interrupts(); //Activate interrupts
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
  noInterrupts();          //disable interrupts
    for(int j=0;j<150;j++) {  //do something cool
      setAllLeds();
    }

  Serial.println("REBOOTING");
  delay(50);
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
}
