#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>

Adafruit_BMP280 bme; // I2C
MPU9250_asukiaaa mySensor;
float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ, gxv, gyv, gzv;

int angulox1, angulox2;

void setup() {
  Serial.begin(9600);
  while (!Serial);

#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
#endif

  bme.begin();
//  mySensor.beginAccel();
  mySensor.beginGyro();


  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
}

void loop() {

//  if (mySensor.accelUpdate() == 0) {
//    aX = mySensor.accelX();
//    aY = mySensor.accelY();
//    aZ = mySensor.accelZ();
//    aSqrt = mySensor.accelSqrt();
//    Serial.print("accelX: " + String(aX));
//    Serial.print("\taccelY: " + String(aY));
//    Serial.print("\taccelZ: " + String(aZ));
//    Serial.print("\taccelSqrt: " + String(aSqrt));
//  }

  if (mySensor.gyroUpdate() == 0) {

    for (int i = 0; i <= 100; i++) {
    angulox1 = 3 + round(mySensor.gyroX());
    angulox1 = angulox1 + 3 + round(mySensor.gyroX());
  }
    angulox2 = angulox2 + angulox1;



    Serial.println(angulox2/490);

    //Serial.print(" gyroY: " + String(anguloy));
    //Serial.print("gyroZ: " + String(anguloz));
  }

  //Serial.println(""); // Add an empty line
//  delay(100);
  }






//funciones

  int inverseconstrain(int limitesuperior,int limiteinferior,int valordentrodelumbral,int valorentrada){
  int valorsalida;

  if (valorentrada > limitesuperior || limiteinferior < valor entrada) {
  valorsalida = valoentrada;
  }
  else {
  valorsalida = valordentrodelumbral;
  }
  return valorsalida;
  }
