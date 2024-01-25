#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN A0
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const int BUTTON_PIN = 7;  // Connect the Button to pin 7 or change here
const int LED_PIN    = 3;  // Connect the LED to pin 3 or change here

// variables will change:
int ledState = LOW;        // tracks the current state of LED
int lastButtonState;       // the previous state of the button
int currentButtonState;    // the current state of the button

void setup() {
  Serial.begin(9600);         // initialize serial
  pinMode(BUTTON_PIN, INPUT); // set Arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);    // set Arduino pin to output mode

  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("R.E.L.I.E.F");
  lcd.setCursor(2, 1);
  lcd.print("User Interface");
  delay(3000);

  lcd.clear();
}

void loop() {
  // Read temperature and humidity
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);

  // Display humidity on LCD
  lcd.setCursor(3, 0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");

  // Display temperature on LCD
  lcd.setCursor(2, 1);
  lcd.print("Temp: ");
  lcd.print(f);
  lcd.print(" F");

  // Button functionality
  lastButtonState = currentButtonState;           // save the last state
  currentButtonState = digitalRead(BUTTON_PIN);  // read new state

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.print("The button is pressed: ");

    // Toggle state of LED
    if (ledState == LOW) {
      ledState = HIGH;
      Serial.println("Turning LED on");
    } else {
      ledState = LOW;
      Serial.println("Turning LED off");
    }

    // Control LED according to the toggled state
    digitalWrite(LED_PIN, ledState);  // turns the LED on or off based on the variable
  }

  delay(2000);
}