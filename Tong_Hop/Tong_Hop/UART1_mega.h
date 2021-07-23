#ifndef UART1_MEGA_H
#define UART1_MEGA_H

#include <StringSplitter.h>

bool sRelay = 0;
byte sLed1W_A = 0; //p.ngu1
//Led 1W se co gia tri 0-1-2-3 tuong ung cuong do sang
byte sLed1W_B = 0; //p.khach
bool sLed_A = 0;  //p.bep
bool sLed_B = 0;  //p.tam
bool sLed_C = 0;  //p.ngu2
bool sDoor = 0;

char mk[5] = "0000";

String tmp, time_g, save[10];

void uart1_setup()
{
  Serial3.begin(9600);
}

void reciveUART()
{
  Serial.println("Doc du lieu...");
  if (Serial3.available() > 0) {
    tmp = Serial3.readStringUntil('\n');
    Serial.println(tmp);
    
    StringSplitter *splitter = new StringSplitter(tmp, ',', 10);
    int itemCount = splitter->getItemCount();

    for (int i = 0; i < itemCount; i++) {
      String item = splitter->getItemAtIndex(i);
      save[i] = item;
    }

    delete splitter;

    //triet,0,0,0,0,0,0,0,2021-06-08T13:49:17Z,ta,\n
    if (save[0] == "triet" && save[9] == "ta") {
      sLed1W_A = save[1].toInt();
      sLed_C = save[2].toInt();
      sLed1W_B = save[3].toInt();
      sLed_A = save[4].toInt();
      sLed_B = save[5].toInt();
      sRelay = save[6].toInt();
      sDoor = save[7].toInt();

      time_g = save[8];
    } else if (save[0] == "triet1" && save[2] == "ta1") time_g = save[1];
  }
}

#endif
