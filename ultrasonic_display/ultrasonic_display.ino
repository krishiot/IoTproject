#include <LiquidCrystal_I2C.h>
#include <NewPing.h>  // Include the NewPing library for the HC-SR04 sensor

#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();         // Initializes the LCD 
  lcd.backlight();    // Turns on the backlight
  lcd.setCursor(0, 0);// Sets the cursor on the LCD
  lcd.clear();        // Clears the LCD display
  Serial.begin(9600);
}

void loop() {
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  unsigned int cm = sonar.ping_cm(); // Send ping, get distance in centimeters

  Serial.print("Distance: ");
  Serial.print(cm); // Print the distance to the serial monitor
  Serial.println(" cm");

  lcd.setCursor(0, 1);  // Set cursor to second line
  lcd.print("Distance: ");  // Print label
  lcd.print(cm);  // Print distance in cm
  
  lcd.print(" cm     ");  // Print some spaces to clear any remaining characters
}
