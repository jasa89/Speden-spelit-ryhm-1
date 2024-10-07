#include "buttons.h"
const int PIN[] = {4,5,6,7};


 

void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
  // https://www.electrosoftcloud.com/en/pcint-interrupts-on-arduino/#:~:text=PCINT%20interrupts%20are%20interrupts%20that%20can%20be%20triggered%20from%20any
  // https://www.arduino.cc/reference/en/language/structure/compound-operators/compoundbitwiseor/
PCICR |= B00000100;
PCMSK2 |= B11110000;
 for (int i = 0; i < 4 ; i++)
      {
        pinMode(PIN[i], INPUT_PULLUP);

      } 
}

int readButtons()
{
  int button=0;  
  for(int i = 0; i < 4; i++)
      {
        if(digitalRead(PIN[i]) == LOW)
              button |= 1<<i;
      }
            
            //chosenNumbers[numberCounter]=buttonState;
            //numberCounter++;
            //buttonRead=true;
    return(button);          
  }

int whatButton( int w)
{
  int buttonstate= w/2;
  return buttonstate;
} 
