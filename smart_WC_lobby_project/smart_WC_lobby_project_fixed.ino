#include <SoftwareSerial.h>

#define CB_MQ A0    // Cảm biến MQ135
#define buzz 9      // Còi hú

void setup() {
  pinMode(CB_MQ, INPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  Serial.begin(9600); 
  delay(1000);
}

void loop() {
  int GT_cbkhoi = digitalRead(CB_MQ);
  delay(100);
  if (GT_cbkhoi == 0) {
    for (int i = 0; i < 10; i++) {
      digitalWrite(buzz, HIGH);
      delay(200);
      digitalWrite(buzz, LOW);
      delay(200);
    }
  } else {
    digitalWrite(buzz,LOW);
  }
}
