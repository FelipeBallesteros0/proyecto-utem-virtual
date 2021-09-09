float i=1.5237475984328953;

#include "math.h"
void setup() 
{
  Serial.begin(115200);
}

void loop() {
  Serial.println(i,6);
  float price = i*1000;
  Serial.println(price,2);
  
  float roundNearest = roundf(i*1000) ; // x 100 for two decimal place
   roundNearest = roundNearest/1000;
  Serial.println(roundNearest,6);

  price = (roundNearest*1000);
  Serial.println(price,2);
  while(1){}
}
