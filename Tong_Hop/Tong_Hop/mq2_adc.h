#ifndef MQ2_ADC_H
#define MQ2_ADC_H

#define adc_mq2 A1
#define nguong  320

bool getADCMQ2()
{
  int tmp = 0;
  for (byte i = 0; i < 3; i++)
  {
    tmp = tmp + analogRead(adc_mq2);
  }
  tmp = tmp / 3;
  Serial.println("MQ135: " + String(tmp));
  if (tmp > nguong)
  {
    return true;
  }
  return false;
}

#endif
