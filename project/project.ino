#include <Servo.h>

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
#define led3 2
const int BUZZ = 6;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(6,OUTPUT);
  myservo.attach(9);
}

void loop() {
  long duration, distance ;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // This is where the LED On/Off happens

   
   
    for (pos = 180; pos >= 0; pos -= 1) { 
    // in steps of 1 degree
    myservo.write(pos); 
//    delay(2000); 
    
    
    }
    
    digitalWrite(led,HIGH);
    digitalWrite(led3,HIGH);// When the Red condition is met, the Green LED should turn off
    digitalWrite(led2,LOW);
     tone(6,4000);
    delay(4000);
    tone(6,0);
   
//    analogWrite(BUZZ, 1000);
    





}
  else {


    
  
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  
}       
 
    
    digitalWrite(led,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led2,HIGH);

  }
  if (distance >= 150 || distance >= 0){


    
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

