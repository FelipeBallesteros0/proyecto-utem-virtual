#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;
SimpleKalmanFilter simpleKalmanFilter( 2, 2, 0.01);

int gx1,gx2,anguloy1,anguloy2,anguloz1,anguloz2;

int uk,ve2,ve3,integral2;
float t,dt,ve,integral;
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
   t = micros();
   
   mySensor.gyroUpdate();
   ve = mySensor.gyroX();
   ve2 = simpleKalmanFilter.updateEstimate(ve) + 3;
   
   dt = (micros() - t)/100000;
   
   integral = integral + (ve2*dt);
   integral2 = integral/9.5;
   
   Serial.println(integral2);
//   Serial.print("_");
//   Serial.print(ve2);
//   Serial.print("_");
//   Serial.println(dt);
   
  }







  
