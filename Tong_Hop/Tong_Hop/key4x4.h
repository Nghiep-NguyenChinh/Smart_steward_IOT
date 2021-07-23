#ifndef KEY4X4_H
#define KEY4X4_H

#include <Keypad.h>

char keys[4][4] = //keys[rows][columns]
{
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'},
};

//Pin map keypad 4x4 arduino
byte rowPins[4] = {23, 25, 27, 29};
byte columnPins[4] = {31, 33, 35, 37};

//setup keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, 4, 4);

void key4x4_setup()
{
  keypad.setDebounceTime(10);
}

char getKeyPW()
{
  char temp = keypad.getKey();
  if ((int)keypad.getState() == PRESSED)
  {
    return temp;
  }
}

#endif
