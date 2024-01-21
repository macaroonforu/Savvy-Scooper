#include<Servo.h>

Servo s1;

int enaA = 5;
int in1 = 6;
int in2 = 7;

int enaB = 11;
int in3 = 8;
int in4 = 9;

void setup() {
  // put your setup code here, to run once:
  s1.attach(3);
  //Motor A
  pinMode(enaA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //Motor B
  pinMode(enaB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //IR Sensor
  pinMode(12, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop(){
    //CLOCKWISE MAX SPEED A&B for 2 seconds
    start();
    check();
    delay(2000);
    //STOP A to turn (Black)
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    check();
    delay(1000);

    //Start A again so both are running
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enaA, 127);
   
    check();
    delay(3000);
    //STOP B to turn
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
   
    check();
    delay(2000);
    //Start B again so both are running
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enaB, 127);
 
    check();
    //delay(2000);
}

void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void start(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enaA, 127);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enaB, 127);
}

void check(){
  if(digitalRead(2) == LOW){
      digitalWrite(12, HIGH);
      //delay(10);
      collect();
  }
  else{
    digitalWrite(12, LOW);
    //delay(10);
  } 
}

void collect(){
    digitalWrite(12, HIGH);
    delay(10);
    stop();
    delay(1000);
    s1.write(90);
    delay(1000);
    s1.write(0);
    delay(1000);
    while(digitalRead(2)==LOW){
      delay(10);
      if(digitalRead(2)==HIGH){
        break;
      }
    }
    start();
}
