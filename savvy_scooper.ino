#include<Servo.h>

Servo s1;

int enaA = 5;
int in1 = 6;
int in2 = 7;

int enaB = 11; //10 got fried!
int in3 = 8;
int in4 = 9;

void setup() {
  //Attach a servo object to pin3 
  s1.attach(3); 
  //yellow wheel 
  pinMode(enaA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //black wheel 
  pinMode(enaB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //IR Sensor
  pinMode(12, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop(){
    start(); //Start the motors 
    check(); 
    delay(2000); //drive 2 seconds
    //stop yellow wheel to turn 
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    check();
    delay(1000); //drive 2 seconds
  
    //start yellow wheel again 
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enaA, 127);
    check();
    delay(3000); //drive 3 seconds

    //stop black wheel to turn
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    check();
    delay(2000); //drive 2 seconds
  
    //start black wheel again
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enaB, 127);
    check();
}

//turn both motors off
void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//start both motors 
void start(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enaA, 127);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enaB, 127);
}

//check if the IR sensor is being blocked or not and react accordingly 
void check(){
  //The IR sensor is being blocked: garbage detected!
  if(digitalRead(2) == LOW){
      digitalWrite(12, HIGH); //turn red LED on 
      collect(); //collect garbage 
  }
  else{
    digitalWrite(12, LOW); //turn red LED off
  } 
}

//Turn off motors, pick up garbage, wait for IR sensor to stop being blocked then resume motion 
void collect(){
    delay(10);
    stop(); //turn off both motors 
    delay(1000); //wait 1 second
    s1.write(90); //rotate scooper down 
    delay(1000); //wait 1 second
    s1.write(0); //rotate scooper back up 
    delay(1000); //wait 1 second 

   //Wait for the IR sensor to stop being obstructed 
    while(digitalRead(2)==LOW){
      delay(10);
      if(digitalRead(2)==HIGH){
        break;
      }
    start(); //turn motors back on 
}
