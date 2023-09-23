/********************************
  PROJECT CODE:RFID02 UNO
  DATE:05.05.2022
  STATUS :COMPLETED AND WORKING CODE


*/
#include "face.h"
#include"lcd.h"
#include"keypad.h"
#include"rfid.h"
#include"gsm.h"
#include"fingermatch.h"
#include"iot.h"
#include"soft.h"
extern volatile char key_value;
int r_id = 0;
int f_id = 0;
int fc_id = 0;
int voted_status[4] = {0, 0, 0, 0};
int dmk, admk, bjp, nota = 0;
bool polling_status = false;
bool iot_poll = false;
#define iot_status 5
bool fa_id = false, fa_id1 = false;
int count_g = 0;

//void fin();
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" VOTING7 ");
  delay(1000);
  //lcd.backlight();
  Serial2.begin(9600);
  //finger_init();
  Serial3.begin(9600);
  // A mySerial.begin(9600);
  //  iot.begin(9600);
  keypad_init();
  pinMode(iot_status, INPUT_PULLUP);


}
void loop() {
  //  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print(" VOTING ");
  reset_poll();
  iot_state();
  rfid_check();
  vote_check();
  //    Serial.println(key());
  //  delay(1000);
  // getFingerprintID();
}

void reset_poll()
{
  f_id = 0;
  rfidno = 0;
  fc_id = 0;
  keyValue = 'x';
}
void iot_state()
{
  //  while (Serial2.available() > 0)
  //  {
  //    char c = Serial2.read();
  if (digitalRead(iot_status) == 0)
  {
    iot_poll = true;
  }

  if (digitalRead(iot_status) == 1)
  {
    iot_poll = false;
  }
}

void rfid_check()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLACE VOTER ID");
  do {
    iot_state();
    rfid();
  }
  while (rfid() == 0);
  lcd.setCursor(0, 1);
  lcd.print(rfidno);
  r_id = rfidno;
  face_check();
  delay(2000);

}

void face_check()
{
  fid = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SHOW FACE");
  do {
    iot_state();
    py();
  }
  while (py() == 0);
  lcd.setCursor(0, 1);
  lcd.print(fid);
  fc_id = fid;
  delay(2000);
  if ((r_id == 5) && (fc_id == 5))
  {
    po_ui();
  }
  else if ((fc_id == r_id) || (fc_id == 5))
  {
    voting_ui();
  }
}




void vote_check()
{

  if (r_id != 5 && fc_id != 5) {
    iot_state();
    //face_reset();
    if ((polling_status == true) && (iot_poll == true))
    {
      if ((voted_status[r_id - 1]) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("welcome");
        lcd.setCursor(0, 1);
        lcd.print("PERSON:");
        lcd.print(r_id);
        //        if (fc_id == r_id)
        //        {
        //          fid_check();
        //        }
        //        else
        //        {
        //          lcd.clear();
        //          lcd.setCursor(0, 0);
        //          lcd.print("FACE ID MISMATCH");
        //          iot_send("*FACE ID MISMATCH#");
        //          send_sms(r_id, "FACE ID MISMATCH");
        //          delay(2000);
        //          polling_status = false;
        //          rfid_check();
        //        }
        delay(2000);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ALREADY VOTED");
        lcd.setCursor(0, 1);
        lcd.print("PERSON:");
        lcd.print(r_id);
        iot_send("*PERSON_" + String(r_id) + "ALREADY_VOTTED#");
        send_sms(r_id, "ALREADY VOTED");
        delay(2000);
      }
    }
    else if ((polling_status == true) && (iot_poll == false))
    { lcd.clear();
      lcd.setCursor(0, 0);
      iot_send("*POLLING_STOPPED#");
      lcd.setCursor(0, 0);
      lcd.print("BOOTH START");
      lcd.setCursor(0, 1);
      lcd.print("IOT STOPPED");
      delay(2000);
    }
    else if ((polling_status == false) && (iot_poll == false))
    {
      lcd.clear();
      iot_send("*POLLING_STOPPED#");
      lcd.setCursor(0, 0);
      lcd.print("BOOTH STOPPED");
      lcd.setCursor(0, 1);
      lcd.print("IOT STOPPED");
      delay(2000);
    }
    else if ((polling_status == false) && (iot_poll == true))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BOOTH STOPPED");
      lcd.setCursor(0, 1);
      lcd.print("IOT STARTED");
      iot_send("*POLLING_STOPPED#");

      delay(2000);
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WELCOME PO");
    lcd.setCursor(0, 1);
    lcd.print("PERSON:");
    lcd.print(r_id);
    iot_send("*P.O.LOGGED_IN#");
    delay(2000);
    //    if (fc_id == 5)
    //    {
    //      fid_check();
    //    }
    //    else
    //    {
    //      lcd.clear();
    //      lcd.setCursor(0, 0);
    //      lcd.print("FACE ID MISMATCH");
    //      iot_send("*FACE ID MISMATCH#");
    //      send_sms(r_id, "FACE ID MISMATCH");
    //      delay(2000);
    //      polling_status = false;
    //      rfid_check();
    //    }
  }
}

