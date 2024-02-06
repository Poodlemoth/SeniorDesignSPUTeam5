#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN A0
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const int ledButtonPin = 2;
const int emergencyStopButtonPin = 3;
const int ledPin = 8;

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(ledPin, OUTPUT); // Declare LED pin as output
  pinMode(ledButtonPin, INPUT); // Declare LED button pin as input
  pinMode(emergencyStopButtonPin, INPUT_PULLUP); // Declare emergency stop button pin as input with internal pull-up resistor
  
  lcd.setCursor(0, 0);
  lcd.print("Hello to RELIEF!");
  lcd.setCursor(1, 1);
  lcd.print("User Interface");
  delay(5000);

  lcd.clear();
}

void loop() {
  if (checkEmergencyStop()) return;
  
  displayTemperatureHumidity();
  
  controlLED();
  
  delay(100);
}

void displayTemperatureHumidity() { // Temperature and Humuidty read out function
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)
  
  //--------------------humidity------------------------
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");

  //-----------------temperature as Fahrenheit----------
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(f);
  lcd.print(" F");
}

// LED Button Control
void controlLED() {
  if (digitalRead(ledButtonPin) == HIGH && digitalRead(ledPin) == LOW) { // When button is pushed and the led is off the led will turn on
    digitalWrite(ledPin, HIGH); // Turn on the LED
    Serial.println("Your LED was turned on");
  } else if (digitalRead(ledButtonPin) == HIGH && digitalRead(ledPin) == HIGH) { // When button is pushed and led is on the led will turn off
    digitalWrite(ledPin, LOW); // Turn off the LED
    Serial.println("Your LED was turned off");
  }
}

// Emergency Stop Button Function
bool checkEmergencyStop() {
  if (digitalRead(emergencyStopButtonPin) == HIGH) { // When button is pushed all functions (LCD, LED, Motor) will not work
    digitalWrite(ledPin, LOW); // Turn off the LED
    lcd.noBacklight(); // Turn off LCD
    while (true) {
      // Loop indefinitely, effectively stopping the program
    }
    return true;
  }
  return false;
}
