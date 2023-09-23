#ifndef IOT_H
#define IOT_H
#include"soft.h"
void iot_send(String text)
{
  for (int i = 0; i < text.length(); i++)
  {
    Serial2.write(text[i]);
  }
}
#endif
