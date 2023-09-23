#ifndef GSM_H
#define GSM_H

char garray[10];
char marray[10];
char mob_no[5][11] = {"8189988347", "8099552677", "8189988347", "8189988347", "8189988347"};
void send_sms(int number, String text );
long int ph = 0;
extern int mob[10];
char ph_c[11];

void send_sms(int number, String text)
{
  for (int i = 0; i < 10; i++)
  {
    garray[i] = mob_no[number - 1][i];
  } 
  delay(2000);
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000); 
  Serial.println("AT+CMGS=\"+91"+String(garray)+"\"\r");
  delay(1000);
  Serial.println(text);
  delay(1000);
  Serial.println(char(26));
  delay(1000);
}
#endif
