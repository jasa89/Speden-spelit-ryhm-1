#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
  // https://www.electrosoftcloud.com/en/pcint-interrupts-on-arduino/#:~:text=PCINT%20interrupts%20are%20interrupts%20that%20can%20be%20triggered%20from%20any
  // https://www.arduino.cc/reference/en/language/structure/compound-operators/compoundbitwiseor/
PCICR |= B00000100;
PCMSK2 |= B11110000;
 for (int i = 0; i < 4 ; i++)
      {
        pinMode(PINS[i], INPUT_PULLUP);

      } 
}
// Source-material : https://www.circuits-diy.com/button-debounce-arduino-tutorial/
// https://deepbluembedded.com/arduino-button-debouncing/
ISR(PCINT2_vect)
{
        static unsigned long lastInterrupTimeStamp=0;
        unsigned long interrupTimeStamp=millis();
        if (interrupTimeStamp - lastInterrupTimeStamp > 100)
        {
        	buttonState=0;
        
          	for(int i = 0; i < 4; i++)
            		{
            			if(digitalRead(PINS[i]) == LOW)
              			buttonState |= 1<<i;
            		}
        	changed=1;
        }
        lastInterrupTimeStamp=interrupTimeStamp;
}
