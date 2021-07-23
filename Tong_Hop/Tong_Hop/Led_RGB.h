#ifndef LED_RGB_H
#define LED_RGB_H

#define b A8
#define r A9
#define g A10

void blinkLED(char color)
{
  if(color == 'r')
  {
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
    delay(1);
    analogWrite(r,0);
    analogWrite(g,255);
    analogWrite(b,255);
    delay(1);
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
  }
  if(color == 'b')
  {
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
    delay(1);
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,0);
    delay(1);
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
  }
  if(color == 'g')
  {
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
    delay(1);
    analogWrite(r,255);
    analogWrite(g,0);
    analogWrite(b,255);
    delay(1);
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,255);
  }
}

void setLedRGB(char color)
{
  if(color == 'r')
  {
    analogWrite(r,0);
    analogWrite(g,255);
    analogWrite(b,255);
  }
  if(color == 'b')
  {
    analogWrite(r,255);
    analogWrite(g,255);
    analogWrite(b,0);
  }
  if(color == 'g')
  {
    analogWrite(r,255);
    analogWrite(g,0);
    analogWrite(b,255);
  }
}

#endif
