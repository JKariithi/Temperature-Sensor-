// Include the libraries we need
// for LCD 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

// for Temperaure
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27,20,4); // setting the address to 0x27 for a 16 chars and 2 line display

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 23

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP); // using pull up instead of the resistor.
  
  // Start up the library
  sensors.begin();
  lcd.init();
  lcd.backlight();
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  delay(1500);
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("Temperature: ");
    lcd.setCursor(0,1);
    lcd.print(tempC);
    Serial.print("Temperature: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}
