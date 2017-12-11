#include <OneWire.h>
#include <DallasTemperature.h>

// Create a Onewire Referenca and assign it to pin 8 on your Arduino
OneWire oneWire(2);

// declare as sensor referenec by passing oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// declare your device address
// YOUR ADDRESS GOES HERE!!!!
DeviceAddress tempSensor = {0x28, 0x14, 0xD6, 0x29, 0x08, 0x00, 0x00, 0x9D};
DeviceAddress tempSensor2 = {0x28, 0xDC, 0xE7, 0x29, 0x08, 0x00, 0x00, 0xEA};
DeviceAddress tempSensor3 = {0x28, 0xE2, 0xA5, 0x29, 0x08, 0x00, 0x00, 0x7E};
DeviceAddress tempSensor4 = {0x28, 0x86, 0x1A, 0x2A, 0x08, 0x00, 0x00, 0xC9};
DeviceAddress tempSensor5 = {0x28, 0x3B, 0xD1, 0x29, 0x08, 0x00, 0x00, 0x5E};
DeviceAddress tempSensor6 = {0x28, 0x47, 0xFF, 0x5A, 0x08, 0x00, 0x00, 0xC1};
DeviceAddress tempSensor7 = {0x28, 0x5F, 0x7F, 0x29, 0x08, 0x00, 0x00, 0xD0};

//DeviceAddress tempSensor = {0x28, 0x21, 0x9C, 0x29, 0x08, 0x00, 0x00, 0xCF};
// A Variable to hold the temperature you retrieve
float tempC;
float tempC2;
float tempC3;
float tempC4;
float tempC5;
float tempC6;
float tempC7;


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor2, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor2), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor3, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor3), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor4, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor4), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor5, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor5), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor6, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor6), DEC); 
  Serial.println();
  Serial.print("-----------------");
  // set the resolution to 9 bit - Valid values are 9, 10, or 11 bit.
  sensors.setResolution(tempSensor7, 9);
  // confirm that we set that resolution by asking the DS18B20 to repeat it back
  Serial.print("Sensor Resolution: ");
  Serial.println(sensors.getResolution(tempSensor7), DEC); 
  Serial.println();

}



void loop(void)
{ 
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC = sensors.getTempC(tempSensor);
  
  Serial.print("Temp C1: ");
  Serial.print(tempC,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor2); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC2 = sensors.getTempC(tempSensor2);
  
  Serial.print("Temp C2: ");
  Serial.print(tempC2,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor3); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC3 = sensors.getTempC(tempSensor3);
  
  Serial.print("Temp C3: ");
  Serial.print(tempC3,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor4); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC4 = sensors.getTempC(tempSensor4);
  
  Serial.print("Temp C4: ");
  Serial.print(tempC4,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor5); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC5 = sensors.getTempC(tempSensor5);
  
  Serial.print("Temp C5: ");
  Serial.print(tempC5,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor6); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC6 = sensors.getTempC(tempSensor6);
  
  Serial.print("Temp C6: ");
  Serial.print(tempC6,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  // Tell the Sensor to Measure and Remember the Temperature it Measured
 
  sensors.requestTemperaturesByAddress(tempSensor7); // Send the command to get temperatures
 
  // Get the temperature that you told the sensor to measure
  tempC7 = sensors.getTempC(tempSensor7);
  
  Serial.print("Temp C7: ");
  Serial.print(tempC7,4);  // The four just increases the resolution that is printed
  Serial.println("\n-----------------");
  
  delay(2000);
}

