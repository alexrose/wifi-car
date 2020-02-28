#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// Define used pins
#define MOTOR_FRONT_PWM D5
#define MOTOR_FRONT_DIR D6
#define MOTOR_REAR_PWM D2
#define MOTOR_REAR_DIR D3

// Blynk token
char auth[] = "7cba3879268f4ec7ab5a6422cd48fe1e";
char ssid[] = "BeastCarAP";
char pass[] = "b00p";
bool isConnected = false;

void setup()
{
  Serial.begin(115200);

  WiFiManager wifiManager;
  if (!wifiManager.autoConnect(ssid, pass)) {
    Serial.println("I forgot how to wifi.");
    delay(1000);
  }
 
  pinMode(MOTOR_FRONT_PWM, OUTPUT);
  pinMode(MOTOR_FRONT_DIR, OUTPUT);
  pinMode(MOTOR_REAR_PWM, OUTPUT);
  pinMode(MOTOR_REAR_DIR, OUTPUT);
  
  digitalWrite(MOTOR_FRONT_PWM, LOW);
  digitalWrite(MOTOR_FRONT_DIR, LOW);
  digitalWrite(MOTOR_REAR_PWM, LOW);
  digitalWrite(MOTOR_REAR_DIR, LOW);

  Blynk.config(auth);
  Blynk.connect();
}

BLYNK_WRITE(V1) {
  int x = param.asInt();
  
  // FRONT MOTOR
  if (x < 40) {
    analogWrite(MOTOR_FRONT_PWM, 0);
    analogWrite(MOTOR_FRONT_DIR, 1024);
  }
  
  if (x > 60) {
    analogWrite(MOTOR_FRONT_PWM, 1024);
    analogWrite(MOTOR_FRONT_DIR, 0);
  }

  if (x >= 40 && x <= 60) {
    analogWrite(MOTOR_FRONT_PWM, 1024);
    analogWrite(MOTOR_FRONT_DIR, 1024);
  }
}

BLYNK_WRITE(V2) {
  int y = param.asInt();
  
  // BACKWARD
  if (y >= 0 && y < 10) {
    analogWrite(MOTOR_REAR_PWM, 0);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }

  if (y >= 10 && y < 20) {
    analogWrite(MOTOR_REAR_PWM, 200);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }

  if (y >= 20 && y < 30) {
    analogWrite(MOTOR_REAR_PWM, 400);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }

  if (y >= 30 && y < 40) {
    analogWrite(MOTOR_REAR_PWM, 600);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }

  if (y >= 40 && y < 50) {
    analogWrite(MOTOR_REAR_PWM, 800);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }
  
  // STOP
  if (y == 50) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 1024);
  }

  // FORWARD
  if (y > 50 && y <= 60) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 800);
  }

  if (y > 60 && y <= 70) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 600);
  }

  if (y > 70 && y <= 80) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 400);
  }

  if (y > 80 && y <= 90) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 200);
  }

  if (y > 90 && y <= 100) {
    analogWrite(MOTOR_REAR_PWM, 1024);
    analogWrite(MOTOR_REAR_DIR, 0);
  }
}


void loop()
{
  Blynk.run();
}
