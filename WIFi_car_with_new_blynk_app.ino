
#define BLYNK_TEMPLATE_ID "TMPL355n_8lRJ"
#define BLYNK_TEMPLATE_NAME "smartcar"
#define BLYNK_AUTH_TOKEN "5jU30urC-rjeCdOV1-fbeGnWqiup5717"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Servo.h>
#include<SoftwareSerial.h>
SoftwareSerial t(1,3);


Servo servo1;



#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D7


int x = 50;
int y = 50;
int Speed;


char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Galaxy M21E1FB";
char pass[] = "ctcd1215"; 


void setup() {
  Serial.begin(9600);
  //Set motor pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  t.begin(9600);

  servo1.attach(14);
  //servo2.attach(12);
}


BLYNK_WRITE(V0) {
  x = param[0].asInt();
}

BLYNK_WRITE(V1) {
  y = param[0].asInt();
}

BLYNK_WRITE(V3)

{
   int pos1=param.asInt();
    t.write(pos1);
   servo1.write(pos1);
}
/*BLYNK_WRITE(V4)

{
  int pos2=param.asInt();
   servo2.write(pos2);
}*/



void smartcar() {
  if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();
  smartcar();
  //t.write("0");
  //delay(1000);
  //t.write("1");
  //delay(1000);
}




void carForward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carBackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carLeft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carRight() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
