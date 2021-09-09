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

void setup() {
  Serial.begin(115200);
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
    Serial.println("terminoX");
    
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
    Serial.println("terminoY");
    
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
    Serial.println("terminoZ");
    
  delay(200);
///////termina calibracion z
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
}

//delay(1000);
}
