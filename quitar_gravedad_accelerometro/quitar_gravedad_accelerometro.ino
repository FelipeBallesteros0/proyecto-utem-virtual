#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

//SimpleKalmanFilter kax( 0.3, 0.3, 0.9);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginAccel();
  delay(200);
}

void loop() {
  mySensor.accelUpdate();
  
float     aax = mySensor.accelX();
float     aay = mySensor.accelY();
float     aaz = mySensor.accelZ();
float     ra = mySensor.accelSqrt();
     
float     aax3 = aax - (aax/ra);
float     aay3 = aay - (aay/ra);
float     aaz3 = aaz - (aaz/ra);

     Serial.print(aax3);
     Serial.print(",");
     Serial.print(aay3);
     Serial.print(",");
     Serial.print(aaz3);
     Serial.println();
     delay(10);
}
