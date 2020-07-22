
//By Karim Elabyad
// This code takes sound input from arduino sound sensor and initiates two servo motors 

//Libraries
#include <Servo.h>

//Definitions
Servo ButtonServo;  
Servo ArmServo;
int posButton = 0;
int posArm = 0;
int SoundInput = 3;
int stateLED = LOW;
int stateButton = LOW;
int previous = LOW;
long time = 0;
long debounce = 200;
int counter = 0;


//Setup
void setup() {
  // put your setup code here, to run once:
  
  pinMode(SoundInput, INPUT); // attavhes the sound sensor to pin 3
  ButtonServo.attach(10);  // attaches the servo on pin 9 to the servo object
  ArmServo.attach(9);  // attaches the servo on pin 9 to the servo object
  
}

//Main Loop
void loop() 
{
  stateButton = digitalRead(SoundInput);  //Reads sound sensor input 
  Serial.print(stateButton); // Prints sound sensor state to serial monitor

  //Section of code that reads sound sensor
  if(stateButton == HIGH && previous == LOW && millis() - time > debounce) 
  {
    if(( stateLED == HIGH )) 
    {
            stateLED = LOW ;
    } else {

    if (counter == 0){
       ButtonServo.write(135); // moves first servo to 135 degrees
       delay(24000); // delay of 24 seconds
       ButtonServo.write(90); // moves first servo to 90 degrees
       counter = 1;
    }
  
    counter ==1;

    // Section that moves arm servo front and back 5 times
    for (counter =1; counter <= 6; counter++){
        for (posArm == 0; posArm <= 180; posArm += 180) 
        { // goes from 0 degrees to 180 degrees in steps of 180 degree
            ArmServo.write(posArm);              // tell servo to go to position in variable 'pos'
            delay(500); 
        }// waits 15ms for the servo to reach the position
        for (posArm == 180; posArm >= 0; posArm -= 180) 
        { // goes from 180 degrees to 0 degrees in steps of 180 degree
            ArmServo.write(posArm);              // tell servo to go to position in variable 'pos'
            delay(500); 
        }// waits 15ms for the servo to reach the position
    }
        }
    time = millis();
  }
    previous == stateButton;
    counter = 0;
}
