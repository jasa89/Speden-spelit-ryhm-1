#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile int score = 0;
volatile int interruptCounter = 0;

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

void loop()
{
  byte luettu = digitalRead(12);    //TEST
  if (luettu ==LOW) {               //TEST
    buttonNumber++;                 //TEST
    Serial.print("ButtonNumber: "); //TEST
    Serial.println(buttonNumber);   //TEST
  }
  if(buttonNumber>=0)
  {
     // start the game if buttonNumber == 4
      isRunning = true;
      Serial.println("Interrupts enabled");
      luettu = 0;             //TEST
      buttonNumber=-1;
      
     // check the game if 0<=buttonNumber<4
  }

  if(newTimerInterrupt)
  {
    newTimerInterrupt = false;
     // new random number must be generated and corresponding led must be activated

    //Generate random number to int variable
    int ledNumber = random(0,4); 
    int led = ledNumber;
    Serial.print("LED: ");
    Serial.println(led);

    

  }
}

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
  TCCR1A = 0;         //WGM11 ja WGM10 = 0
  TCCR1B = 11;        //WGM12 => CTC mode ja CS11 ja CS10 => prescaler jakaa 64:lla 16000 000 Hz kellon => 250 000 sykäystä/s
  OCR1A = 250000;      // => 1000 keskeytystä/s
  TIMSK1 = 2;         // OCIE1A = Output Compare Interrupt Enable 1A

}


ISR(TIMER1_COMPA_vect) //GPT
{
  //  Communicate to loop() that it's time to make new random number. Increase timer interrupt rate after 10 interrupts.
  Serial.println("interrupt happened");   //TEST

  //Increase interruptCounter by 1
  interruptCounter++;

  //after 10 interrupts, increase interrupt rate:
  if (interruptCounter >= 10) {
    OCR1A = OCR1A / 2;    //Halve the compare value to double the interrupt frequency
    interruptCounter = 0; //Reset counter
  }

  //set newTimerInterrupt to true to generate a new number in loop()
  newTimerInterrupt = true;
  Serial.println(interruptCounter); //TEST
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h

  initializeTimer(); //Activate timer
  InitializeGame();


  interrupts(); //Activate interrupts
}

