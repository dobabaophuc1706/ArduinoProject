//#include <sim900.h>
#include <Servo.h>
Servo myservo;
#include <SoftwareSerial.h>
SoftwareSerial SIM900(2, 3);
String number1 = "phone number";  // Thay đổi SĐT
String val;
int baodong = 0;
int gui = 0;

#define CB_MQ A0    // Cảm biến MQ135
#define leddo 4     // Điều khiển LED đỏ
#define ledxanh 5   // Điều khiển LED xanh
#define ledtrang 6  // Điều khiển LED trắng
#define quat 7      // Điều khiển role quạt
#define maybom 8    // Điều khiển role máy bơm
#define buzz 9      // Còi hú
#define CB_IR 10    // Cảm biến hồng ngoại
#define servo 11    // Servo

int dem = 0;

void setup() {
  myservo.attach(servo);
  myservo.write(0);

  pinMode(CB_IR, INPUT);
  pinMode(CB_MQ, INPUT);

  pinMode(quat, OUTPUT);
  pinMode(maybom, OUTPUT);

  pinMode(buzz, OUTPUT);
  pinMode(leddo, OUTPUT);
  pinMode(ledxanh, OUTPUT);
  pinMode(ledtrang, OUTPUT);

  digitalWrite(buzz, LOW);
  digitalWrite(quat, HIGH);
  digitalWrite(maybom, HIGH);
  digitalWrite(ledtrang, LOW);
  digitalWrite(ledxanh, HIGH);
  digitalWrite(leddo, LOW);

  Serial.begin(9600);
  SIM900.begin(9600);
  delay(2000);
  SIM900.print("AT+CLIP=1\r");
  delay(1000);
}

void call() {
  SIM900.print(F("ATD"));
  SIM900.print(number1);
  SIM900.print(F(";\r\n"));
  delay(20000);  //20 sec delay
  SIM900.println("ATH");
  delay(1000);  //1 sec delay
}

void message() {
  SIM900.println("AT+CMGF=1");
  delay(1000);
  SIM900.println("AT+CMGS=\"" + number1 + "\"\r");
  delay(1000);
  String SMS = "CO HOC SINH HUT THUOC TRONG NHA VE SINH";
  SIM900.println(SMS);
  delay(100);
  SIM900.println((char)26);
  delay(1000);
}
void loop() {
  int GT_cbkhoi = digitalRead(CB_MQ);
  int GT_cbxanuoc = digitalRead(CB_IR);
  delay(100);

  if ((GT_cbkhoi == 0) && (gui == 0)) {
    myservo.write(90);
    digitalWrite(quat, LOW);
    digitalWrite(leddo, HIGH);
    for (int i = 0; i < 10; i++) {
      digitalWrite(buzz, HIGH);
      delay(200);
      digitalWrite(buzz, LOW);
      delay(200);
    }
    // Tin nhắn
    // message();
    // Gọi
    call();
    gui = 1;
    baodong = 1;
  }
  if ((GT_cbkhoi == 1) && (gui == 1)) {
    gui = 0;
  }
  if (GT_cbxanuoc == 0) {
    myservo.write(90);
    digitalWrite(ledxanh, LOW);    // Đèn tắt
    digitalWrite(leddo, HIGH);     // Đèn sáng
    digitalWrite(quat, LOW);       // Quạt chạy
    digitalWrite(ledtrang, HIGH);  // Đèn sáng
    delay(100);

    dem = 1;
  }

  if (dem == 1 && GT_cbxanuoc == 1 && baodong == 0) {
    myservo.write(0);
    dem = 0;
    delay(100);
    digitalWrite(maybom, LOW);  // Máy bơm chạy
    delay(1000);
    digitalWrite(maybom, HIGH);   // Máy bơm tắt
    digitalWrite(ledtrang, LOW);  // Đèn tắt
    delay(500);

    digitalWrite(quat, HIGH);     // Quạt tắt
    digitalWrite(ledxanh, HIGH);  // Đèn sáng
    digitalWrite(leddo, LOW);     // Đèn tắt
  }
}
