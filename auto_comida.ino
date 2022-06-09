#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(2, 3);
Servo servo1;

bool estado1 = LOW;
bool estado2 = LOW;
int angservo = 90;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  servo1.attach(11);
  servo1.write(angservo);
}

void loop() {
  if (Serial.available()) {        // If HC-12 has data

    char texto = Serial.read();
    switch (texto) {

      case '1':
        analogWrite(9, 255);
        analogWrite(10, 0);
        break;

      case '2':
        analogWrite(9, 0);
        analogWrite(10, 255);
        break;

      case '3':
        angservo = angservo + 15;
        angservo = constrain(angservo, 60, 120);
        servo1.write(angservo);

        break;

      case '4':
        angservo = angservo - 15;
        angservo = constrain(angservo, 60, 120);
        servo1.write(angservo);
        break;

      case '5':
        analogWrite(9, 0);
        analogWrite(10, 0);
        break;
    }
  }

  //  else
  //  {
  //    analogWrite(9, 0);
  //    analogWrite(10, 0);
  //  }


}
