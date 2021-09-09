#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);

int angulox1,angulox2,anguloy1,anguloy2,anguloz1,anguloz2;
//int cx1,cx2,cx3,cx4;

int gx1;
int ve,ve2,ve3;
int t,acc,vel,pos,dt;

const float g = 9.780327;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
  mySensor.beginAccel();
}

void loop() {

   mySensor.gyroUpdate();
   ve = mySensor.gyroX();
   ve2 = simpleKalmanFilter.updateEstimate(mySensor.gyroX());
// ve2 = simpleKalmanFilter.updateEstimate(mySensor.gyroX()) + 3;

  Serial.print(ve);
  Serial.print(",");
  Serial.println(ve2);
  
  }
