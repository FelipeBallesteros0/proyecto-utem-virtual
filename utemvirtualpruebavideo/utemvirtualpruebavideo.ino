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

const int stepX = 2;
const int dirX  = 5;
const int stepY = 3;
const int dirY  = 6;
const int stepZ = 4;
const int dirZ  = 7;
const int enPin = 8;

int angulo,anguloactual,n,npasos;
float pasosporangulo = 0.102857142 ;//360/400

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();

  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);
  pinMode(stepY,OUTPUT);
  pinMode(dirY,OUTPUT);
  pinMode(stepZ,OUTPUT);
  pinMode(dirZ,OUTPUT);
  pinMode(enPin,OUTPUT);

  digitalWrite(enPin,LOW);
  digitalWrite(dirX,HIGH);
  digitalWrite(dirY,HIGH);
  digitalWrite(dirZ,HIGH);
  
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
   vgx41 = vgx4;

//   angulo = integral*2.4;
     angulo = -integral*6;

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

        for(int x = 0; x < npasos; x++) {
           digitalWrite(stepX,HIGH);
           delayMicroseconds(1000);
           digitalWrite(stepX,LOW);
           delayMicroseconds(1000);
        }
        anguloactual = angulo;
    }


   
   Serial.print(angulo,10);
   Serial.println();
   
  }






















  
