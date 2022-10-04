// "StAuth10184-01: I Kevin Sar, 000390567 certify that this material is my original work. 
// No other person's work has been used without due acknowledgement. I have not made my work available to anyone else."

// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);

// Variable to save deviceAddress to
DeviceAddress deviceAddress;

// Boolean Flags to determine whether sensor is connected or disconnected and to say disconnect ONCE when disconnected
bool isConnected = true;
bool sayItOnce = false;

// Function to print the Device Address of the Temperature Sensor
void printAddress(DeviceAddress deviceAddress) {
    for (uint8_t i = 0; i < 8; i++) {
      if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
    Serial.println("");
  } 

void setup() {

  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin();

  // int Variable to help check whether the Temperature Sensor is connected or not on start
  int checkAddress = DS18B20.getAddress(deviceAddress, oneWireBus);
  Serial.println();
  Serial.println();
  Serial.println("Temperature Application");
  if(checkAddress == 1){
    Serial.print("Found DS18B20 Sensor with address: ");
    printAddress(deviceAddress);
  }

} 
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0);

  // If Temperature is -127 degrees, there is no Temperature Sensor Connected
  if(fTemp == -127){
    isConnected = false;
    if(sayItOnce == false){
      sayItOnce = true;
      Serial.println("No DS18B20 Temperature Sensors Installed!");
    }
  }

  // Anything else, the Temperature is connected
  else {
    isConnected = true;

    if(isConnected == true){
      sayItOnce = false;
    }
    String weatherMsg = "";

    if (fTemp < 10 ) {
      weatherMsg = "Cold!";
    } else if (fTemp > 10 && fTemp <= 15) {
      weatherMsg = "Cool";
    } else if (fTemp > 15 && fTemp <= 25) {
      weatherMsg = "Perfect";
    } else if (fTemp > 25 && fTemp <= 30) {
      weatherMsg = "Warm";
    } else if (fTemp > 30 && fTemp <= 35) {
      weatherMsg = "Hot";
    } else if (fTemp > 35) {
      weatherMsg = "Too Hot!";
    } 
  
    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + weatherMsg); 
  
    // wait 5s (5000ms) before doing this again 
    delay(5000); 
  }
} 