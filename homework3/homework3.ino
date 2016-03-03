int ledPin1 = 3;
int ledPin2 = 5;
int ledPin3 = 6;
int ledPin4 = 13;
int timeShowRandom = 1000;
int timeShowDecision = 3000;
int timeBlink = 50;
int buttonPin = 4;

int buttonPress = false;
int randomNumber;
int previousNo = 0;
int timePassed = 0;

int pirPin = 9;

int laserPin = 10;
int calibrationTime = 30;  
long unsigned int lowIn;     
long unsigned int pause = 1000;      

boolean lockLow = true;
boolean takeLowTime;  

int potentiomenterInput = 5;
 
void setup()  {

  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin4, OUTPUT);
  digitalWrite(pirPin, LOW);
  pinMode(ledPin1, OUTPUT);
   pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);

    pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);


  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
    
}
 

void getRandomNo() {
  int rand = random(10,13);
  if(rand == previousNo) {
    getRandomNo();
  } else {
    randomNumber = rand;
    previousNo = randomNumber;
  }
}

 
void loop()  {
 
  potentiomenterInput = (analogRead(5)/4); // Divides input 0-1023 to resemble to 0-255
 
  analogWrite(ledPin1, potentiomenterInput);  
  analogWrite(ledPin2, potentiomenterInput);  
  analogWrite(ledPin3, potentiomenterInput);  
  // The delay can be change to get the desired dimming effect
  delay(20);   

 if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin4, HIGH);   //the led visualizes the sensors output pin state
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin4, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }




        if(digitalRead(buttonPin) == HIGH && buttonPress == false) {
     buttonPress = true;
  } if(buttonPress == true && timePassed <= timeShowRandom) {
    getRandomNo(); // Get random pin number
    digitalWrite(randomNumber, HIGH);
    delay(timeBlink);  
    digitalWrite(randomNumber, LOW);
    delay(timeBlink);  
    timePassed = timePassed + (timeBlink * 2);
  } else if(buttonPress == true) {
    digitalWrite(random(10,13), HIGH); // Set random pin on
    delay(timeShowDecision); // For x seconds
    buttonPress = false; // Set button to be enabled again
    timePassed = 0;
  } else {
    // Reset all output pins
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }    

           
       }
                           
}
