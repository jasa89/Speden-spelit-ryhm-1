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
volatile byte buttonState=0;


volatile bool newTimerInterrupt = false;  //  For timer interrupt handler
volatile bool checkGameStatus = false;
volatile bool gameActive = false;          //  For setting if the game is running or not

//**********************************
//          Known bugs
//**********************************
/*
BUG: If two of the same numbers are generated after each other the led does not turn off making the game confusing on what to press
BUG: setAllLeds() function only lights up two leds
BUG: Buttons seem to bounce causing various problems like making the player fail on the 1st button press even if correct.
BUG: when endGame() is called the game doesn't reset, just hangs
*/
//**********************************
//            Setup
//**********************************

void setup()
{
  //  Initialize all modules
  Serial.begin(9600); //TEST
  //Changed inits to fuction calls.
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  pinMode(13,INPUT); //for reset
  
}


//**********************************
//          Main loop
//**********************************
void loop() {

//This is supposed to be true when (undecided) two buttons are pressed


  while (gameActive==false) {                            //While loop for waiting user to start the game via inputs
    setAllLeds();
      if(buttonState>=8)  {                             //Start game by calling startGame function if buttonState is more or equal to 8 meaning two buttons must be pressed for this to be true
      Serial.println("Starting in: 3");
      delay(1000);
      Serial.println("Starting in: 2");
      delay(1000);
      Serial.println("Starting in: 1");
      delay(1000);
      gameActive = true;
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
  sei();
}


ISR(TIMER1_COMPA_vect)  {
  //  Communicate to loop() that it's time to make new random number. Increase timer interrupt rate after 10 interrupts.

  //set newTimerInterrupt to true to generate a new number in loop()
  newTimerInterrupt = true;
  Serial.println("running TIMER1");
}

ISR(PCINT2_vect)
{
  
  Serial.println("running PCINT2_vect");
  static unsigned long lastInterrupTimeStamp=0;
  unsigned long interrupTimeStamp=millis();
    if (interrupTimeStamp - lastInterrupTimeStamp > 240)  {
      buttonState=0;  
      
        for(int i = 0; i < 4; i++)  {

            if(digitalRead(PINS[i]) == LOW) {
		          buttonState |= 1<<i;
		          userNumbers[currentButtonIndex]=i;
            	currentButtonIndex++;
            	checkGameStatus=true;
              
	          }
	        }

	    lastInterrupTimeStamp=interrupTimeStamp;

    }
}

//**********************************
//          Check game
//**********************************

void checkGame() {
	/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
*/
  Serial.println("running checkGame");
//compare arrays to currentButtonIndex (i), if userNumbers dont't match randomNumbers then end the game (maybe belongs in PCINT2_vect?)
    for (int i=0; i<=currentButtonIndex;i++) {
       if (userNumbers[i] != randomNumbers[i] ) {    //userNumbers = button press history --- randomNumbers = led history
        endGame();
      }

      else {
        correctPresses++;
        score += 10;
        showResult(score);
        checkGameStatus = false;
        Serial.print("Correct Presses:");
        Serial.println(correctPresses);
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

  currentButtonIndex = 0;
  currentLedIndex = 0;
  showResult(0);
}



//**********************************
//          Start the game
//**********************************
void startGame() {
   // see requirements for the function from SpedenSpelit.h
  if (gameActive == true) {
    cycleRandomLeds(); //Needs delay?
    initializeGame();
    initializeTimer(); //Activate timer

    Serial.println("STARTING GAME");
    interrupts(); //Activate interrupts
  }
}

//**********************************
//           End the game
//**********************************
void endGame() {
  noInterrupts();
  Serial.println("running endGame");
  gameActive = false;
}

//**********************************
//           Sources
//**********************************
// https://www.w3schools.com/
// https://stackoverflow.com/questions/24153883/comparing-two-arrays-in-c-element-by-element

//**********************************
//    Clipboard for copypasting     
//**********************************
/* COMPARE 
    for(int k=4; k<=7;k++) {
    if (digitalRead(PINS[k]) == LOW) {                //Check PINS from 4 to 7 if some of them are low
      Serial.print("comparing");
      int buttonNumber = digitalRead(PINS[k]);        //Save the PIN value to variable
      userNumbers[currentButtonIndex] = buttonNumber; //Save the PIN value to array
      currentButtonIndex++;                           //Increment currentIndex to change array "save slot"
      checkGameStatus = true;                         //set checkGameStatus to true to check if the press was correct
    }
  }
*/
