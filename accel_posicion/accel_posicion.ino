#include <MPU9250_asukiaaa.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP280 bme;
MPU9250_asukiaaa mySensor;

SimpleKalmanFilter kax( 0.3, 0.3, 0.9);

int nDEC = 100;

float t,dt,t2,dt2;

float aax = 0;
float aay = 0;
float aaz = 0;

float aax2 = 0;
float aay2 = 0;
float aaz2 = 0;

float aax3 = 0;
float aay3 = 0;
float aaz3 = 0;

float aax4 = 0;
float aay4 = 0;
float aaz4 = 0;

float aax41 = 0;
float aay41 = 0;
float aaz41 = 0;

float vax = 0;
float vay = 0;
float vaz = 0;

float vax1 = 0;
float vay1 = 0;
float vaz1 = 0;

float pax = 0;
float pay = 0;
float paz = 0;

const float g = 9.780327;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  bme.begin();
  mySensor.beginAccel();
  delay(200);
}

void loop() {
  

//   t = micros();
   
   mySensor.accelUpdate();
   
   aax = mySensor.accelX();
//   aay = mySensor.accelY();
//   aaz = mySensor.accelZ();

   aax2 = kax.updateEstimate(aax);
//   aay2 = kay.updateEstimate(aay);
//   aaz2 = kaz.updateEstimate(aaz);
      
   aax3 = round(aax2*nDEC);
//   aay = round(aay*nDEC);
//   aaz = round(aaz*nDEC);
//   
   aax3 = (aax3/nDEC) + 0.039999998;
//   aay = (aay/nDEC);
//   aaz = (aaz/nDEC);
   
   aax4 = aax3*g;
//   aay = aay*g;
//   aaz = aaz*g;

//   dt = (micros() - t)/1000000;
   dt = 0.1;

//   vax =  vax + ((dt/2) * (aax4 + aax41));
   vax =  ((dt/2) * (aax4 + aax41));
//   vay = vay + (dt/2) + (aay + aay41);
//   vaz = vaz + (dt/2) + (aaz + aaz41);
   
   aax41 = aax4;
//   aay41 = aay;
//   aaz41 = aaz;



//   dt2 = (micros() - t)/1000000;

   pax = pax + ((dt/2) * (vax + vax1));
//   pay = pay + (dt2/2) + (vay + vay1);
//   paz = paz + (dt2/2) + (vaz + vaz1);


//   pax = pax + vax*dt;
//   pay = pay + vay*dt;
//   paz = paz + vaz*dt;

   vax1 = vax;
//   vay1 = vay;
//   vaz1 = vaz;
   
   Serial.print(pax*100,10);
   Serial.print(",");
//   Serial.print(pay,10);
//   Serial.print(",");
//   Serial.print(paz,10);
//   Serial.print(",");
   Serial.print(aax,10);
   Serial.print(",");
   Serial.print(aax2,10);
   Serial.print(",");
   Serial.print(aax4,30);
      Serial.print("_______");
   Serial.print(vax,20);
//   Serial.print(",");
//   Serial.print(aay,10);
//   Serial.print(",");
//   Serial.print(aaz,10);
   Serial.println();
   delay(100);
  }







  
