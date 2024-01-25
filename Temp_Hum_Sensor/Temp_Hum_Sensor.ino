#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN A0
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
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
  
  delay(2000);

}