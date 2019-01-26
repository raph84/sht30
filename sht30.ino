#include <LiquidCrystal_I2C.h>
#include <WEMOS_SHT3X.h>

SHT3X sht30(0x45);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
}

void loop() {
  if(sht30.get()==0){
    serialOut(sht30.cTemp, sht30.humidity);
    displayLcd(sht30.cTemp, sht30.humidity);
  }
  else
  {
    Serial.println("Error!");
    displayLcd(0,0,"Error!");
  }
  delay(1000);

}

void serialOut(float cTemp, float humidite){
  Serial.print("Temperature in Celsius : ");
  Serial.println(sht30.cTemp);
  Serial.print("Temperature in Fahrenheit : ");
  Serial.println(sht30.fTemp);
  Serial.print("Relative Humidity : ");
  Serial.println(sht30.humidity);
  Serial.println();
}

void displayLcd(float cTemp, float humidity) {
  String bufT;
  bufT += F("TEMP: ");
  bufT += String(cTemp,2);

  String bufH;
  bufH += F("HUMIDITY: ");
  bufH += String(humidity,2);

  displayLcd(0, 0, bufT);
  displayLcd(0, 1, bufH);
}

void displayLcd(int x, int y, String str) {
  lcd.setCursor(x, y);
  lcd.print(str); 
}
