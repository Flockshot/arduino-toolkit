#include <LiquidCrystal.h>
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  6     // IN1 on the ULN2003 driver 1
#define motorPin2  7     // IN2 on the ULN2003 driver 1
#define motorPin3  8     // IN3 on the ULN2003 driver 1
#define motorPin4  9     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int sensorPin = A0;
const int background = 35;
int isDetected = 0;
int direction = 0;
int isMoving = 0;
const int turnSteps360 = 2100*4;

void setup() {
  lcd.begin(16, 2);
  pinMode(sensorPin, INPUT);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(500.0);
  stepper1.setSpeed(1000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);

  int thisReading = analogRead(sensorPin);   // Take a reading
  if(thisReading > background)
    isDetected = 1;
  else
    isDetected = 0;

  lcd.print("Reading: ");
  lcd.print(thisReading);

  lcd.setCursor(0, 1);
  if (isDetected == HIGH)                  
  {
    lcd.print("Detected");
    direction = 1;

    if(!isMoving)
    {
      stepper1.setSpeed(1000);
      stepper1.moveTo(turnSteps360);
      isMoving = 1;
    }
    else
    {
      if(stepper1.distanceToGo() == 0)
        isMoving = 0;
    }
  }  
  else
  {                                           
    lcd.print("Not Detected");
    direction = -1;

    if(!isMoving)
    {
      stepper1.setSpeed(1000);
      stepper1.moveTo(-stepper1.currentPosition());
      isMoving = 1;
    }
    else
    {
      if(stepper1.distanceToGo() == 0)
        isMoving = 0;
    }
  }
  delay(200);
}
