#include <math.h>

const int xdir = 5;
const int xstep = 2;
const int ydir = 6;
const int ystep = 3;
const int zdir = 7;
const int zstep = 4;
const int adir = 13;
const int astep = 12;

const int enPin = 8;

int currentAnglex = 0;
int anglex = 0;
float stepPerAnglex = 1.8;
int numstepx;

int currentAngley = 0;
int angley = 0;
float stepPerAngley = 1.8;
int numstepy;

int currentAnglez = 0;
int anglez = 0;
float stepPerAnglez = 1.8;
int numstepz;

int pasosx = 0;
int pasosy = 0;
int pasosz = 0;


void setup() {
  Serial.begin(115200);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  pinMode(xstep,OUTPUT);
  pinMode(ystep,OUTPUT);
  pinMode(zstep,OUTPUT);
  pinMode(xdir,OUTPUT);
  pinMode(ydir,OUTPUT);
  pinMode(zdir,OUTPUT);
  
  digitalWrite(xdir,HIGH);
  digitalWrite(ydir,HIGH);
  digitalWrite(zdir,HIGH);
}

void loop() {

 if (Serial.available() > 0) {
  
  char texto = Serial.read();

  switch (texto) {
  case '1':
    anglex = -90;
    angley = -45;
    anglez = -120;
    break;
    
  case '2':
    anglex = 0;
    angley = 0;
    anglez = 0;
    break;
    
  case '3':
    anglex = 90;
    angley = 45;
    anglez = 120;
    break;
}
}

///////////empeza el motor x
    if(currentAnglex != anglex){

        if(currentAnglex < anglex){
            digitalWrite(xdir,HIGH);
            numstepx = (anglex - currentAnglex) / stepPerAnglex;
        }
        else{
            digitalWrite(xdir,LOW);
            numstepx = (currentAnglex - anglex) / stepPerAnglex;
        }

  if(pasosx < numstepx){
    digitalWrite(xstep,HIGH);
    pasosx++;
  }

      else{
        pasosx = 0;
        currentAnglex = anglex;
        }
    }
///////////termina el motor x
///////////empeza el motor y
    if(currentAngley != angley){

        if(currentAngley < angley){
            digitalWrite(ydir,HIGH);
            numstepy = (angley - currentAngley) / stepPerAngley;
        }
        else{
            digitalWrite(ydir,LOW);
            numstepy = (currentAngley - angley) / stepPerAngley;
        }

  if(pasosy < numstepy){
    digitalWrite(ystep,HIGH);
    pasosy++;
  }

      else{
        pasosy = 0;
        currentAngley = angley;
        }
    }
///////////termina el motor y
///////////empeza el motor z
    if(currentAnglez != anglez){

        if(currentAnglez < anglez){
            digitalWrite(zdir,HIGH);
            numstepz = (anglez - currentAnglez) / stepPerAnglez;
        }
        else{
            digitalWrite(zdir,LOW);
            numstepz = (currentAnglez - anglez) / stepPerAnglez;
        }

  if(pasosz < numstepz){
    digitalWrite(zstep,HIGH);
    pasosz++;
  }

      else{
        pasosz = 0;
        currentAnglez = anglez;
        }
    }
///////////termina el motor z
           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           digitalWrite(ystep,LOW);
           digitalWrite(zstep,LOW);
           delayMicroseconds(1000);
}
