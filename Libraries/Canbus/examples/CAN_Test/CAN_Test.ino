/* Welcome to the ECU Reader project. This sketch uses the Canbus library.
It requires the CAN-bus shield for the Arduino. This shield contains the MCP2515 CAN controller and the MCP2551 CAN-bus driver.
A connector for an EM406 GPS receiver and an uSDcard holder with 3v level convertor for use in data logging applications.
The output data can be displayed on a serial LCD.

SK Pang Electronics www.skpang.co.uk

v1.0 28-03-10

Modified by Shawn Hymel @ SparkFun Electronics
October 5, 2015
Removed LCD commands. Only prints to Serial console.

*/

#include <Canbus.h>

#define COMMAND 0xFE
#define CLEAR   0x01
#define LINE0   0x80
#define LINE1   0xC0

int LED = 13;

char buffer[16];
 
void setup() {
  
  pinMode(LED, OUTPUT); 

  Serial.begin(9600);
  Serial.println("ECU Reader");  /* For debug use */
  

  if(Canbus.init(CANSPEED_500))  /* Initialise MCP2515 CAN controller at the specified speed */
  {
    Serial.println("CAN Init ok");
  } else
  {
    Serial.println("Can't init CAN");
  } 
   
  delay(1000); 

}
 

void loop() {
    
  Canbus.ecu_req(ENGINE_RPM,buffer);          /* Request for engine RPM */
  Serial.print("RPM: ");
  Serial.print(buffer);
   
  digitalWrite(LED, HIGH);
   
  Canbus.ecu_req(VEHICLE_SPEED,buffer);
  Serial.print(" Speed: ");
  Serial.print(buffer);
      
  Canbus.ecu_req(ENGINE_COOLANT_TEMP,buffer);
  Serial.print(" Temp: ");
  Serial.print(buffer);
   
  Canbus.ecu_req(MAF_SENSOR,buffer);
  Serial.print(" MAF: ");
  Serial.println(buffer);
    
//  Canbus.ecu_req(O2_VOLTAGE,buffer);
      
   digitalWrite(LED, LOW); 
   delay(50); 

}
