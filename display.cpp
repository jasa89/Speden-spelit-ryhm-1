#include "display.h"

int reset = 12;
int shiftClock = 11;
int latchClock = 10;
int outEnable = 9;
int serialInput = 8;

byte digitSegments[]= { //segment numbers
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void initializeDisplay(void)
{
  //alustetaan lähtönä
  pinMode(reset,OUTPUT);
  pinMode(shiftClock,OUTPUT);
  pinMode(latchClock,OUTPUT);
  pinMode(outEnable,OUTPUT);
  pinMode(serialInput,OUTPUT);
  //nollataan siirtorekisterit
  digitalWrite(reset,HIGH);
  delay(1);
  digitalWrite(reset,LOW);
  delay(1);
  digitalWrite(reset,HIGH);
// See requirements for this function from display.h
}

void writeByte(uint8_t bits,bool last)
{
  digitalWrite(latchClock, LOW); //
  shiftOut(serialInput, shiftClock, MSBFIRST, digitSegments[bits]); //Arduino reference shiftOut()
    if(last) {
      digitalWrite(latchClock,HIGH);
    }
// See requirements for this function from display.h
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  writeByte(tens, true); //vasen display
  writeByte(ones, false);  //oikea display
// See requirements for this function from display.h
}

void showResult(byte number)
{
  uint8_t tens = number / 10;
  uint8_t ones = number % 10;
  writeHighAndLowNumber(ones, tens);
// See requirements for this function from display.h
}

