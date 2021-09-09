//#include <MPU9250_asukiaaa.h>
//#include <Adafruit_BMP280.h>
#include <math.h>
//#include <SimpleKalmanFilter.h>

//Adafruit_BMP280 bme;
//MPU9250_asukiaaa mySensor;

//SimpleKalmanFilter kax( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kay( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kaz( 0.3, 0.3, 0.9);

//float t,dt,t2,dt2 = 0;

//float vgx = 0;
//float vgx2 = 0;
//float vgx3 = 0;
//float vgx21 = 0;

//float offsetx;

const int xdir = 5;//pin 5
const int xstep = 2;//pin 2
const int ydir = 6;
const int ystep = 3;
const int zdir = 7;
const int zstep = 4;

const int enPin = 8;

int currentAnglex = 0;
int anglex = 0;
float stepPerAnglex = 0.9;
int numstepx;
int nx;

int currentAngley = 0;
int angley = 0;
float stepPerAngley = 0.9;
int numstepy;
int ny;

int currentAnglez = 0;
int anglez = 0;
float stepPerAnglez = 0.9;
int numstepz;
int nz;

void setup() {
  Serial.begin(115200);
//  while (!Serial);
//  bme.begin();
//  mySensor.beginGyro();
  
  pinMode(xdir,OUTPUT);
  pinMode(xstep,OUTPUT);
  pinMode(ydir,OUTPUT);
  pinMode(ystep,OUTPUT);
  pinMode(zdir,OUTPUT);
  pinMode(zstep,OUTPUT);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  digitalWrite(xdir,HIGH);
  digitalWrite(ydir,HIGH);
  digitalWrite(zdir,HIGH);

  delay(200);
}

void loop() {

if (Serial.available()) {
    char texto = Serial.read();
    
        switch (texto) {
            case '1':
            anglex += 90;
            break;
            
            case '2':
            anglex += -90;
            break;

            case '3':
            angley += 90;
            break;
            
            case '4':
            angley += -90;
            break;

            case '5':
            anglez += 90;
            break;
            
            case '6':
            anglez += -90;
            break;
          }

////////aca empieza el motor x
       if( currentAnglex != anglex ){

        if( currentAnglex < anglex){
            digitalWrite(xdir,HIGH);
             nx = anglex - currentAnglex;
            numstepx = nx / stepPerAnglex;
        }

        else if( currentAnglex > anglex){
            digitalWrite(xdir,LOW);
            nx = currentAnglex - anglex;
            if( anglex == 0){
               nx = currentAnglex;
            }
            numstepx = nx / stepPerAnglex;
        }

        for(int x = 0; x < numstepx*8.75; x++) {
           digitalWrite(xstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(1000);
        }
        currentAnglex = anglex;
    }
/////////////termina el motor x
/////////////aca empieza el motor y
          if( currentAngley != angley ){

        if( currentAngley < angley){
            digitalWrite(ydir,HIGH);
             ny = angley - currentAngley;
            numstepy = ny / stepPerAngley;
        }

        else if( currentAngley > angley){
            digitalWrite(ydir,LOW);
            ny = currentAngley - angley;
            if( angley == 0){
               ny = currentAngley;
            }
            numstepy = ny / stepPerAngley;
        }

        for(int x = 0; x < numstepy; x++) {
           digitalWrite(ystep,HIGH);
           delayMicroseconds(3000);
           digitalWrite(ystep,LOW);
           delayMicroseconds(3000);
        }
        currentAngley = angley;
    }
////////////termina el motor y
/////////////aca empieza el motor z
          if( currentAnglez != anglez ){

        if( currentAnglez < anglez){
            digitalWrite(zdir,HIGH);
             nz = anglez - currentAnglez;
            numstepz = nz / stepPerAnglez;
        }

        else if( currentAnglez > anglez){
            digitalWrite(zdir,LOW);
            nz = currentAnglez - anglez;
            if( anglez == 0){
               nz = currentAnglez;
            }
            numstepz = nz / stepPerAnglez;
        }

        for(int x = 0; x < numstepz; x++) {
           digitalWrite(zstep,HIGH);
           delayMicroseconds(3000);
           digitalWrite(zstep,LOW);
           delayMicroseconds(3000);
        }
        currentAnglez = anglez;
    }
////////////termina el motor y
                   
}

//delay(1000);
}
