#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax( 0.3, 0.3, 0.9);

int nDEC = 100000;

const float g = 9.780327;
float dt = 0.01;
float ra = 0;

float aax = 0;
float aax2 = 0;
float aax3 = 0;

float vax = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginAccel();
  delay(200);
}

void loop() {
  
   mySensor.accelUpdate();
   aax = mySensor.accelX();
   ra = mySensor.accelSqrt();
   
//   aax2 = aax - (aax/ra);
   aax2 = aax2*g;

   aax3 = kax.updateEstimate(aax2);

//   aax3 = round(aax2*nDEC);
//   aax3 = (aax3/nDEC) + 0.01;

   vax = vax + (aax3*dt);
//   vax = vax*1000;
//   vax =  vax + ((dt/2) * (aax2 + aax21));
//   aax21 = aax2;
   
//   pax = pax + ((dt/2) * (vax + vax1));

//   pax = pax + vax*dt;
//   vax1 = vax;
   
//   Serial.print(pax*100,10);
//   Serial.print(",");
//   Serial.print(aax,10);
//   Serial.print(",");
   Serial.print(aax2,10);
   Serial.print(",");
   Serial.print(aax3,10);
//   Serial.print(",");
//   Serial.print(vax,10);
   Serial.println();
   
   delay(10);
  }
