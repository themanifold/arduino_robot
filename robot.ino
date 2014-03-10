#include <AFMotor.h>

AF_DCMotor motorR(4);
AF_DCMotor motorL(1);

int maximumRange = 200;
int minimumRange = 0;
int sensorPinL = A0; //Analogue in L
int sensorPinR = A1; //Analogue in R
int sensorValueL = 0; //start value left
int sensorValueR = 0; //start value right
int speedL = 100;
int speedR = 100;

int trigPin = 10;
int echoPin = 9;

void setup() {
  Serial.begin (9600); //sets up serial port to allow input

}

void loop() {
  int foundL = 0;
  int foundR = 0;

  Serial.println(distanceAway());
  
  while(distanceAway() > 30) {
    go_fwd();
  }
  go_bwd();
  stop_move();
  spin_left();
  
//    findLine(foundL, foundR);
//    if(foundL == 0 && foundR == 1) {
//      spin_left();
//      go_fwd();
//    }
//    if(foundL == 1 && foundR == 0) {
//      spin_right();
//      go_fwd();
//    }
//    
//    if(foundL == 1 && foundR == 1) {
//      go_bwd();
//    }
  
}

void spin_left() {
  motorR.setSpeed(speedL);
  motorL.setSpeed(speedR);
  motorR.run(FORWARD);
  motorL.run(BACKWARD);
  delay(500);
}

void spin_right() {
  motorR.setSpeed(speedL);
  motorL.setSpeed(speedR);
  motorR.run(BACKWARD);
  motorL.run(FORWARD);
  delay(500);
}

void go_fwd() {
  motorR.setSpeed(speedL);
  motorR.run(FORWARD);
    motorL.setSpeed(speedR);
  motorL.run(FORWARD);
  delay(500);
}

void go_bwd() {
  motorR.setSpeed(speedL);
  motorR.run(BACKWARD);
  motorL.setSpeed(speedR);
  motorL.run(BACKWARD);
  delay(500);
}

void stop_move() {
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(500);
}

void findLine(int & foundL, int & foundR) {
  sensorValueL = analogRead(sensorPinL);
  
  if(sensorValueL > 100) {
    foundL = 1;
  }
  else {
    foundL = 0;
  }
  sensorValueR = analogRead(sensorPinR);

  if(sensorValueR > 100) {
    foundR = 1;
  }
  else {
    foundR = 0;
  }
}

long distanceAway() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in mm) based on the speed of sound.
  long distance;
  distance = duration/58.2;

  if (distance >= maximumRange || distance <= minimumRange){
    /* Send a negative number to computer and Turn LED ON 
     to indicate "out of range" */
    Serial.println("-1");
  }
  else {
    /* Send the distance to the computer using Serial protocol, and
     turn LED OFF to indicate successful reading. */
  }

  //Delay 50ms before next reading.
  delay(50);
  return(distance);
}





