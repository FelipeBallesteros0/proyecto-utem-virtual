#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax(0.355,0.355,0.09);

float t,dt;

float vgx = 0;
float vgx2 = 0;
float vgx3 = 0;
float vgx4 = 0;

float vgx41 = 0;

float integral = 0;

float offsetx;

const int stepX = 2;
const int dirX  = 5;
const int stepY = 3;
const int dirY  = 6;
const int stepZ = 4;
const int dirZ  = 7;
const int enPin = 8;

int angulo,anguloactual,n,npasos;
float pasosporangulo = 0.9 ;//360/400

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();

  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);

  pinMode(enPin,OUTPUT);

  digitalWrite(enPin,LOW);
  digitalWrite(dirX,HIGH);


for (int i = 0; i <= 1000; i++) {
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kax.updateEstimate(vgx);
   }
   offsetx = vgx2;
  
  delay(200);
}

void loop() {
   t = millis();
   delay(200);
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kax.updateEstimate(vgx) - offsetx;
   vgx2 = inverseconstrain(-0.5,0.5,0,vgx2);
   dt = (millis() - t)/1000;
   integral = integral + (dt/2) * (vgx41 + vgx2);
   vgx41 = vgx4;

     angulo = -integral*5.6;

       if( anguloactual != angulo ){

        if( anguloactual < angulo){
            digitalWrite(dirX,HIGH);
             n = angulo - anguloactual;
            npasos = n / pasosporangulo;
        }

        else if( anguloactual > angulo){
            digitalWrite(dirX,LOW);
            n = anguloactual - angulo;
            if( angulo == 0){
               n =anguloactual;
            }
            npasos = n / pasosporangulo;
        }

        for(int x = 0; x < npasos*8.75; x++) {
           digitalWrite(stepX,HIGH);
           delayMicroseconds(1000);
           digitalWrite(stepX,LOW);
           delayMicroseconds(1000);
        }
        anguloactual = angulo;
    }

   Serial.print(integral,10);
   Serial.println();
   
  }



  float inverseconstrain(float limiteinferior,float limitesuperior,float valordentrodelumbral,float valorentrada){
  float valorsalida;

  if ( limiteinferior < valorentrada && valorentrada < limitesuperior) {
  valorsalida = valordentrodelumbral;
  }
  else {
  valorsalida = valorentrada;
  }
  return valorsalida;
  }
