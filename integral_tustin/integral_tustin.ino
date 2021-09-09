#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);

int gx1,gx2,anguloy1,anguloy2,anguloz1,anguloz2;
//int cx1,cx2,cx3,cx4;

int uk,ve,integral;
int ve3 = 0;

float t,dt;
float uk1 = 0;

const float g = 9.780327;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
  mySensor.beginAccel();
  delay(200);
}

void loop() {
   t = millis();
   
   mySensor.gyroUpdate();
   ve = mySensor.gyroX();
   uk = simpleKalmanFilter.updateEstimate(ve) + 3;

//   dt = (millis() - t)/1000;
   dt = 0.1;
   integral = integral + (dt/2) * (uk1 + uk);

   uk1 = uk;
   
   Serial.print(integral);
   Serial.print("____");
   Serial.print(uk);
   Serial.print("____");
   Serial.println(dt);

   delay(100);
  }
