#ifndef BUTTONS_H
#define BUTTONS_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int PINS[] = {4,5,6,7};

 
/*  if button 1 pressed , value is 1
    if button 2 pressed , value is 2
    if button 3 pressed , value is 4
    if button 4 pressed , value is 8
    if any other value, two buttons pressed (for reset)
*/ 


/* 
  initButtonsAndButtonInterrupts subroutine is called from Setup() function
  during the initialization of Speden Spelit. This function does the following:
  1) Initializes 4 button pins for the game = Arduino pins 4,5,6,7
  2) Enables PinChangeInterrupt on D-bus in a way that interrupt
     is generated whenever some of pins 4,5,6,7 is connected to LOW state

*/
void initButtonsAndButtonInterrupts(void);


// Intoduce PCINT2_vect Interrupt SeRvice (ISR) function for Pin Change Interrupt.
ISR(PCINT2_vect); 
//functons interrupt uses
int readButton(void); //read button and reurn its value
int whatButton(int);  // translates button to corresponding led
#endif;
