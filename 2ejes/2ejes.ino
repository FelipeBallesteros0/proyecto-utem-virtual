#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax(0.355,0.355,0.09);
SimpleKalmanFilter kay(0.355,0.355,0.09);
SimpleKalmanFilter kaz(0.355,0.355,0.09);

const int xdir = 5;//pin 5
const int xstep = 2;//pin 2
const int ydir = 6;
const int ystep = 3;
const int zdir = 7;
const int zstep = 4;

const int xlim = 9;
const int xpasos = 0;
int xct = 0;
int npasosx = 0;

const int ylim = 10;
const int ypasos = 0;
int yct = 0;
int npasosy = 0;

const int zlim = 11;
const int zpasos = 0;
int zct = 0;
int npasosz = 0;

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

float offsetx;
float offsety;
float offsetz;

float t,dt;

float vgx = 0;
float vgx2 = 0;
float vgx41 = 0;
float pgx = 0;

float vgy = 0;
float vgy2 = 0;
float vgy41 = 0;
float pgy = 0;

float vgz = 0;
float vgz2 = 0;
float vgz41 = 0;
float pgz = 0;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  bme.begin();
  mySensor.beginGyro();
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  pinMode(xdir,OUTPUT);
  pinMode(xstep,OUTPUT);
  pinMode(xlim,INPUT_PULLUP);

  pinMode(ydir,OUTPUT);
  pinMode(ystep,OUTPUT);
  pinMode(ylim,INPUT_PULLUP);

  pinMode(zdir,OUTPUT);
  pinMode(zstep,OUTPUT);
  pinMode(zlim,INPUT_PULLUP);

  digitalWrite(xdir,HIGH);
  digitalWrite(ydir,HIGH);
  digitalWrite(zdir,HIGH);

  delay(200);
///////empieza calculo del offset
for (int i = 0; i <= 100; i++) {
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgy = mySensor.gyroX();
   vgz = mySensor.gyroY();
   vgx2 = kax.updateEstimate(vgx);
   vgy2 = kay.updateEstimate(vgy);
   vgz2 = kaz.updateEstimate(vgz);
   }
   
   offsetx = vgx2;
   offsety = vgy2;
   offsetz = vgz2;

  delay(200);

    Serial.println(offsetx);    
    Serial.println("offsetx");
    Serial.println(offsety);    
    Serial.println("offsety");
    Serial.println(offsetz);    
    Serial.println("offsetz");
    
  delay(200);
///////termina calculo del offset
///////empieza calibracion x   
      while(digitalRead(xlim)){
        
        digitalWrite(xstep,HIGH);
        delayMicroseconds(1000);
        digitalWrite(xstep,LOW);
        delayMicroseconds(1000);
    }

  digitalWrite(xdir,LOW);

    for(int x = 0; x < 100; x++) {
           digitalWrite(xstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(1000);
           npasosx += 1;
        }
  
      while(digitalRead(xlim)){
        digitalWrite(xstep,HIGH);
        delayMicroseconds(1000);
        digitalWrite(xstep,LOW);
        delayMicroseconds(1000);
        npasosx += 1;
    }


    digitalWrite(xdir,HIGH);
    for(int x = 0; x < npasosx/2; x++) { //se queda en el punto medio entre los dos finales de carrera
           digitalWrite(xstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(1000);
        }
        
    Serial.println(npasosx);    
    Serial.println("terminox");
    
  delay(200);
///////termina calibracion x
///////empieza calibracion y   
      while(digitalRead(ylim)){
        
        digitalWrite(ystep,HIGH);
        delayMicroseconds(6000);
        digitalWrite(ystep,LOW);
        delayMicroseconds(6000);
    }

  digitalWrite(ydir,LOW);

    for(int x = 0; x < 400; x++) {
           digitalWrite(ystep,HIGH);
           delayMicroseconds(6000);
           digitalWrite(ystep,LOW);
           delayMicroseconds(6000);
           npasosy += 1;
        }
  
      while(digitalRead(ylim)){
        digitalWrite(ystep,HIGH);
        delayMicroseconds(6000);
        digitalWrite(ystep,LOW);
        delayMicroseconds(6000);
        npasosy += 1;
    }


    digitalWrite(ydir,HIGH);
    for(int x = 0; x < npasosy/2; x++) { //se queda en el punto medio entre los dos finales de carrera
           digitalWrite(ystep,HIGH);
           delayMicroseconds(6000);
           digitalWrite(ystep,LOW);
           delayMicroseconds(6000);
        }
        
    Serial.println(npasosy);    
    Serial.println("terminoy");
    
  delay(200);
///////termina calibracion y
///////empieza calibracion z   
      while(digitalRead(zlim)){
        
        digitalWrite(zstep,HIGH);
        delayMicroseconds(1000);
        digitalWrite(zstep,LOW);
        delayMicroseconds(1000);
    }

  digitalWrite(zdir,LOW);

    for(int x = 0; x < 400; x++) {
           digitalWrite(zstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(zstep,LOW);
           delayMicroseconds(1000);
           npasosz += 1;
        }
  
      while(digitalRead(zlim)){
        digitalWrite(zstep,HIGH);
        delayMicroseconds(1000);
        digitalWrite(zstep,LOW);
        delayMicroseconds(1000);
        npasosz += 1;
    }


    digitalWrite(zdir,HIGH);
    for(int x = 0; x < npasosz/2; x++) { //se queda en el punto medio entre los dos finales de carrera
           digitalWrite(zstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(zstep,LOW);
           delayMicroseconds(1000);
        }
        
    Serial.println(npasosz);    
    Serial.println("terminoz");
    
  delay(200);
///////termina calibracion z
}

void loop() {
   t = millis();
   delay(200);
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgy = mySensor.gyroX();
   vgx2 = kax.updateEstimate(vgx) - offsetx;
   vgy2 = kay.updateEstimate(vgy) - offsety;
   vgx2 = inverseconstrain(-0.5,0.5,0,vgx2);
   vgy2 = inverseconstrain(-0.5,0.5,0,vgy2);
   dt = (millis() - t)/1000;
   pgx = pgx + (dt/2) * (vgx41 + vgx2);
   pgy = pgy + (dt/2) * (vgy41 + vgy2);
   vgz41 = vgz2;
   vgy41 = vgy2;

   anglex = -pgx;
   angley = -pgy;

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

        for(int x = 0; x < numstepy*6; x++) {
           digitalWrite(ystep,HIGH);
           delayMicroseconds(3000);
           digitalWrite(ystep,LOW);
           delayMicroseconds(3000);
        }
        currentAngley = angley;
    }
////////////termina el motor y
//Serial.print(vgx2,5);    
//Serial.print("___");
//Serial.print(vgy2,5);    
//Serial.print("___");
//Serial.println(vgz2,5); 
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
