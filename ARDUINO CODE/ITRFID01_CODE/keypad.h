#ifndef KEYPAD_H
#define KEYPAD_H
#define R0 23
#define R1 25
#define R2 27
#define R3 29
#define C0 31
#define C1 33
#define C2 35
#define C3 37
void key_reset();
volatile char keyValue = 'x';
char Reset = 'x';
void key_reset()
{
  keyValue = 'x';
}
void keypad_init()
{
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(C0, INPUT_PULLUP);
  pinMode(C1, INPUT_PULLUP);
  pinMode(C2, INPUT_PULLUP);
  pinMode(C3, INPUT_PULLUP);
}


char key() {

  digitalWrite(R0, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '1';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '2';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '3';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'A';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '4';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '5';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '6';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'B';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(R3, HIGH);

  if (digitalRead(C0) == LOW) {
    keyValue = '7';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '8';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '9';

  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'C';

  }
  digitalWrite(R0, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, LOW);

  if (digitalRead(C0) == LOW) {
    keyValue = '*';

  }
  if (digitalRead(C1) == LOW) {
    keyValue = '0';

  }
  if (digitalRead(C2) == LOW) {
    keyValue = '#';
  }
  if (digitalRead(C3) == LOW) {
    keyValue = 'D';
  }
  return keyValue;
}
#endif
