// Writen by Clement Law (https://github.com/themanifold/arduino_robot) 
// with copyrights attributed 

#include <AFMotor.h>

// create direct current motors on ports 4(R), 1(L)
AF_DCMotor motorR(4);
AF_DCMotor motorL(1);

// declare global variables for ease

// max/min range of ultrasound sensor
int maximumRange = 200; 
int minimumRange = 0;

// analogue pin numbers dependent on circuit board
int sensorPinL = A0; // left
int sensorPinR = A1; // right

// speed of wheels, measured from 0 to 255 (0 is stop)
int speedL = 100; 
int speedR = 100;

int trigPin = 10;
int echoPin = 9;

// Has to be here: simple initialisation by Arduino firmware
void setup() {
  Serial.begin (9600); //sets up serial port to allow input

}

// Arduino firmware loops the below function ad infinitum

void loop() {
  // Diagnostic: print to serial port (specified in setup()) the 
  // distance away from obstacle reported by ultrasound sensor
  Serial.println(distanceAway());
  
  // While distance from obstacle is > 30cm, keep going forward
  // 30cm is specific to slippery kitchen tiles and rubber wheels
  while(distanceAway() > 30) {
    go_fwd();
  }
  
  // We're closer than 30cm away from obstacle
  // spin wheels backward (more eff. than stopping)
  go_bwd();
  
  // Completely stop wheels
  stop_move();
  
  // Spin robot left
  spin_left();
}

// Simple functions below move robot left, fwd or back
// They last for n milliseconds, empirically determined.

// Spin robot left by counter rotating wheels
void spin_left() {
  motorR.setSpeed(speedL);
  motorL.setSpeed(speedR);
  motorR.run(FORWARD);
  motorL.run(BACKWARD);
  delay(500);
}

// Move robot forward 
void go_fwd() {
  motorR.setSpeed(speedL);
  motorR.run(FORWARD);
  motorL.setSpeed(speedR);
  motorL.run(FORWARD);
  delay(500);
}

// Move robot backward
void go_bwd() {
  motorR.setSpeed(speedL);
  motorR.run(BACKWARD);
  motorL.setSpeed(speedR);
  motorL.run(BACKWARD);
  delay(500);
}

// Completely stop robot
void stop_move() {
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(500);
}

// Infer from analogue signal of ultrasound
// transducer that we'rea certain distance (cm) away

// Attributed to http://bit.ly/1wDOVSP

long distanceAway() {
// The following trigPin/echoPin cycle is used to determine the
// distance of the nearest object by bouncing soundwaves off of it.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
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
