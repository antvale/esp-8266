/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk token
char auth[] = "f907b792ed0e47bdb675467abaf22b74";

// WiFi access
char ssid[] = "HUAWEI P10";
char pass[] = "78b30ca5541f";

// pinout variables, never change
const int BUTTON1 = 0;
const int BUTTON2 = 2;

// button debounce variables
unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
unsigned long debounceDelay = 500;    // the debounce time; increase if the output flickers


WidgetLED ledRed(V3);
WidgetLED ledBlue(V4);

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON1,INPUT);
  digitalWrite(BUTTON1,HIGH);

  pinMode(BUTTON2,INPUT);
  digitalWrite(BUTTON2,HIGH);

  ledRed.off();
  ledBlue.off();
  
  // Debug console
  Serial.begin(115200);

  // pinout init
  
  
  // Try to connected to blynk cloud
  Blynk.begin(auth, ssid, pass);

  // Clear the lcd display widget
  Blynk.virtualWrite(V1, "-.-");
  Blynk.virtualWrite(V2, "-.-");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  
  
  // single click on button 1
  if (singleClickButton(BUTTON1)){
      Blynk.virtualWrite(V1, "Red Pill Refill");
      Blynk.virtualWrite(V2, "Quantity:5");
      ledRed.on();
      ledBlue.off();
      
    }

  // single click on button 2
  if (singleClickButton(BUTTON2)){
      Blynk.virtualWrite(V1, "Blue Pill Refill");
      Blynk.virtualWrite(V2, "Quantity:8");
      ledBlue.on();
      ledRed.off();
    }

}

boolean singleClickButton(int button_pin){

  boolean clicked=false;
  
  // read the state of the switch into a local variable:
  int buttonState = digitalRead(button_pin);
  
  //filter out any noise by setting a time buffer
  if ((millis() - lastDebounceTime) > debounceDelay && buttonState == LOW) {
      clicked=true;
      lastDebounceTime = millis(); //set the current time 
   }

   return clicked;

  }

void turnLedOn(WidgetLED led)
{
  if (led.getValue()) {
    led.off();
    Serial.println("LED: off");
  } else {
    led.on();
    Serial.println("LED: on");
  }
}
