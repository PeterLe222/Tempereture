/*
 *  Sigfox module, Arduino UNO, NTC Thermistor 
 *
 *  Version:           1.0
 *  Design:            Le Thi Anh Thu
 *  Implementation:    Le Hoang Viet Anh
 *  
 */ 
 
#include <arduinoClasses.h>
#include <arduinoSigfox.h>
#include <arduinoUART.h>
#include <arduinoUtils.h>

// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Pin definition for Sigfox module error LED:
const int error_led =  13;

//////////////////////////////////////////////
uint8_t socket = SOCKET0;     //Asign to UART0
//////////////////////////////////////////////

uint8_t error;

// define union-type variables
union
{
  uint8_t  value1[4];
  float    value2;
}temp_union;

union
{
  uint8_t  value3[4];
  float    value4;
}temp_union2;

union
{
  uint8_t  value5[4];
  float    value6;
}temp_union3;

// define variable to create a speficic frame to be sent
uint8_t data[12];
uint8_t size;

// define vars for sensors
float temperature;

void setup() 
{
  // start serial port 
  Serial.begin(9600);
  
  Serial.print("Sigfox ID: ");
  Serial.println(Sigfox.getID());
  pinMode(error_led, OUTPUT);
  
  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////
  error = Sigfox.ON(socket);
  
  // Check status
  if( error == 0 ) 
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

void loop() 
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  /********************************************************************/
  Serial.print("Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  Serial.println("DONE"); 
  /********************************************************************/
  Serial.print("Temperature is: "); 
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
  Serial.print("\n"); 
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire
 
  // get temperature
  temperature = sensors.getTempCByIndex(0);
  
  // Fill structure fields
  temp_union.value2 = temperature;
  temp_union2.value4 = 12.45;
  temp_union3.value6 = 42.45;
  
  // fill 'data' buffer with data
  data[0] = temp_union.value1[3]; // big-endian
  data[1] = temp_union.value1[2];
  data[2] = temp_union.value1[1];
  data[3] = temp_union.value1[0];

  // fill 'data' buffer with data
  data[4] = temp_union2.value3[3]; // big-endian
  data[5] = temp_union2.value3[2];
  data[6] = temp_union2.value3[1];
  data[7] = temp_union2.value3[0];

  // fill 'data' buffer with data
  data[8] = temp_union3.value5[3]; // big-endian
  data[9] = temp_union3.value5[2];
  data[10] = temp_union3.value5[1];
  data[11] = temp_union3.value5[0];
  size = 12;
    
  // Send temperature packet
  error = Sigfox.send(data,size);
  Serial.println();
  
  // Check sending status
  if( error == 0 ) 
  {
    //"Sigfox packet sent OK"
    digitalWrite(error_led, LOW);     
  }
  else 
  {
    //"Sigfox packet sent ERROR" 
    digitalWrite(error_led, HIGH);
  } 
  //Sigfox.OFF(socket);
  delay(5000);
  //////////////////////////////////////////////
  // 3. sleep
  //////////////////////////////////////////////
  //Serial.println("Turn On");
  //Sigfox.ON(socket);
}
 
        
