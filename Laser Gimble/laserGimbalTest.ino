#include <Servo.h>
Servo myservo;
Servo myservo1;
int pos = 0;
int pos2 = 45;

void setup() {  
  pinMode(A1, INPUT);
  Serial.begin(9600);
  myservo.attach(9);
  myservo1.attach(10);
  
}

void loop(){  
  for(pos = 0; pos < 180; pos += 13){ 
   int sensorState = analogRead(A1);
   if (sensorState < 100) {
      myservo.detach();
      myservo1.detach();
   }
      myservo.write(pos); 
      for(pos2 = 55; pos2 < 100; pos2 +=1) {
      myservo1.write(pos2);
      delay(35);
      }
  }
  for(pos = 180; pos>=1; pos-=50){
   int sensorState = analogRead(A1); 
    if (sensorState < 100) {
      myservo.detach();
      myservo1.detach();
   }
    myservo.write(pos); 
    for(pos2 = 135; pos2 > 55; pos2 -=13) {
    myservo1.write(pos/2 + 45);
      delay(20);
    }
  }

  
}
  
