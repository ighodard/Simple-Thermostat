#include <math.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int dangerLed = 13;
const int thermistorPin = A0;


const float seriesResistor = 10000.0; // Series resistor
const float nominalResistance = 1000.0; // thermistor resistance @ 25 degrees
const float nominalTemperature = 25.0; 
const float betaCoefficient = 3950.0; // Beta value according to the Seller



void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  
lcd.setCursor(0,0);
lcd.print("Temperature:");

}

void loop() {
  int reading = analogRead(thermistorPin);

float resistance = seriesResistor / (1023.0 / reading - 1.0);

  // Applying the Steinhart-Hart equation 
float steinhart = resistance / nominalResistance;
steinhart = log(steinhart);
steinhart /= betaCoefficient;
steinhart += 1.0 / (nominalTemperature + 273.15);
steinhart = 1.0 / steinhart;
steinhart -= 273.15; // Kelvin to Degrees celsius

lcd.setCursor(0,1);
lcd.print(steinhart);
lcd.print(" Degrees");


Serial.print("  Temperature: ");
Serial.print(steinhart);

Serial.print(" C");


delay(500);
}




