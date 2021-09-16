#include <math.h>

const int xdir = 13;
const int xstep = 12;
const int ydir = 6;
const int ystep = 3;
const int zdir = 7;
const int zstep = 4;
//const int adir = 13;
//const int astep = 12;

const int enPin = 8;

int currentAnglex = 0;
int anglex = 0;
float stepPerAnglex = 1.8;
int numstepx;

volatile int pasosx = 0;

unsigned long previousMotor1Time = 0;
long Motor1Interval = 1;//tiempo en milisegundos

void setup() {
  Serial.begin(115200);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  pinMode(xstep,OUTPUT);
  pinMode(xdir,OUTPUT);
  digitalWrite(xdir,HIGH);
}

void loop() {

 if (Serial.available() > 0) {
  
  char texto = Serial.read();

  switch (texto) {
  case '1':
    anglex = 0;
    break;
    
  case '2':
    anglex = 90;
    break;
    
  case '3':
    anglex = -90;
    break;
}
}

///////////aqui iba el for
    if(currentAnglex != anglex){

        if(currentAnglex < anglex){
            digitalWrite(xdir,HIGH);
            numstepx = (anglex - currentAnglex) / stepPerAnglex;
        }
        else{
            digitalWrite(xdir,LOW);
            numstepx = (currentAnglex - anglex) / stepPerAnglex;
        }

//////aca iba el for

  if(pasosx < numstepx){
    digitalWrite(xstep,HIGH);
    pasosx++;
    Serial.print(pasosx);
    Serial.println();
  }

      else{
        pasosx = 0;
        currentAnglex = anglex;
        }

           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(1000);
///////////aqui iba el for
    }
}
