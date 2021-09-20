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
  for (int led = 0; led < 15; led++) {
  setLedColor();
 }
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

//TODO
bool readIRSensor() {
 return digitalRead(IR_PIN) == HIGH;
}

//Returns whether or not the touch sensor is being touched
bool readTouchSensor() {
 return digitalRead(TOUCH_PIN) == HIGH;
}


char buf[512];
void loop() {

//Handle ultrasonic building 4 effects
  float distance = readUltrasonic(U4_ECHO, U4_TRIG);
  if (distance > 0 && distance < 16) {        
    auto const currColour1 = CRGB(75,12,200);
    auto const currColour2 = CRGB(125, 200, 35);

    float fractVal1 = 1 / distance;
    fractVal1 = fractVal1 * 275;
    float fractVal2 = fractVal1 * 1.3;
    
    auto const newColour1 = blend(currColour1, CRGB::Red, fractVal1);
    auto const newColour2 = blend(currColour2, CRGB::Red, fractVal2);

    leds[11] = newColour1;
    leds[14] = newColour1;
    leds[3] = newColour2;
    leds[6] = newColour2;
    FastLED.show();

    if (distance < 4.00){
      //trigger flashing sequence
    }
  }


// //Handle all other cases
//  else {
//     auto const colour = CRGB(
//      (100, 255),
//      (0, 50),
//      random8(0, 100)
//    );
//    leds[ledNum] = colour;
//  }


// //Print all sensor details to `buf`
// sprintf(
//  buf,
//  "U4: %dcm\nU3: %dcm\nTouch: %s\nIR: %s\n",
//  readUltrasonic(U4_ECHO, U4_TRIG),
//  readUltrasonic(U3_ECHO, U3_TRIG),
//  (readTouchSensor() ? "yes" : "no"),
//  (readIRSensor() ? "yes" : "no")
//  );
//// //Print `buf` to the serial console
//Serial.print(buf);
}
