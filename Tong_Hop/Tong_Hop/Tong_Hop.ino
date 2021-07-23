//#include "Led_RGB.h"
#include "UART1_mega.h"
#include "control_.h"
#include "key4x4.h"
#include "dht11.h"
//#include "control_servo.h"
#include "acs712.h"
#include "mq2_adc.h"
#include "lcd_i2c.h"
#include <Thread.h>
#include <SoftwareSerial.h>

SoftwareSerial serial1(18, 19);

Thread amp_th = Thread(), dht1_th = Thread(), dht2_th = Thread(), mq_th = Thread(), uart_th = Thread(),
       key_th = Thread();

unsigned long buzz_millis, send_millis, rst_ml;

char c_TH, ch[5];
uint8_t dem_TH = 0;
double ampe, ampe_old;
bool stateBuzz = false, x = false, sim_tt = false, cp_rev = false;

dhtTypeDef valueDHTA;
dhtTypeDef valueDHTB;

void setup()
{
  Serial.begin(9600);
  serial1.begin(9600);

  uart1_setup();
  control_setup();
  reciveUART();

  //key4x4_setup();
  dht11_setup();
  //servo_setup();

  lcd_init();

  Serial.begin(9600);

  amp_th.onRun(ampF);
  amp_th.setInterval(1000);
  mq_th.onRun(mqF);
  mq_th.setInterval(1000);
  dht1_th.onRun(dht1F);
  dht1_th.setInterval(1000);
  dht2_th.onRun(dht2F);
  dht2_th.setInterval(1000);
  uart_th.onRun(uartF);
  uart_th.setInterval(1000);
  key_th.onRun(cKey);
  key_th.setInterval(100);

}

void mqF() {
  if (getADCMQ2())
  {
    stateBuzz = true;
  }
  else
  {
    stateBuzz = false;
  }
}

void uartF() {
  //if (cp_rev)
  //{
  reciveUART();
  control_();
  
  lcd.setCursor(0, 1);
  lcd.print(time_g);
  //}
}

void ampF() {
  ampe = getAmps();
  if (ampe_old != ampe)
  {
    ampe_old = ampe;
  }
}

void dht1F() {
  valueDHTA = getDHTRoomsA();
  lcd.setCursor(10, 2);
  lcd.print(valueDHTA.Temperature);
  lcd.setCursor(12, 2);
  lcd.write(0b11011111);
  lcd.setCursor(15, 2);
  lcd.print(valueDHTA.Humidity);
}

void dht2F() {
  valueDHTB = getDHTRoomsB();
  lcd.setCursor(10, 3);
  lcd.print(valueDHTB.Temperature);
  lcd.setCursor(12, 3);
  lcd.write(0b11011111);
  lcd.setCursor(15, 3);
  lcd.print(valueDHTB.Humidity);
}

void sendS() {
  /*char send0[40], buff[4];
    dtostrf(ampe, 4, 2, buff);*/
  /*sprintf(send0, "triet,%d,%d,%d,%d,%s,ta,end", valueDHTA.Humidity, valueDHTA.Temperature, valueDHTB.Humidity,
          valueDHTB.Temperature, buff);*/
  /*sprintf(send0, "d1%d%dd2%d%da%d%d%d%dg%d", valueDHTA.Humidity, valueDHTA.Temperature, valueDHTB.Humidity,
    valueDHTB.Temperature, ampe/1000, ampe/100%10, ampe/10%10, ampe%10, get_t);*/

  String send0 = String("triet,") + valueDHTA.Humidity + "," + valueDHTA.Temperature + "," +  valueDHTB.Humidity + "," +
                 valueDHTB.Temperature + "," + String(ampe) + ",ta\n";

  Serial3.print(send0);
  Serial.print(send0);
}

void loop()
{
  if (mq_th.shouldRun())
    mq_th.run();

  blinkBuzz();

  if (uart_th.shouldRun())
    uart_th.run();

  if (amp_th.shouldRun())
    amp_th.run();

  if (dht1_th.shouldRun())
    dht1_th.run();

  if (dht2_th.shouldRun())
    dht2_th.run();

  if (key_th.shouldRun())
    key_th.run();

  if (millis() - send_millis >= 1000) {
    //cp_rev = false;
    //delay(500);
    sendS();
    Serial3.flush();
    //cp_rev = true;
    send_millis = millis();
  }
}

void cKey()
{
  c_TH = getKeyPW();
  if (c_TH != NO_KEY)
  {
    if (c_TH == '1') {
      sLed1W_A = 0;
    }
    if (c_TH == '2') {
      sLed1W_A = 1;
    }
    if (c_TH == '3') {
      sLed1W_A = 2;
    }
    if (c_TH == 'A') {
      sLed1W_A = 3;
    }

    if (c_TH == '4') {
      sLed1W_B = 0;
    }
    if (c_TH == '5') {
      sLed1W_B = 1;
    }
    if (c_TH == '6') {
      sLed1W_B = 2;
    }
    if (c_TH == 'B') {
      sLed1W_B = 3;
    }

    if (c_TH == '7') {
      sLed_A = !sLed_A;
    }
    if (c_TH == '8') {
      sLed_B = !sLed_B;
    }
    if (c_TH == '9') {
      sLed_C = !sLed_C;
    }
    if (c_TH == 'C') {
      sRelay = !sRelay;
    }
  }
}

void blinkBuzz()
{
  if (stateBuzz && ((millis() - buzz_millis) > 500))
  {
    x = !x;
    digitalWrite(buzzer, x);
    buzz_millis = millis();
  }
  else if (!stateBuzz)
  {
    digitalWrite(buzzer, 0);
    buzz_millis = millis();
    sim_tt = false;
    serial1.flush();
  }

  if (stateBuzz == true && sim_tt == false) {
    serial1.println("atd0961475262;");
    sim_tt = true;
  }
}
