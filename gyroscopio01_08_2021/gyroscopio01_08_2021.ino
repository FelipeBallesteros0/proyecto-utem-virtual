#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kay( 0.3, 0.3, 0.9);
//SimpleKalmanFilter kaz( 0.3, 0.3, 0.9);

float t,dt,t2,dt2 = 0;

float vgx = 0;
float vgx2 = 0;
float vgx3 = 0;
float vgx21 = 0;

float offsetx;

const int xdir = 5;
const int xstep = 2;
const int enPin = 8;

int currentAngle = 0;
int angle = 0;
float stepPerAngle = 0.9;
int numstep;
int n;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginGyro();
  
  pinMode(xdir,OUTPUT);
  pinMode(xstep,OUTPUT);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  digitalWrite(xdir,HIGH);


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
   delay(500);
   mySensor.gyroUpdate();
   vgx = mySensor.gyroZ();
   vgx2 = kax.updateEstimate(vgx) - offsetx;
   vgx2 = inverseconstrain(-0.2,0.25,0,vgx2);
   dt = (millis() - t)/1000;
//   vgx3 = vgx3 + (vgx2*dt);
   vgx3 = vgx3 + (dt/2)*(vgx2 + vgx21);
   vgx21 = vgx2;

if (Serial.available()) {
    char texto = Serial.read();
    
        switch (texto) {
            case '1':
            angle = 0;
            break;
            
            case '2':
            angle = 90;
            break;
          }


             
    
       if( currentAngle != angle ){

        if( currentAngle < angle){
            digitalWrite(xdir,HIGH);
             n = angle - currentAngle;
            numstep = n / stepPerAngle;
        }

        else if( currentAngle > angle){
            digitalWrite(xdir,LOW);
            n = currentAngle - angle;
            if( angle == 0){
               n =currentAngle;
            }
            numstep = n / stepPerAngle;
        }

        for(int x = 0; x < numstep*8.75; x++) {

           t2 = millis();                                //aaa
          
           digitalWrite(xstep,HIGH);
           delayMicroseconds(1000);
           digitalWrite(xstep,LOW);
           delayMicroseconds(1000);

           mySensor.gyroUpdate();                       //aaa
           vgx = mySensor.gyroZ();                      //aaa
           vgx2 = kax.updateEstimate(vgx) - offsetx;    //aaa
           vgx2 = inverseconstrain(-0.2,0.25,0,vgx2);   //aaa
           dt2 = (millis() - t2)/1000;                  //aaa
           //   vgx3 = vgx3 + (vgx2*dt);                //aaa
           vgx3 = vgx3 + (dt2/2)*(vgx2 + vgx21);        //aaa
           vgx21 = vgx2;                                //aaa
           
           Serial.print(vgx3,10);                       //aaa
           Serial.println();                            //aaa
           
        }
        currentAngle = angle;
    }
                   
}





//   Serial.print(offsetx,10);
//   Serial.print(",");
//   Serial.print(vgx,10);
//   Serial.print(",");
//   Serial.print(vgx3,10);
//   Serial.print(",");
   Serial.print(vgx3,10);
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
