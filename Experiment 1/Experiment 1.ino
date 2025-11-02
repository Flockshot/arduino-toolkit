#define SWITCH 2
#define A 12
#define B 11
#define C 10
#define D 9
#define E 8
#define F 7
#define G 6
#define DP 5

int counting = 0;

//display number 1
void display1(void) {
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}
//display number 2
void display2(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
}
// display number 3
void display3(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);

  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(G, HIGH);
}
// display number 4
void display4(void) {
  digitalWrite(F, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
}
// display number 5
void display5(void) {
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}
// display number 6
void display6(void) {
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
}
// display number 7
void display7(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}
// display number 8
void display8(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}
// display number 9
void display9(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
}
// display number 0
void display0(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}
void clearDisplay(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(G, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
}


void buttonPush() {

  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    //Increment the counting number.
    counting += 1;
    if (counting >= 10)
      counting = 0;

    displayNumber(counting);
  }
  last_interrupt_time = interrupt_time;
}

//Display the number on the 7-segment display according to the number in count.
void displayNumber(int number) {
  clearDisplay();
  switch (number) {
    case 0:
      display0();
      break;
    case 1:
      display1();
      break;
    case 2:
      display2();
      break;
    case 3:
      display3();
      break;
    case 4:
      display4();
      break;
    case 5:
      display5();
      break;
    case 6:
      display6();
      break;
    case 7:
      display7();
      break;
    case 8:
      display8();
      break;
    case 9:
      display9();
      break;
  }
}

void setup() {

  int i;
  //Setup the a-g pins as output
  for (i = 5; i <= 12; i++)
    pinMode(i, OUTPUT);

  //Set the push button pin as input, and make it an external interupt.
  pinMode(SWITCH, INPUT);
  attachInterrupt(digitalPinToInterrupt(SWITCH), buttonPush, RISING);

  
  displayNumber(counting);
}

bool isPressed = false;
bool toChange = false;
bool isClockwise = true;
void loop() {

  if(digitalRead(buttonPush) == HIGH)
  {
    isPressed = true;
    toChange = true;
    delay(250);
  }
  if(!digitalRead(buttonPush))
  {
    isPressed = false;
  }

  if(toChange && !isPressed)
  {    
    isClockwise = !isClockwise;
  }

  if(isClockwise)
  {
    //Outputs for clockwise.
  }
  else
  {
    //Outputs for anti-clockwise.
  }

}