//void  fid_check()
//{
//
//  do {
//    getFingerprintID();
//  }
//  while (f_id == 0);
//  if ((f_id == 5) && (r_id == 5) && (fc_id == 5))
//  {
//    po_ui();
//  }
//  else if (((f_id == r_id) && (fc_id == f_id)) || (f_id == 5))
//  {
//    voting_ui();
//  }
//  else
//  {
//    lcd.clear();
//    lcd.print("FINGER MISMATCH");
//    lcd.setCursor(0, 1);
//    lcd.print("POLLING STOPPED");
//    iot_send("*FINGER_MISMATCH_POLL_STOPPED#");
//    send_sms(r_id, "FINGER MISMATCH");
//    polling_status = false;
//    delay(2000);
//  }
//}
void voting_ui()
{
  key_reset();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1 DMK");
  lcd.setCursor(8, 0);
  lcd.print("2 ADMK");
  lcd.setCursor(0, 1);
  lcd.print("3 BJP");
  lcd.setCursor(8, 1);
  lcd.print("4 NOTA");
  do {
    key();
  }
  while (key() == Reset);
  voted_status[r_id - 1] = keyValue - '0';
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VOTED SUCCESSFULLY");
  lcd.setCursor(0, 1);
  lcd.print(keyValue);
  lcd.setCursor(5, 1);
  lcd.print(voted_status[r_id - 1]);
  for (int i = 0; i < 4; i++)
    Serial.println(voted_status[i]);
  if (fc_id == 5)
  {
    iot_send("*PERSON" + String(r_id) + "VOTED_SUCCESSFULLY_PO_AUTH#");
    send_sms(r_id, "VOTED_SUCESSFULLY_PO_AUTH");
  }
  if (fc_id == r_id)
  {
    iot_send("*PERSON_" + String(r_id) + "VOTED_SUCESSFULLY#");
    send_sms(r_id, "VOTED SUCESSFULLY");
  }
  delay(2000);
}
void po_ui()
{
  key_reset();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1 TOT");
  lcd.setCursor(6, 0);
  lcd.print("2 PL-STRT");
  lcd.setCursor(0, 1);
  lcd.print("3 PL-STP");
  do {
    key();
  }
  while (key() == Reset);
  if (key() == '1')
  {
    for (int i = 0; i < 4; i++)
    {
      if (voted_status[i] == 1)
        dmk++;
      if (voted_status[i] == 2)
        admk++;

      if (voted_status[i] == 3)
        bjp++;

      if (voted_status[i] == 4)
        nota++;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DMK: ");
    lcd.print(dmk);
    lcd.setCursor(8, 0);
    lcd.print("ADMK:");
    lcd.print(admk);
    lcd.setCursor(0, 1);
    lcd.print("BJP:");
    lcd.print(bjp);
    lcd.setCursor(8, 1);
    lcd.print("NOTA:");
    lcd.print(nota);
    delay(2000);
    dmk = 0;
    admk = 0;
    bjp = 0;
    nota = 0;
  }
  if (key() == '2')
  {
    polling_status = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    iot_send("*POLLING_STARTED_PO#");
    lcd.print("POLLING STARTED");
    delay(2000);
  }
  if (key() == '3')
  {
    polling_status = false;
    lcd.clear();
    lcd.setCursor(0, 0);
    iot_send("*POLLING_STARTED_PO#");
    lcd.print("POLLING STOPED"); delay(2000);
  }
  key_reset();
  face_reset();
}
