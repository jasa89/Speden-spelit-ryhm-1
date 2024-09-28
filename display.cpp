#include "display.h"

int reset = 12;
int shiftClock = 11;
int latchClock = 10;
int outEnable = 9;
int serialInput = 8;

byte digitSegments[]= { //segment numbers
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f  //9
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
  shiftOut(serialInput, shiftClock, MSBFIRST, digitSegment[bits]); //Arduino reference shiftOut()
    if(last) {
      digitalWrite(latchClock,HIGH);
    }
// See requirements for this function from display.h
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  writeByte(tens, false); //vasen display
  writeByte(ones, true);  //oikea display
// See requirements for this function from display.h
}

void showResult(byte number)
{
  uint8_t tens = number / 10;
  uint8_t ones = number % 10;
  writeHighAndLowNumber(tens, ones);
// See requirements for this function from display.h
}

