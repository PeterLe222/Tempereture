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

// define variable to create a speficic frame to be sent
uint8_t data[12];
uint8_t size;

// define vars for sensors
float temperature;

void setup() 
{
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
}

void loop() 
{  
  //exapmle temperature
  temperature = 21.51;
  
  // Fill structure fields
  temp_union.value2 = temperature;  
  
  // fill 'data' buffer with data
  data[0] = temp_union.value1[3]; // big-endian
  data[1] = temp_union.value1[2];
  data[2] = temp_union.value1[1];
  data[3] = temp_union.value1[0];
  size = 4;
    
  // Send temperature packet
  error = Sigfox.send(data,4);
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

  delay(5000);
  //////////////////////////////////////////////
  // 3. sleep
  //////////////////////////////////////////////
}
 
        
