#ifndef CONTROL_H
#define CONTROL_H

#include "UART1_mega.h"
//#include "control_servo.h"

#define buzzer 39
#define relay 7
#define led1  2
#define led2  3
#define led3  4
#define led1w_a 6 //Phong ngu 1
#define led1w_b 5 //Phong khach

void setLed1W_ab(byte a, byte b)
{
  if (a > 3 || b > 3)
    return;
  switch (a)
  {
    case 0:
      analogWrite(led1w_a, 0);
      break;
    case 1:
      analogWrite(led1w_a, 30);
      break;
    case 2:
      analogWrite(led1w_a, 130);
      break;
    case 3:
      analogWrite(led1w_a, 200);
      break;
  }
  switch (b)
  {
    case 0:
      analogWrite(led1w_b, 0);
      break;
    case 1:
      analogWrite(led1w_b, 30);
      break;
    case 2:
      analogWrite(led1w_b, 130);
      break;
    case 3:
      analogWrite(led1w_b, 200);
      break;
  }
}

void control_setup()
{
  TCCR4B = TCCR4B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz Code for Available PWM frequency for D2, D3 & D5
  pinMode(led1w_a, OUTPUT);
  pinMode(led1w_b, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(buzzer, 0);
  digitalWrite(relay, sRelay);
  digitalWrite(led1, sLed_A);
  digitalWrite(led2, sLed_B);
  digitalWrite(led3, sLed_C);
  setLed1W_ab(sLed1W_A, sLed1W_B);
}

void control_()
{
  digitalWrite(relay, sRelay);
  digitalWrite(led1, sLed_A);
  digitalWrite(led2, sLed_B);
  digitalWrite(led3, sLed_C);
  setLed1W_ab(sLed1W_A, sLed1W_B);

}

#endif
