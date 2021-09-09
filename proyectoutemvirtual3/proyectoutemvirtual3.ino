#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kgx(1.15,1.15,0.09);
SimpleKalmanFilter kgy( 2, 2, 0.01);// tengo que cambiar estos numeros despues
SimpleKalmanFilter kgz( 2, 2, 0.01);//

float t,dt;

float vgx = 0;
float vgx2 = 0;
float vgx3 = 0;
float vgx4 = 0;

float vgx41 = 0;

float integral = 0;

int nDEC = 1; //numero de decimales, ej: 100 son 2 decimales, 1000 son 3 decimales despues de la coma, 1 es aproximar a la unidad

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
  delay(200);
}

void loop() {
   t = millis();
   
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kgx.updateEstimate(vgx);
   vgx3 = roundf(vgx2*nDEC);
   vgx4 = (vgx3/nDEC) + 1;
   dt = (millis() - t)/1000;

   integral = integral + (dt/2) * (vgx41 + vgx4);
//   integral = integral + (vgx4*dt);

   vgx41 = vgx4;
   
//   Serial.print(integral,10);
//   Serial.print(",");
//   Serial.print(vgx4,10);
//   Serial.print(",");
   Serial.print(integral*2.4,10);
//   Serial.print(",");
//   Serial.print(dt,10);
   Serial.println();
   
  }
