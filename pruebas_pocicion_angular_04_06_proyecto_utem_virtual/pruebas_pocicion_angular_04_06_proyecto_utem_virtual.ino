#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;
SimpleKalmanFilter simpleKalmanFilter(2, 2, -0.002);

float ukx,uky,ukz;

float t,dt;
float ukx1 = 0;
float uky1 = 0;
float ukz1 = 0;
float vex=0;
float vey=0;
float vez=0;
float integralx=0;
float integraly=0;
float integralz=0;

const float g = 9.780327;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
//  mySensor.beginAccel();
  delay(200);
}

void loop() {
   
   dt = 0.01;
   mySensor.gyroUpdate();

//     ukx = mySensor.gyroX()+ 0.96;
//     uky = mySensor.gyroY()+ 0.96;
//     ukz = mySensor.gyroZ()+ 0.96;
     
   vex = mySensor.gyroX();
   ukx = simpleKalmanFilter.updateEstimate(simpleKalmanFilter.updateEstimate(vex)) + 0.98;

   vey = mySensor.gyroY();
   uky = simpleKalmanFilter.updateEstimate(simpleKalmanFilter.updateEstimate(vey)) + 0.98;

   vez = mySensor.gyroZ();
   ukz = simpleKalmanFilter.updateEstimate(simpleKalmanFilter.updateEstimate(vez)) + 0.98;

//   integralx = integralx + (dt/2) * (ukx1 + ukx);
//   integraly = integraly + (dt/2) * (uky1 + uky);
//   integralz = integralz + (dt/2) * (ukz1 + ukz);

   integralx = integralx + (ukx*dt);
   integraly = integraly + (uky*dt);
   integralz = integralz + (ukz*dt);
   
   ukx1 = ukx;
   uky1 = uky;
   ukz1 = ukz;
   
   Serial.print(integralx);
   Serial.print("__");
   Serial.print(integraly);
   Serial.print("__");
   Serial.print(integralz);

   Serial.print("__");
   Serial.print(ukx);
   Serial.print("__");
   Serial.print(uky);
   Serial.print("__");
   Serial.println(ukz);
   
//   Serial.print(ukx,10);
//   Serial.print("__");
//   Serial.print(uky,10);
//   Serial.print("__");
//   Serial.println(ukz,10);

   delay(10);
  }
