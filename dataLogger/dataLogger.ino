#include <mcp_can.h>
#include <SPI.h>
#include <SD.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10

File dataFile;

void setup()
{
  Serial.begin(115200);
  
  if (SD.begin(4)) // Pin 4 is used for SD card module
    Serial.println("SD card initialized successfully");
  else
    Serial.println("Error initializing SD card...");
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  Serial.println("MCP2515 Library Receive Example...");
  
  
}

int volt, motor_Speed, current, temp_cont, temp_mot;
float throttle;
char strThrottle[5];

void loop()
{
  if(!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    if((rxId & 0x1FFFFFFF) == 0x0CF11E05 ){
      motor_Speed = (rxBuf[1]*256 + rxBuf[0]);
      volt = (rxBuf[5]*256 + rxBuf[4])/10;
      current = (rxBuf[3]*256 + rxBuf[2])/10;
	  
	  logData();
    }
    else if((rxId & 0x1FFFFFFF) == 0x0CF11F05 ){
      throttle = rxBuf[0];
      throttle = throttle/51.0;
      temp_cont = rxBuf[1]-40;
	  temp_mot = rxBuf[2]-30;
	  
	  logData();

      //디버깅용
      dtostrf(throttle, 3, 2, strThrottle);
    }
    
    //디버깅용
    sprintf(msgString, "Throttle : %s ControllerTemp : %d BatVolt : %d MotorCurrent : %d motorSpeed : %d", strThrottle, temp_cont, volt, current, motor_Speed );
  } Serial.println(msgString);
}

void logData()
{
	dataFile = SD.open("data.csv", FILE_WRITE);
	  if(dataFile)
	  {
		  dataFile.print(motor_Speed);
		  dataFile.print(", ");
		  dataFile.print(throttle);
		  dataFile.print(", ");
		  dataFile.print(volt);
		  dataFile.print(", ");
		  dataFile.print(temp_cont);
		  dataFile.print(", ");
		  dataFile.print(temp_mot);
		  dataFile.print(", ");
		  dataFile.print("\n");
	  }
	  dataFile.close();
}
