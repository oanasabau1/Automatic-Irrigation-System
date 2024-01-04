/*

  Automatic Irrigation System
  The aim is to monitor soil moisture levels and activate an irrigation system (such as a water pump) 
  when the humidity drops below a certain threshold.
  Additionally a photoresistor will be used to measure light intensity to ensure that our plant gets a generous amount of light, 
  with all the plant's needs displayed on an LCD screen and in the Serial Monitor.

*/

// Including the specific libraries for the LCD component
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Pins declaration
int waterPin = A0;
int photoPin = A1;
int pumpPin = 3;

// Variables
int soilMoistureValue = 0;
int percentage = 0;
int light = 0;
int photoResistorThreshold = 10; // Set the desired threshold value for the photoresistor

void setup() {

  // Initializing the LCD
  lcd.begin(16, 2);
  lcd.backlight();

  // Setting the pins accordingly
  pinMode(photoPin, INPUT);
  pinMode(waterPin, INPUT);
  pinMode(pumpPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Read the values from the sensors
  soilMoistureValue = analogRead(waterPin);
    light = analogRead(photoPin);

  // Calculate the percentage of the soil moisture based on this formula after calibrating the sensor
  percentage = map(soilMoistureValue, 250, 576, 100, 0);

  // Showing info on Serial Monitor
  Serial.print("Soil moisture:");
  Serial.print(percentage);
  Serial.println("%");

  Serial.print("Light:");
  Serial.print(light);
  Serial.println(" units");

  // Update first line only when needed on the LCD
  lcd.setCursor(0, 0);

  // The soil is too dry
  if (percentage < 10) {
    lcd.print("I'm thirsty!       "); // Ensure a stable display width
    digitalWrite(pumpPin, LOW);  // Start the pump
    Serial.println("I'm thirsty!");
  } 

  // The soil is too moist
  if (percentage > 80) {
    lcd.print("Refreshing water! "); // Ensure a stable display width
    digitalWrite(pumpPin, HIGH);  // Stop the pump
    Serial.println("Refreshing water!");
  }

  // Update second line only when needed on the LCD
  lcd.setCursor(0, 1);

  // Too dark for the plant
  if (light < photoResistorThreshold) {
    lcd.print("Give me light!     "); // Ensure a stable display width
    Serial.println("Give me light!");
  } 
  // A generous amount of light is received
  else {
    lcd.print("Nice lighting!     "); // Ensure a stable display width
    Serial.println("Nice lighting!");
  }
  Serial.println("\n");

  // Wait for one second
  delay(1000);
}
