#ifndef DHT11_H
#define DHT11_H

#include "DHT.h"
const int DHTPIN_1 = 8;
const int DHTPIN_2 = 9;
const int DHTTYPE = DHT11;

DHT dht_1(DHTPIN_1, DHTTYPE);
DHT dht_2(DHTPIN_2, DHTTYPE);

typedef struct
{
  byte Humidity;
  byte Temperature;
} dhtTypeDef;

void dht11_setup()
{
  dht_1.begin();
  dht_2.begin();
}

dhtTypeDef getDHTRoomsA()
{
  dhtTypeDef tmp;
  tmp.Humidity = dht_1.readHumidity();
  tmp.Temperature = dht_1.readTemperature();

  return tmp;
}

dhtTypeDef getDHTRoomsB()
{
  dhtTypeDef tmp;
  tmp.Humidity = dht_2.readHumidity();
  tmp.Temperature = dht_2.readTemperature();

  return tmp;
}

#endif
