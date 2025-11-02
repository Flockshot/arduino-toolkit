#include <AccelStepper.h>


#define MAX_RES_VAL 1023
#define MIN_RES_VAL 0
#define MAX_VOLT_VAL 255
#define MIN_VOLT_VAL 0
#define HALFSTEP 8


const int input1 = 2;
const int enableOut= 3;
const int input2 = 4;

const int motorPin1 = 13;
const int motorPin2 = 12;
const int motorPin3 = 11;
const int motorPin4 = 10;

AccelStepper stepper1(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

const int stepPerRev = 2048;

const int trigger = 8;
const int echo = 9;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(enableOut, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(500.0);


  Serial.begin(9600);
  stepper1.setCurrentPosition(0);
}

bool isSpeedSet = false;
int speed = 0;

bool emergencyBrake = false;

void loop() {
  //analogWrite(enableOut, MAX_VOLT_VAL);
  //digitalWrite(input1, HIGH);
  //digitalWrite(input2, LOW); 
  

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH); // turn on the Trigger to generate pulse
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.0344 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 30)
  {
    emergencyBrake = true;
    analogWrite(enableOut, 0);
  }    
  else
  {
    emergencyBrake = false;
  }
  


  if (Serial.available()  > 0)
  {
    //incoming_val = Serial.read();
    char incoming_val = Serial.read();    

    Serial.print(incoming_val);
    Serial.println("");

   // analogWrite(enableOut, incoming.toInt());

    if (incoming_val == '1')
    {
      analogWrite(enableOut, isSpeedSet?speed:MAX_VOLT_VAL);
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH); 
    }
    else if(incoming_val == '0')
    {
      analogWrite(enableOut, MIN_VOLT_VAL);
    }
    else if(incoming_val == '-')
    {
      analogWrite(enableOut, isSpeedSet?speed:MAX_VOLT_VAL);
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
    }
    else if(incoming_val == '2')
    {
      isSpeedSet = true;
      analogWrite(enableOut, MAX_VOLT_VAL);
    }
    else if(incoming_val == '3')
    {
      isSpeedSet = true;
      analogWrite(enableOut, MAX_VOLT_VAL/2);
    }
    else if(incoming_val == '4')
    {
      isSpeedSet = true;
      analogWrite(enableOut, MAX_VOLT_VAL/4);      
    }
    else if(incoming_val == '5')
    {
      isSpeedSet = true;      
      analogWrite(enableOut, (MAX_VOLT_VAL*3)/4);
    }
    else if(incoming_val == '6')
    {
      stepper1.moveTo(stepPerRev);
      stepper1.runToPosition();
      delay(500);
    }
    else if(incoming_val == '7')
    {
      stepper1.moveTo(-stepPerRev);
      stepper1.runToPosition();
      delay(500);
    }

  }
  
  
}
