#include <Wire.h>
#include <toneAC.h>

#define MOTION_SENSOR_PIN 12  // Digital pin connected to the motion sensor
#define MOTION_SENSOR_PIN_2 11
#define MOTION_SENSOR_PIN_3 13

#define DURATION 5000        // Duration for which the frequency generation remains active (30 seconds)
#define DURATION_EGG 5000 // Pi on for 10s
#define Pi_pin 8
#define ADXL345 0x53
//pin 9 and 10 for ToneAC
#define battery_pin A0
#define battery_notification_pin 5
#define min_voltage 11.8


int movement = 0; 
int pi_running = 0;
float xval;
float yval;
float zval;

float xprev = 0;
float yprev = 0;
float zprev = 0;

float jolt_sq;
float jolt_limit = 0.01;

unsigned long startTime_egg = 0;
unsigned long timeToStop_egg = 0;

float adc_in = 0.0;
float battery_voltage = 0.0;
int adc_val = 0;



void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(MOTION_SENSOR_PIN_2, INPUT);
  pinMode(MOTION_SENSOR_PIN_3, INPUT);

  //pinMode(battery_pin, INPUT);
  pinMode(battery_notification_pin, OUTPUT);

  pinMode(Pi_pin, OUTPUT);
  digitalWrite(Pi_pin, LOW);
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(10);


}

int motion = 0;
int running = 0;
unsigned long startTime = 0;
long frequency = 0;

void loop() {
  
  if(running)
    generateFrequency(frequency);

  else
    if ((digitalRead(MOTION_SENSOR_PIN) == HIGH) || (digitalRead(MOTION_SENSOR_PIN_2 == HIGH)|| (digitalRead(MOTION_SENSOR_PIN_3 == HIGH))))
      motion = 1;       // Motion detected
    else
      motion = 0;
    
  

  if(motion)
  {
    motion = 0;
    running = 1;
    startTime = millis();
    frequency = random(45000, 60001);
    toneAC(frequency);
  }

  egg_sensor_detect();
  battery_level();

}

void generateFrequency(long frequency) {

  unsigned long timeToStop = startTime+((unsigned long) DURATION);
  Serial.println();
  
  if(millis()>=timeToStop)
  {
    Serial.println("Time Up");
    running = 0;
    startTime = 0;
    cleanOutput();
  }
}


void cleanOutput()
{
  toneAC();
}



void egg_sensor_detect(void)
{
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  xval = (Wire.read() | Wire.read() << 8);
  xval = xval/256;
  yval = (Wire.read() | Wire.read() << 8);
  yval = yval/256; 
  zval = (Wire.read() | Wire.read() << 8);
  zval = zval/256; 

  jolt_sq = (sq(xval-xprev) + sq(yval - yprev) + sq(zval-zprev));

  Serial.print(xval, 4);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(yval, 4);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(zval, 4);

  Serial.print("\t");
  Serial.print(jolt_sq, 4);

  Serial.println();
  xprev = xval;
  yprev = yval;
  zprev = zval;
  
  if (pi_running)
  {
    if(millis()>=timeToStop_egg)
    {
      digitalWrite(Pi_pin, LOW);
      pi_running = 0;
      startTime_egg = 0;
    }
  }
  else
  {
    if (jolt_sq > jolt_limit)
      movement = 1; 
    else
      movement = 0;
  }

  if (movement)
  {
    digitalWrite(Pi_pin, HIGH);
    movement = 0;
    pi_running = 1;
    startTime_egg = millis();
    timeToStop_egg = startTime_egg+((unsigned long) DURATION_EGG);
  }

  // delay before next reading:
  delay(10);
}

void battery_level(void)
{
  adc_val = analogRead(battery_pin);
  adc_in = (float)(adc_val*5)/1024.0;
  battery_voltage = adc_in*5;

  if(battery_voltage < min_voltage)
    digitalWrite(battery_notification_pin, HIGH);
  else
    digitalWrite(battery_notification_pin, LOW);

}
