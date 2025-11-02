
#define YELLOW 2
#define GREEN 3
#define MAX_LEDS 4
#define MIN_SWITCH_DELAY 100
#define MAX_SWITCH_DELAY 500

const int leds[MAX_LEDS] = {2,3,4,5};

void setup() {
  // put your setup code here, to run once:
  int i = 0;
  for(;i<MAX_LEDS;i++)
  {
      pinMode(leds[i], OUTPUT);
      digitalWrite(leds[i], 1);    
  }
  
}

int current_led = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(current_led>=MAX_LEDS)
    current_led = 0;

  current_led = random(0,MAX_LEDS);
  
  digitalWrite(leds[current_led], 0);
  delay(random(MIN_SWITCH_DELAY, MAX_SWITCH_DELAY+1));
  digitalWrite(leds[current_led], 1);

  current_led++;


}
