const int BUTTON_PIN = 7;  // Connect the Button to pin 7 or change here
const int LED_PIN    = 3;       // Connect the LED to pin 3 or change here
  
// variables will change:
int ledState = LOW;        // tracks the current state of LED
int lastButtonState;        // the previous state of button
int currentButtonState; // the current state of button
  
void setup() {
  Serial.begin(3000);                         // initialize serial
  pinMode(BUTTON_PIN, INPUT);  // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);      // set arduino pin to output mode
  
  currentButtonState = digitalRead(BUTTON_PIN);
}
  
void loop() {
  lastButtonState    = currentButtonState;                // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); // read new state
  
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");
  
    // toggle state of LED
    if(ledState == LOW) {
       ledState = HIGH;  
       Serial.println("Turning LED on");
    }
    else {
      ledState = LOW;
      Serial.println("Turning LED off");
    }
 
    // control LED arccoding to the toggled state
    digitalWrite(LED_PIN, ledState);  //turns the LED on or off based on the variable
  }
}