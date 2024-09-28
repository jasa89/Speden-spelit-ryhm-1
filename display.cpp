#include "display.h"

int reset = 12;
int shiftClock = 11;
int latchClock = 10;
int outEnable = 9;
int serialInput = 8;

byte digitSegments[]= {
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
  
// See requirements for this function from display.h
}


void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
// See requirements for this function from display.h
}

void showResult(byte number)
{
// See requirements for this function from display.h
}

