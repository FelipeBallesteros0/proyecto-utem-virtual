const int enPin = 8;

const int stepPin = 2;
const int dirPin = 5;
const int stepY = 3;
const int dirY = 6;
const int stepZ = 4;
const int dirZ = 7;



void setup() {
  
  Serial.begin(115200);
  
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
  
}

void loop() {

 if (Serial.available() > 0) {
  
  char incomingByte = Serial.read();

  switch (incomingByte) {
  case '1':
    motorpapx(0);
    break;
    
  case '2':
    motorpapx(90*8.75);
    break;
    
//  default:
//    // statements
//    break;
}
  }
  Serial.println();
}

void motorpapx(int angle){

  int n;
  int currentAngle = 0;
  float stepPerAngle = 0.9; // 360 grados/400 pasos// multiplicar el numero de pasos por la relacion de los engranajes
  int   numstep;


    if( currentAngle != angle ){

        if( currentAngle < angle){
            digitalWrite(dirPin,HIGH);
             n = angle - currentAngle;
            numstep = n / stepPerAngle;
        }

        else if( currentAngle > angle){
            digitalWrite(dirPin,LOW);
            n = currentAngle - angle;
            if( angle == 0){
               n =currentAngle;
            }
            numstep = n / stepPerAngle;
        }

        for(int x = 0; x < numstep; x++) {
           digitalWrite(stepPin,HIGH);
           delayMicroseconds(1000);
           digitalWrite(stepPin,LOW);
           delayMicroseconds(1000);
        }
        currentAngle = angle;
    }
    
   delay(500);

}
