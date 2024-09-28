#include "buttons.h"




void initButtonsAndButtonInterrupts(void)
{
  // See requirements for this function from buttons.h
PCICR |= B00000100;
PCMSK2 |= B11110000;
 for (int i = 0; i < 4 ; i++)
      {
        pinMode(PINS[i], INPUT_PULLUP);

      } 
}

ISR(PCINT2_vect) {
  	static unsigned long lastInterrupTimeStamp=0;
	unsigned long interrupTimeStamp=millis();
        	if (interrupTimeStamp - lastInterrupTimeStamp > 50)
        		{
          		for (int j=0; j<4; j++)
            		{
              			if (digitalRead(PINS[j] == LOW))
              			{
                			pressedButton=PINS[j];
              			}
            		}
              		lastInterrupTimeStamp=interrupTimeStamp;
        		}
}
