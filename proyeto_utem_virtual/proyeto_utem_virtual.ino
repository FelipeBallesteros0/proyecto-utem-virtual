#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(D1,D8,D0); //Hardware SPI
                                                       //DC,CE,RST.respectivamente, el DIN va en D7 y el CLK en D5
void setup() {
Serial.begin(9600);
display.begin();
display.setContrast(50);
display.setTextSize(1);
display.setCursor(0,0);
display.setTextColor(BLACK);
display.clearDisplay();
display.display();
delay(1000);
}

void loop() {

{
  if (Serial.available()){
  char aaa = Serial.read();
//    switch(aaa){
//  case 'a' :
  String gx =Serial.readString();
  float gy =Serial.read();
  float gz =Serial.read();
  float ax =Serial.read();
  float ay =Serial.read();
  float az =Serial.read();

//  float fgx = gx;
//  float fgy = gy;
//  float fgz = gz;
//  float fax = ax;
//  float fay = ay;
//  float faz = az;

 // display.print(aaa);
  Serial.print(gx);
  display.print("Gx=");
  display.println(gx);
//  display.print("Gy=");
//  display.println(fgy);
//  display.print("Gz=");
//  display.println(fgz);
//  display.print("Ax=");
//  display.println(fax);
//  display.print("Ay=");
//  display.println(fay);
//  display.print("Az=");
//  display.println(faz);
  
  display.display();
  delay(100);
  display.clearDisplay();
//  break;
//  }
  
    }
   }
}
