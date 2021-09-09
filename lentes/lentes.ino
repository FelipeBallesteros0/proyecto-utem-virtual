#include <SoftwareSerial.h>

SoftwareSerial HC12(2,3);
bool estado1 = LOW;
bool estado2 = LOW;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
}

void loop() {
if (Serial.available()) {        // If HC-12 has data
    
    char texto = Serial.read();
        switch (texto) {
          
  case '1':
    estado1 = digitalRead(9);
    digitalWrite(9,!estado1);
    break;
  
  case '2':
    estado2 = digitalRead(8);
    digitalWrite(8,!estado2);
    break;
    }
   }
  }
