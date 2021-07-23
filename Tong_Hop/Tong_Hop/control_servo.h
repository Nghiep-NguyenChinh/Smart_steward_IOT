#ifndef CONTROL_SERVO_H
#define CONTROL_SERVO_H

#include <Servo.h>

Servo myser1, myser2;

#define serPin1 12
#define serPin2 13

bool stateDoor = 0; //0 is close

void servo_setup()
{
  pinMode(serPin1, INPUT_PULLUP);
  pinMode(serPin2, INPUT_PULLUP);
  myser1.attach(serPin1);
  myser2.attach(serPin2);
  myser1.write(160); //Phai 160
  myser2.write(0);
}

void openDoor()
{
  if(stateDoor)
    return;
  byte a = 160;
  byte b = 0;
  for(byte i=0; i<9; i++)
  {
    a = a - 10;
    b = b + 10;
    myser1.write(a);
    myser2.write(b);
  }
  stateDoor = 1;
}

void closeDoor()
{
  if(!stateDoor)
    return;
  byte a = 65;
  byte b = 95;
  for(byte i=0; i<9; i++)
  {
    b = b - 10;
    myser2.write(b);
  }
  myser2.write(0);
  delay(10);
  myser1.write(160);
  stateDoor = 0;
}

#endif
