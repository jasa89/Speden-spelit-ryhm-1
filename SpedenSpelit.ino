#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile int buttonNumber2 = -1;          // for buttons interrupt handler 
volatile int score = 0;
volatile int interruptCounter = 0;

//for random LED number
int userNumbers[100];
int currentIndex = 0;

volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool isRunning = false;




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
  byte luettu = digitalRead(12);    
  if (luettu ==LOW) {               
    buttonNumber++;        
  //Serial.print("ButtonNumber: "); 
  //Serial.println(buttonNumber);   
  }
//--------END OF TEST CODE---------

  if(buttonNumber>=0) {
     // start the game if buttonNumber == 4
      isRunning = true;
      
//--------TEST CODE----------------
      luettu = 0;
      buttonNumber=-1;
//--------END OF TEST CODE---------

      startTheGame();
     // check the game if 0<=buttonNumber<4
  }

  if(newTimerInterrupt) {
    newTimerInterrupt = false;
     // new random number must be generated and corresponding led must be activated

    //Generate random number for ledNumber
    byte ledNumber = random(0,4);            //Generate number for ledNumber
    userNumbers[currentIndex] = ledNumber;  //Assign ledNumber to array
    currentIndex++;                         //Increment currentIndex to change array "save slot"

//--------TEST CODE-------------
    //Serial.print("LED: ");                  //Print LED value
    //Serial.println(ledNumber);
//--------END OF TEST CODE------

    setLed(ledNumber);

//--------TEST CODE-------------
    Serial.print("LED: ");  
    Serial.println(ledNumber);
//--------END OF TEST CODE------
  }

}



//**********************************
//        Timer/Interrupt
//**********************************

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
  TCCR1A = 0;         //WGM11 ja WGM10 = 0
  TCCR1B = 11;        //WGM12 => CTC mode ja CS11 ja CS10 => prescaler jakaa 64:lla 16000 000 Hz kellon => 250 000 sykäystä/s
  OCR1A = 250000;      // => 1000 keskeytystä/s
  TIMSK1 = 2;         // OCIE1A = Output Compare Interrupt Enable 1A

}


ISR(TIMER1_COMPA_vect)
{
  //  Communicate to loop() that it's time to make new random number. Increase timer interrupt rate after 10 interrupts.
//--------TEST CODE-----------------------
 // Serial.println("interrupt happened"); 
//--------END OF TEST CODE---------------

  //Increase interruptCounter by 1
  interruptCounter++;

  //after 10 interrupts, increase interrupt rate:
  if (interruptCounter >= 10) {
    OCR1A = OCR1A / 1.1;        //Halve the compare value to double the interrupt frequency
    interruptCounter = 0;     //Reset counter
  }

  //set newTimerInterrupt to true to generate a new number in loop()
  newTimerInterrupt = true;

//--------TEST CODE------------------------
  //Serial.println(interruptCounter); 
//--------END OF TEST CODE-------------
}




//**********************************
//          Check Game
//**********************************

void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}





//**********************************
//         initializeGame
//**********************************
void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}




//**********************************
//            StartGame
//**********************************
void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h

  initializeTimer(); //Activate timer
  initializeGame();

  interrupts(); //Activate interrupts

//--------TEST CODE--------------------------
  Serial.println("Interrupts enabled");
//--------END OF TEST CODE---------------------
}

