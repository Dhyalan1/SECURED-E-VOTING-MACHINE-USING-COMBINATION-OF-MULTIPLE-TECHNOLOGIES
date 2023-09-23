#ifndef PY_H
#define PY_H
char f_data;
int fid = 0;
#include"lcd.h"
void face_reset();
void face_reset()
{
  fid = 0;
}
int py()
{
  while (Serial3.available() > 0)
  {
    f_data = Serial3.read();
    Serial.print(f_data);
    switch (f_data)
    {
      case 'A' : lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE ID:1");
        fid = 1;
        break;
      case 'B' : lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE ID:2");
        fid = 2;
        break;
      case 'C' : lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE ID:3");
        fid = 3;
        break;
      case 'D' : lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE ID:4");
        fid = 4;
        break;
      case 'E' : lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FACE ID:5");
        fid = 5;
        break;
    }
  }
  return fid;
}
#endif
