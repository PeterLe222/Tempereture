/*
    Sigfox module, Arduino UNO, NTC Thermistor

    Version:           1.0
    Design:            Le Thi Anh Thu
    Implementation:    Le Hoang Viet Anh

*/

#include <arduinoClasses.h>
#include <arduinoSigfox.h>
#include <arduinoUART.h>
#include <arduinoUtils.h>

// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE 2

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// declare your device address
// from 1 to 7, 1 is the furthest, 3 meter between each sensor
//DeviceAddress tempSensor_6 = {0x28, 0x14, 0xD6, 0x29, 0x08, 0x00, 0x00, 0x9D};
//DeviceAddress tempSensor_3 = {0x28, 0xDC, 0xE7, 0x29, 0x08, 0x00, 0x00, 0xEA};
//DeviceAddress tempSensor_7 = {0x28, 0xE2, 0xA5, 0x29, 0x08, 0x00, 0x00, 0x7E};
//DeviceAddress tempSensor_2 = {0x28, 0x86, 0x1A, 0x2A, 0x08, 0x00, 0x00, 0xC9};
//DeviceAddress tempSensor_5 = {0x28, 0x3B, 0xD1, 0x29, 0x08, 0x00, 0x00, 0x5E};
//DeviceAddress tempSensor_4 = {0x28, 0x47, 0xFF, 0x5A, 0x08, 0x00, 0x00, 0xC1};
//DeviceAddress tempSensor_1 = {0x28, 0x5F, 0x7F, 0x29, 0x08, 0x00, 0x00, 0xD0};
DeviceAddress tempSensor[7] = {
  {0x28, 0x5F, 0x7F, 0x29, 0x08, 0x00, 0x00, 0xD0}, // sensor 1
  {0x28, 0x86, 0x1A, 0x2A, 0x08, 0x00, 0x00, 0xC9}, // sensor 2
  {0x28, 0xDC, 0xE7, 0x29, 0x08, 0x00, 0x00, 0xEA}, // sensor 3
  {0x28, 0x47, 0xFF, 0x5A, 0x08, 0x00, 0x00, 0xC1}, // sensor 4
  {0x28, 0x3B, 0xD1, 0x29, 0x08, 0x00, 0x00, 0x5E}, // sensor 5
  {0x28, 0x14, 0xD6, 0x29, 0x08, 0x00, 0x00, 0x9D}, // sensor 6
  {0x28, 0xE2, 0xA5, 0x29, 0x08, 0x00, 0x00, 0x7E}  // sensor 7
};
//DeviceAddress tempSensor = {0x28, 0x21, 0x9C, 0x29, 0x08, 0x00, 0x00, 0xCF};
// A Variable to hold the temperature you retrieve
float tempC;

// Pin definition for Sigfox module error LED:
const int error_led =  13;

//////////////////////////////////////////////
uint8_t socket = SOCKET0;     //Asign to UART0
//////////////////////////////////////////////

uint8_t error;

// define union-type variables for sensor 1
union
{
  uint8_t  value1[4];
  float    value2;
} temp_union;


// define variable to create a speficic frame to be sent
uint8_t data[12];
uint8_t size;

void setup()
{
  // start serial port
  Serial.begin(9600);

  Serial.println();
  Serial.print("Sigfox ID: ");
  Serial.println(Sigfox.getID());
  pinMode(error_led, OUTPUT);

  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////
  error = Sigfox.ON(socket);

  // Check status
  if ( error == 0 )
  {
    //"Switch ON OK"
    digitalWrite(error_led, LOW);
  }
  else
  {
    //"Switch ON ERROR"
    digitalWrite(error_led, HIGH);
  }

  // Start up the library
  sensors.begin();

}

// set initial time
unsigned long previousMillis = 0;

// set time to start the function
//int interval = 24 * 60 * 60 * 1000; // 1 time a day

// set time to test 1 second
int interval = 1000;
// set value for i to start the loop
int i;

void loop()
{
  unsigned long currentMillis = millis();

  // start when the time matches the desire
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time in send data
    previousMillis = currentMillis;
    // get temperature
    // Tell the Sensor to Measure and Remember the Temperature it Measured

    for ( i = 0; i < 7; i++)
    {
      sensors.requestTemperaturesByAddress(tempSensor[i]); // Send the command to get temperatures

      // Get the temperature that you told the sensor to measure
      tempC = sensors.getTempC(tempSensor[i]);

      // Fill structure fields
      temp_union.value2 = tempC;


      // fill 'data' buffer with data from sensor 1
      data[0] = temp_union.value1[3]; // big-endian
      data[1] = temp_union.value1[2];
      data[2] = temp_union.value1[1];
      data[3] = temp_union.value1[0];
      uint8_t sensor = i + 1;
      data[4] = sensor;

      size = 5;
      // Send temperature packet
      error = Sigfox.send(data, size);
      Serial.println();

      // Check sending status
      if ( error == 0 )
      {
        //"Sigfox packet sent OK"
        digitalWrite(error_led, LOW);
      }
      else
      {
        //"Sigfox packet sent ERROR"
        digitalWrite(error_led, HIGH);
      }
    }
  }
}


