#ifndef FINGER_MATCH_H
#define FINGER_MATCH_H
#include <Adafruit_Fingerprint.h>
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
extern volatile char key_value;
extern int f_id;

int getFingerprintID()
{
  while (Serial1.available() > 0)
  {
    char f = Serial1.read();
    switch (f)
    {
      case '1' : f_id = 1;
        break;

      case '2' : f_id = 2;
        break;
      case '3' : f_id = 3;
        break;
      case '4' : f_id = 4;
        break;
      case '5' : f_id = 5;
        break;
    }
  }
  return f_id;
}
//void finger_init()
//{
//  finger.begin(57600);
//  while (!Serial);  // For Yun/Leo/Micro/Zero/...
//  delay(100);
//  Serial.println("\n\nAdafruit finger detect test");
//
//  // set the data rate for the sensor serial port
//  finger.begin(57600);
//  delay(5);
//  if (finger.verifyPassword()) {
//    Serial.println("Found fingerprint sensor!");
//  } else {
//    Serial.println("Did not find fingerprint sensor :(");
//    while (1) {
//      delay(1);
//    }
//  }
//
//}
//
//uint8_t getFingerprintID() {
//  uint8_t p = finger.getImage();
//  switch (p) {
//    case FINGERPRINT_OK:
//      Serial.println("Image taken");
//      break;
//    case FINGERPRINT_NOFINGER:
//      Serial.println("No finger detected");
//      return p;
//    case FINGERPRINT_PACKETRECIEVEERR:
//      Serial.println("Communication error");
//      return p;
//    case FINGERPRINT_IMAGEFAIL:
//      Serial.println("Imaging error");
//      return p;
//    default:
//      Serial.println("Unknown error");
//      return p;
//  }
//
//  // OK success!
//
//  p = finger.image2Tz();
//  switch (p) {
//    case FINGERPRINT_OK:
//      Serial.println("Image converted");
//      break;
//    case FINGERPRINT_IMAGEMESS:
//      Serial.println("Image too messy");
//      return p;
//    case FINGERPRINT_PACKETRECIEVEERR:
//      Serial.println("Communication error");
//      return p;
//    case FINGERPRINT_FEATUREFAIL:
//      Serial.println("Could not find fingerprint features");
//      return p;
//    case FINGERPRINT_INVALIDIMAGE:
//      Serial.println("Could not find fingerprint features");
//      return p;
//    default:
//      Serial.println("Unknown error");
//      return p;
//  }
//
//  // OK converted!
//  p = finger.fingerSearch();
//  if (p == FINGERPRINT_OK) {
//    Serial.println("Found a print match!");
//  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//    Serial.println("Communication error");
//    return p;
//  } else if (p == FINGERPRINT_NOTFOUND) {
//    Serial.println("Did not find a match");
//    return p;
//  } else {
//    Serial.println("Unknown error");
//    return p;
//  }
//
//  // found a match!
//  Serial.print("Found ID #"); Serial.print(finger.fingerID);
//  Serial.print(" with confidence of "); Serial.println(finger.confidence);
//  f_id = finger.fingerID;
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("FOUND:");
//  lcd.setCursor(7, 0);
//  lcd.print(finger.fingerID);
//  delay(2000);
//  return finger.fingerID;
//}
//
//// returns -1 if failed, otherwise returns ID #
//int getFingerprintIDez() {
//  uint8_t p = finger.getImage();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  p = finger.image2Tz();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  p = finger.fingerFastSearch();
//  if (p != FINGERPRINT_OK)  return -1;
//
//  // found a match!
//  Serial.print("Found ID #"); Serial.print(finger.fingerID);
//  Serial.print(" with confidence of "); Serial.println(finger.confidence);
//  return finger.fingerID;
//}
#endif
