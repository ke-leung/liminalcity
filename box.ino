#include <FastLED.h>

//LED defines
#define LED_PIN PD3
#define NUM_LEDS 15
CRGB leds[NUM_LEDS];

//Touch sensor
#define TOUCH_PIN PD4

//IR motion sensor
#define IR_PIN PD5

//Ultrasonic sensor (building 4)
#define U4_ECHO PD6
#define U4_TRIG PD7

//Ultrasonic sensor (building 3)
#define U3_ECHO PB1
#define U3_TRIG PB0

//Conditions to change LED effects
bool b1Trigger = false;
bool b4Trigger = false;
bool b2Trigger = false;

 
void setup() {
 //Start serial at 115200 baud
 //Serial.begin(115200);
 //Set up LED output pin
 pinMode(LED_PIN, OUTPUT);
 FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
 //Disable all LEDs at reboot
 for (auto& led : leds) {
  led = CRGB(0, 0, 0);
 }
 FastLED.show();
 delay(1000);
 //Set up touch sensor
 pinMode(TOUCH_PIN, INPUT);
 //Set up IR sensor
 pinMode(IR_PIN, INPUT);
 //Set up ultrasonic distance sensor (building 5)
 pinMode(U4_ECHO, INPUT);
 pinMode(U4_TRIG, OUTPUT);
 //Set up ultrasonic distance sensor (building 3)
 pinMode(U3_ECHO, INPUT);
 pinMode(U3_TRIG, OUTPUT);

 //set default lights
  setLedColor();
}

void setLedColor()  {
  //cycle through all buildings
  leds[0] = CRGB(75, 200, 150);
  delay(20);
  FastLED.show();
  leds[1] = CRGB(25, 220, 175);
  delay(20);
  FastLED.show();
  leds[2] = CRGB(50, 210, 160);
  delay(20);
  FastLED.show();
  leds[3] = CRGB(125, 200, 35);
  delay(20);
  FastLED.show();
  leds[6] = CRGB(150, 200, 60);
  delay(20);
  FastLED.show();
  leds[7] = CRGB(45, 20, 250);
  delay(20);
  FastLED.show();
  leds[8] = CRGB(75, 45, 200);
  delay(20);
  FastLED.show();
  leds[9] = CRGB(156, 85, 20);
  delay(20);
  FastLED.show();
  leds[10] = CRGB(160, 90, 10);
  delay(20);
  FastLED.show();
  leds[11] = CRGB(75, 12, 200);
  delay(20);
  FastLED.show();
  leds[14] = CRGB(90, 5, 220);
  delay(20);
  FastLED.show();
}

//Returns distance in cm
int readUltrasonic(uint8_t echoPin, uint8_t trigPin) {
 //Clear trigger pin
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 //Set trigger pin for 10us
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 int const duration = pulseIn(echoPin, HIGH);
 return duration * 0.034/2;
}

//Returns whether or not motion is detected
bool readIRSensor() {
 return digitalRead(IR_PIN) == HIGH;
}

//Returns whether or not the touch sensor is being touched
bool readTouchSensor() {
 return digitalRead(TOUCH_PIN) == HIGH;
}

//Handle ultrasonic building 4 effects
void handleUltrasonic4(){
  float distance = readUltrasonic(U4_ECHO, U4_TRIG);
  auto const currColour = CRGB(75,12,200);
  
  if (distance > 0 && distance < 17) {        
    float fractVal = 1 / distance;
    fractVal = fractVal * 300;
    
    auto const newColour = blend(currColour, CRGB::Red, fractVal);

    leds[11] = newColour;
    leds[14] = newColour;
    FastLED.show();

    if (distance < 4.00){
      //trigger flashing sequence
    }
  }
}

//Handle ultrasonic building 3 effects
void handleUltrasonic3(){
  float distance = readUltrasonic(U3_ECHO, U3_TRIG);  
  auto const currColour = CRGB(125, 200, 35);

  if (distance > 0 && distance < 13) {
    float fractVal = 1 / distance;
    fractVal = fractVal * 350;
    
    auto const newColour = blend(currColour, CRGB::Red, fractVal);
    
    leds[3] = newColour;
    leds[6] = newColour;
    FastLED.show();
    
    if (distance < 4.00){
      //trigger flashing sequence
    }
  }
}

void loop() {

  handleUltrasonic4();
  handleUltrasonic3();
  

// //Handle all other cases
//  else {
//     auto const colour = CRGB(
//      (100, 255),
//      (0, 50),
//      random8(0, 100)
//    );
//    leds[ledNum] = colour;
//  }

}
