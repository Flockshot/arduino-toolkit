/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>


#define MAX_RES_VAL 1023
#define MIN_RES_VAL 0
#define MAX_VOLT_VAL 5
#define MIN_VOLT_VAL 0



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ldrPin = A5;
const int tempPin = A4;

int val = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
}

void loop()
{  
  int ldrInput = analogRead(ldrPin);
  ldrInput = analogRead(ldrPin);
  int tempInput = analogRead(tempPin);
  tempInput = analogRead(tempPin);

  lcd.clear();
  lcd.setCursor(0, 0);
  printLightVoltage(ldrInput); 
  lcd.setCursor(0, 1);
  printTemperature(tempInput);
  delay(250);
  
}


void printLightVoltage(int ldrInput)
{
  //int ldrInput = analogRead(ldrPin);
  float ldrNormalized =  normalize(ldrInput);
  float ldrVoltValue = MAX_VOLT_VAL-ldrNormalized;//ldrNormalized;
  
  lcd.print("Light: ");
  lcd.print(ldrVoltValue);
  lcd.print("V");
}

void printTemperature(int tempInput)
{
  //int tempInput = analogRead(tempPin);
  float tempNormalized = normalize(tempInput);
  float tempCentigrade = (tempNormalized*1000)/10;
  lcd.print("Temp: ");
  lcd.print(tempCentigrade);
  lcd.print("\337C");
}

float normalize(float input)
{
  return (((float)(input)/(float)(MAX_RES_VAL-MIN_RES_VAL))*MAX_VOLT_VAL)+MIN_VOLT_VAL;
}