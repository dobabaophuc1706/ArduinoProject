#include <Servo.h>
Servo myServo;
int servoPin = 10;
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(4, 3);  // TX, RX
DFRobotDFPlayerMini myDFPlayer;
int pos = 0;

#define thungracday 9
#define bom 8

const int motorA1 = 7;  // kết nối chân IN1 với chân 7 arduino
const int motorA2 = 6;  // kết nối chân IN2 với chân 6 arduino

const int trig = 12;  // chân trig của HC-SR04
const int echo = 11;  // chân echo của HC-SR04

float GetDistance() {
  unsigned long duration;  // biến đo thời gian
  int distanceCm;          // biến lưu khoảng cách

  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(2);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distanceCm = int(duration / 2 / 29.412);
  delay(10);

  return distanceCm;
}

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(150);
  pinMode(thungracday, INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(bom, INPUT);
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);   // chân echo sẽ nhận tín hiệu
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {
    while (true) {
      delay(0);
    }
  }
  myDFPlayer.volume(30);  // cài đặt âm lượng từ 0-30
  myDFPlayer.play(1);
  delay(1500);  // khi cắm điện thì âm thanh khởi động được kích hoạt (bài 1)
}

void loop() {
  long distance = GetDistance();

  if ((distance < 25) && (digitalRead(thungracday) == HIGH)) {
    mo_thung_rac();
    am_thanh_mo_thung_rac();
    delay(4000);  // thời gian nắp thùng rác mở là 4s
    dong_thung_rac();
    am_thanh_dong_thung_rac();
  }

  if ((distance < 25) && (digitalRead(thungracday) == LOW)) {
    am_thanh_thung_rac_day();  // lựa chọn 1: khi thùng rác đầy thì chỉ phát ra âm thanh và không mở thùng rác
    // mo_thung_rac(); am_thanh_thung_rac_day();    // lựa chọn 2: khi thùng rác đầy thì vẫn mở thùng rác và phát âm thanh thùng rác đầy
  }
  if (digitalRead(bom) == LOW) {
    bom_chay();
    delay(80);
    bom_dung();
    delay(1000);
  }
}

void mo_thung_rac() {
  myServo.write(0);  // Cho servo quay một góc 180 độ
}
void dong_thung_rac() {
  myServo.write(150); // đóng nắp về vị trí ban 
}

void am_thanh_mo_thung_rac()  //khi thùng rác mở thì sẽ phát âm thanh (2)
{
  myDFPlayer.play(2);
  delay(1300);
}

void am_thanh_dong_thung_rac()  //khi thùng rác mở thì sẽ phát âm thanh (3)
{
  myDFPlayer.play(3);
  delay(1300);
}
void am_thanh_thung_rac_day()  //khi thùng rác mở thì sẽ phát âm thanh (4)
{
  myDFPlayer.play(4);
  delay(1300);
}
void bom_chay()  //Điều khiển bơm chạy
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
}
void bom_dung()  //Điều khiển bơm dừng
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
}
