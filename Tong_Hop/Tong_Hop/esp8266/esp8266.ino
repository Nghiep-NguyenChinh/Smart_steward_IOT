#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <StringSplitter.h>

//code firebase
String FIREBASE_HOST = "smart-steward-default-rtdb.firebaseio.com";
String FIREBASE_AUTH = "BB1UD4sslGjWOlizxUxwrkxWlUXjj1vprNDtIZGF";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

SoftwareSerial myserial(D1, D2); // giả lập rx tx

// Variables to save date and time
String formattedDate, state, send0, sendb, doc_t, gio, phut, giay, ngay, thang, nam, save[8];
uint8_t run8266 = 0, nd_tb, da_tb;
unsigned long send_ml;

void readF() {
  //2021-05-25T13:42:43Z
  timeClient.forceUpdate();
  doc_t = timeClient.getFormattedDate();
  Serial.println(doc_t);

  nam = doc_t.substring(0, 4);
  thang = doc_t.substring(5, 7);
  ngay = doc_t.substring(8, 10);
  gio = doc_t.substring(11, 13);
  phut = doc_t.substring(14, 16);
  giay = doc_t.substring(17, 19);

  Serial.println("Read");
  if (myserial.available() > 0) {
    state = myserial.readStringUntil('\n');
    Serial.println(state);

    StringSplitter *splitter = new StringSplitter(state, ',', 8);
    int itemCount = splitter->getItemCount();

    for (int i = 0; i < itemCount; i++) {
      String item = splitter->getItemAtIndex(i);
      save[i] = item;
    }

    delete splitter;

    //triet,0,0,0,0,0,ta,\n
    if (save[0] == "triet" && save[6] == "ta") {
      Serial.println("d2");
      Firebase.setInt("da pn 2", save[3].toInt());
      Firebase.setInt("nd pn 2", save[4].toInt());

      Serial.println("d1");
      Firebase.setInt("da pn 1", save[1].toInt());
      Firebase.setInt("nd pn 1", save[2].toInt());

      Serial.println("cs");
      Firebase.setString("cs", save[5]);

      nd_tb = (save[4].toInt() + save[2].toInt()) / 2;
      da_tb = (save[1].toInt() + save[3].toInt()) / 2;

      Firebase.setInt("tk/" + ngay + "-" + thang + "-" + nam + "/" + gio + "/nd", nd_tb);
      Firebase.setInt("tk/" + ngay + "-" + thang + "-" + nam + "/" + gio + "/da", da_tb);

    }
  } else state = " ";
}
// goi mega
void sendF() {
  if (digitalRead(D3) == 1) {
    if (millis() - send_ml >= 1000) {
      Serial.println("Send");
      send0 = send0 + "triet,";
      send0 = send0 + getFB("dk pn 1") + ",";
      send0 = send0 + getFB("dk pn 2") + ",";
      send0 = send0 + getFB("dk pk") + ",";
      send0 = send0 + getFB("dk pb") + ",";
      send0 = send0 + getFB("dk pt") + ",";
      send0 = send0 + getFB("dk rl") + ",";
      send0 = send0 + getFB("dk cua") + ",";
      send0 = send0 + ngay + "-" + thang + "-" + nam + " " + gio + ":" + phut + ":" + giay + " " + ",";
      send0 = send0 + "ta\n";

      myserial.print(send0);
      myserial.flush();
      Serial.print(send0);

      send0.clear();

      send_ml = millis();
    }
  }
  else if (digitalRead(D3) == 0) {
    if (millis() - send_ml >= 1000) {
      Serial.println("Send time");
      send0 = send0 + "triet1,";
      send0 = send0 + ngay + "-" + thang + "-" + nam + " " + gio + ":" + phut + ":" + giay + " " + ",";
      send0 = send0 + "ta1\n";

      myserial.print(send0);
      myserial.flush();
      Serial.print(send0);

      send0.clear();

      send_ml = millis();
    }
  }
}

void setup()
{
  Serial.begin(9600);
  WiFi.begin("NAM ANH", "113114115@");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  myserial.begin(9600);

  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(25200);

  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(D3, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, 1);
}

uint8_t getFB(String str) {
  return Firebase.getInt(str);
}

void loop()
{
  readF();
  sendF();
  run8266 = !run8266 & 1;
  Firebase.setInt("run8266", run8266);

  delay(500);
}
