#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kay( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kaz( 0.3, 0.3, 0.9);

const int xdir = 5;
const int xstep = 2;
const int enPin = 8;

float t,dt = 0;

float vgx = 0;
float vgx2 = 0;
float vgx3 = 0;
float vgx21 = 0;

int currentAngle = 0;
int angle = 0;
float stepPerAngle = 0.9;
int numstep;
char texto;

float offsetx;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();

  pinMode(xdir,OUTPUT);
  pinMode(xstep,OUTPUT);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  digitalWrite(xdir,HIGH);

    for (int i = 0; i <= 1000; i++) {
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kax.updateEstimate(vgx);
   }
   offsetx = vgx2;

  
  delay(200);
}

void loop() {
//   t = millis();
////   delay(10);
//   mySensor.gyroUpdate();
//   vgx = mySensor.gyroZ();
//   vgx2 = kax.updateEstimate(vgx);
//   dt = (millis() - t)/1000;
//   vgx3 = vgx3 + (vgx2*dt);
//
//   Serial.print(vgx,10);
//   Serial.print(",");
//   Serial.print(vgx2,10);
//   Serial.println();

  while (Serial.available()) { 
     texto = Serial.read();
//        Serial.println(texto);
  }

   switch (texto) {
  case '1':
  angle = 0;
    break;
  case '2':
  angle = 90;
    break;
//  default:
//  angle = currentAngle;
//    break;
    }

    int n;
    
       if( currentAngle != angle ){

        if( currentAngle < angle){
            digitalWrite(xdir,HIGH);
             n = angle - currentAngle;
            numstep = n / stepPerAngle;
        }

        else if( currentAngle > angle){
            digitalWrite(xdir,LOW);
            n = currentAngle - angle;
            if( angle == 0){
               n =currentAngle;
            }
            numstep = n / stepPerAngle;
        }

        for(int x = 0; x < numstep*8.75; x++) {
           digitalWrite(xstep,HIGH);
           delayMicroseconds(2000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(2000);

   t = millis();
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kax.updateEstimate(vgx) - offsetx;
   dt = (millis() - t)/1000;
//   vgx3 = vgx3 + (vgx2*dt);
   vgx3 = vgx3 + (dt/2)*(vgx2 + vgx21);
   vgx21 = vgx2;
   
   Serial.print(vgx3,10);
//   Serial.print(",");
//   Serial.print(vgx2,10);
   Serial.println();
           
        }
        currentAngle = angle;
    }
//   delay(500);
}
