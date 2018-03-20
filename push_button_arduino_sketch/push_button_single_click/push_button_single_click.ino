/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk token
char auth[] = "f907b792ed0e47bdb675467abaf22b74";

// WiFi access
char ssid[] = "NETGEAR39";
char pass[] = "qazplm01";

// pinout variables, never change
const int BUTTON1 = 0;
const int BUTTON2 = 2;

// button debounce variables
unsigned long lastDebounceTime = 0;   // the last time the output pin was toggled
unsigned long debounceDelay = 500;    // the debounce time; increase if the output flickers

int count=0;

// Dry-run to check the connectvity b/w blynk app and esp8266
// WidgetLED 

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON1,INPUT);
  digitalWrite(BUTTON1,HIGH);

  pinMode(BUTTON2,INPUT);
  digitalWrite(BUTTON2,HIGH);
  
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
  if (clickButton(BUTTON1)==0){
      Blynk.virtualWrite(V1, "Red Pill Refill");
      Blynk.virtualWrite(V2, "Quantity:5");
    }

  // single click on button 2
  if (clickButton(BUTTON2)==0){
      Blynk.virtualWrite(V1, "Blue Pill Refill");
      Blynk.virtualWrite(V2, "Quantity:8");
    }

}

int clickButton(int button_pin){

  int clickMode=-1;
  
  // read the state of the switch into a local variable:
  int buttonState = digitalRead(button_pin);
  
   //filter out any noise by setting a time buffer
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
     //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    
    if ( buttonState == LOW) {
      clickMode=0;
      lastDebounceTime = millis(); //set the current time
    }
    

   }//close if(time buffer)    

   return clickMode;
  }
