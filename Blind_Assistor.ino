
const int motorPin1 = 3;
const int motorPin2 = 5;
const int motorPin3 = 10;

const int trigPin1 = 6;
const int echoPin1 = 7;

const int trigPin2 = 11;
const int echoPin2 = 12;

const int trigPin3 = 10;
const int echoPin3 = 13;

float duration1, duration2, duration3, distance1, distance2, distance3;

void setup() {
  pinMode(motorPin1, OUTPUT);   
  pinMode(motorPin2, OUTPUT); 
  pinMode(motorPin3, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.begin(9600);
}

void loop() {
 digitalWrite(trigPin1, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(2);
 duration1 = pulseIn(echoPin1, HIGH);
 distance1 = (duration1*.0343)/2;
 Serial.print("Distance1: ");
 Serial.println(distance1);
if (0 < distance1 <= 30)
  {
    digitalWrite(motorPin1, HIGH);    
    //delay(100);
  } 
if ( distance1 > 30)
  {
     digitalWrite(motorPin1, LOW);    
     //delay(100);
  } 
   
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(2);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2*.0343)/2;
  Serial.print("Distance2: ");
  Serial.println(distance2);
   if (0 < distance2 <= 30)
  {
    digitalWrite(motorPin2, HIGH);    
    //delay(100);
  } 
if ( distance2 > 30) 
  {
     digitalWrite(motorPin2, LOW);    
     //delay(100);
  } 
  

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH); 
  delayMicroseconds(2);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = (duration3*.0343)/2;
  Serial.print("Distance3: ");
  Serial.println(distance3);
  if (0 < distance3 <= 30)
  {
    digitalWrite(motorPin3, HIGH);    
           Serial.print("ON: ");

   // delay(100);
  } 
  if ( distance3 > 30) 
  {
     digitalWrite(motorPin3, LOW);   
     //delay(100);
  } 
 

 

}
