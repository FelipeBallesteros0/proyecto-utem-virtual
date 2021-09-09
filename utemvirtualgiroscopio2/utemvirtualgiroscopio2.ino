#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;

int angulox1,angulox2,anguloy1,anguloy2,anguloz1,anguloz2;
int cx1,cx2,cx3,cx4;

const float g = 9.780327;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
  mySensor.beginAccel();
}

void loop() {

  if (mySensor.gyroUpdate() == 0) {
    
    for (int i = 0; i <= 100; i++) {
    angulox1 = inverseconstrain(-5,-1,0,mySensor.gyroX());
    angulox1 = angulox1 + inverseconstrain(-5,-1,0,mySensor.gyroX());
  }
    angulox2 = angulox2 + angulox1;


    for (int i = 0; i <= 100; i++) {
    anguloy1 = inverseconstrain(0,2,0,mySensor.gyroY());
    anguloy1 = anguloy1 + inverseconstrain(0,2,0,mySensor.gyroY());
  }
    anguloy2 = anguloy2 + anguloy1;


    for (int i = 0; i <= 100; i++) {
    anguloz1 = inverseconstrain(-1,0,0,mySensor.gyroZ());
    anguloz1 = anguloz1 + inverseconstrain(-1,0,0,mySensor.gyroZ());
  }
    anguloz2 = anguloz2 + anguloz1;
  }

//  if (mySensor.accelUpdate() == 0) {
//
//      for (int i = 0; i <= 100; i++) {
//    cx1 = mySensor.accelX();
//    cx1 = cx1 + mySensor.accelX();
//    }
//    cx2 = cx2 + cx1;
//
//      for (int i = 0; i <= 100; i++) {
//    cx3 = cx2;
//    cx3 = cx3 + cx2;
//    }
//    cx4 = cx4 + cx3;
//  
//  }




  
  Serial.print("angulos_XYZ_");
  Serial.print(angulox2/500);
  Serial.print("_");
  Serial.print(anguloy2/500);
  Serial.print("_");
  Serial.println(anguloz2/500);
  }


    //funciones

  int inverseconstrain(int limiteinferior,int limitesuperior,int valordentrodelumbral,int valorentrada){
  int valorsalida;

  if ( limiteinferior < valorentrada && valorentrada < limitesuperior) {
  valorsalida = valordentrodelumbral;
  }
  else {
  valorsalida = valorentrada;
  }
  return valorsalida;
  }
