#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

//SimpleKalmanFilter kax( 0.3, 0.3, 0.9);

float gx,gy,gz;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginAccel();
  delay(200);
}

void loop() {
  
float     t = millis()/1000;
          mySensor.accelUpdate();
          
float     aax = mySensor.accelX();
float     aay = mySensor.accelY();
float     aaz = mySensor.accelZ();

float     ra = mySensor.accelSqrt();

//float     gx = aax/ra;
//float     gy = aay/ra;
//float     gz = aaz/ra;

float     dt = (millis()/1000) - t;
float     alpha = t/(t + dt);
          
float     aax2 = alpha * gx + (1 - alpha) * aax;
float     aay2 = alpha * gy + (1 - alpha) * aay;
float     aaz2 = alpha * gz + (1 - alpha) * aaz;
     
float     aax3 = aax - aax2;
float     aay3 = aay - aay2;
float     aaz3 = aaz - aaz3;

     Serial.print(aax3);
     Serial.print(",");
     Serial.print(aay3);
     Serial.print(",");
     Serial.print(aaz3);
     Serial.println();
     delay(10);
}
