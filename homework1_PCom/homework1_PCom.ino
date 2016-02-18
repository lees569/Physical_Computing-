/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin1 = 5;
const int buttonPin2 = 8;  

const int AOUTpin=0;
const int DOUTpin=7;
const int ledPin =  2;      

// variables will change:
int buttonState1 = 0;
int buttonState2 = 0;

int limit;
int value;
// Pins
int sensorPin = 5;
int lightPin = 3;


// Variables
int lightState = 0;
int lowThreshold = 10 ;
int highTreshold = 40;

void setup() {

  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  pinMode(DOUTpin, INPUT);


  
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState1 == HIGH || buttonState2 == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);


    value= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin
    limit= digitalRead(DOUTpin);//reads the digital value from the alcohol sensor's DOUT pin
    
    Serial.print("Alcohol value: ");
    Serial.println(value);//prints the alcohol value
    Serial.print("Limit: ");
    Serial.print(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
    delay(100);
    if (value > 900){
    digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
    }
    else{
    digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
    }
  }

   int sensorValue = analogRead(sensorPin);

   Serial.print("Light Level: ");
    Serial.println(sensorValue);//prints the alcohol value

  // If light level is low is detected, switch light on
  if (sensorValue < lowThreshold){
    digitalWrite(lightPin, HIGH);
  }
  
  // If light level goes up again, switch the lights off
  if (sensorValue > highTreshold){ 
    digitalWrite(lightPin, LOW);
  }
  
}
