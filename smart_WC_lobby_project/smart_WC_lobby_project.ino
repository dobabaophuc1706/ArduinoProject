//#include <sim900.h>
#include <Servo.h>
Servo myservo;
#include <SoftwareSerial.h>
SoftwareSerial SIM900(2, 3);    // chân 2 arduino nối TX sim800A - chân 3 arduino nối với RX sim800A
String number1 = "0932329328";  // nhập sdt cần gọi vào đây
String val;
int baodong = 0;
int gui = 0;

#define CB_MQ A0    // cảm biến khí ga
#define buzz 9      // còi hú

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
