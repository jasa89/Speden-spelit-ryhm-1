#include "buttons.h"
const int PIN[] = {4,5,6,7}; //Digital outs 4-7 for buttons.


 

void initButtonsAndButtonInterrupts(void)
{
  // Sources:
  // https://www.electrosoftcloud.com/en/pcint-interrupts-on-arduino/#:~:text=PCINT%20interrupts%20are%20interrupts%20that%20can%20be%20triggered%20from%20any
  // https://www.arduino.cc/reference/en/language/structure/compound-operators/compoundbitwiseor/
  // Setting interrupts for ports and setting them HIGH
PCICR |= B00000100;
PCMSK2 |= B11110000;
 for (int i = 0; i < 4 ; i++)
      {
        pinMode(PIN[i], INPUT_PULLUP);

      } 
}

int readButton() 
{
 
 int button=0;   
 //checking for ports that are LOW and marking corresponding bit as 1 
 for(int i = 0; i < 4; i++)  
      {
        if(digitalRead(PIN[i]) == LOW)
              button |= 1<<i;
      }
    //returns the info to caller
    return(button);          
  }

int whatButton( int w)
{
//Converting buttonvalue to led value.
   int convertedLedValue= 5;
   switch (w) {
  case 1:
    convertedLedValue= 0;
    break;
  case 2:
    convertedLedValue= 1;
    break;
  case 4:
    convertedLedValue= 2;
    break;
  case 8:
    convertedLedValue= 3;
    break;
  default:
    convertedLedValue= 4;
    break;
} 

    return(convertedLedValue) ;

} 

