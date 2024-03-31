#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define FANPIN 3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

enum DisplayState {
  TEMP_HUM_DISPLAY,
  FAN_STATUS_DISPLAY
};

DisplayState currentState = TEMP_HUM_DISPLAY;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(FANPIN, OUTPUT);
}

void loop() {
  switch (currentState) {
    case TEMP_HUM_DISPLAY:
      displayTempHum();
      delay(2000); // Display temperature and humidity for 2 seconds
      currentState = FAN_STATUS_DISPLAY;
      break;

    case FAN_STATUS_DISPLAY:
      displayFanStatus();
      delay(2000); // Display fan status for 2 seconds
      currentState = TEMP_HUM_DISPLAY;
      break;
  }
}

void displayTempHum() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");
}

void displayFanStatus() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fan: ");

  float temperature = dht.readTemperature();

  if (temperature > 35) {
    digitalWrite(FANPIN, LOW);
    lcd.print("ON");
    Serial.println("Temperature is too high! Turning on fan...");
  } else {
    digitalWrite(FANPIN, HIGH);
    lcd.print("OFF");
  }
}
