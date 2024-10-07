#include "leds.h"
#include "buttons.h"
//void checkGame(byte);
const int PINS[] = {4,5,6,7};
//volatile int pressedButton = 0;
byte buttonRead=false;
volatile int buttonState = 0;
int chosenNumbers[10];
int userNumbers[10];
int numberCounter=0; 
int  currentButtonIndex=0;
/*  if button 1 pressed , value is 1
    if button 2 pressed , value is 2
    if button 3 pressed , value is 4
    if button 4 pressed , value is 8
    if value >=9 , two buttons pressed (for reset)
*/ 

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
initButtonsAndButtonInterrupts();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  

      while(buttonRead ==true)
      {
        Serial.println("************");
        Serial.println(buttonState);
        //Serial.println(nonZero);
        Serial.println("************");
        buttonRead=false;
          if (buttonState == 1) 
          {
          analogWrite(A0,512); 
          analogWrite(A1,0);
          analogWrite(A2,0);
          analogWrite(A3,0);
          }
      else if (buttonState == 2) 
          {
          analogWrite(A0,0); 
          analogWrite(A1,512);
          analogWrite(A2,0);
          analogWrite(A3,0);
          }
      else if (buttonState == 4) 
        {
          analogWrite(A0,0); 
          analogWrite(A1,0);
          analogWrite(A2,512);
          analogWrite(A3,0);
          }
      else if (buttonState == 8) 
        {
          analogWrite(A0,0); 
          analogWrite(A1,0);
          analogWrite(A2,0);
          analogWrite(A3,512);
          }
      else {
          analogWrite(A0,0); 
          analogWrite(A1,0);
          analogWrite(A2,0);
          analogWrite(A3,0);
        
        }
      
     
      Serial.println("!");
      Serial.print(currentButtonIndex);
      Serial.println("!");
    
      while (numberCounter==4 ) {
          for (int i=0; i<4; i++)
            {Serial.println(chosenNumbers[i]);
            }
            numberCounter=0;
      }
      while (currentButtonIndex==4 ) {
          for (int i=0; i<4; i++)
            {Serial.println(userNumbers[i]);
            }
            currentButtonIndex=0;
      }
      }
    }

  /* Temporary test with stuff from github.
    ISR(PCINT2_vect)
    {
      
      static unsigned long lastInterrupTimeStamp=0;
      unsigned long interrupTimeStamp=millis();
        if (interrupTimeStamp - lastInterrupTimeStamp > 540)
          {
        buttonState=readButtons();
        chosenNumbers[numberCounter]=whatButton(buttonState);
        numberCounter++;
        buttonRead=true;
        }
      lastInterrupTimeStamp=interrupTimeStamp;
    }
  */
  ISR(PCINT2_vect)	//Does not trigger?
{
  Serial.println("running PCINT2_vect");
  static unsigned long lastInterrupTimeStamp=0;
  unsigned long interrupTimeStamp=millis();

    if (interrupTimeStamp - lastInterrupTimeStamp > 240)  {
      buttonState=0;  
      Serial.println("!!!");
        for(int i = 0; i < 4; i++)  {
          if(digitalRead(PINS[i]) == LOW) buttonState |= 1<<i;
          }
          Serial.println(buttonState);
          Serial.println(currentButtonIndex);
          userNumbers[currentButtonIndex]=buttonState/2;
          currentButtonIndex++;
          buttonRead=true;
          Serial.println("****");
	                                                        }
            
	      

	    lastInterrupTimeStamp=interrupTimeStamp;
    }
