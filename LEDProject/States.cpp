#include "States.h"

#include <Arduino.h>
#include <string.h>
#include "PinDefinitions.h"
#include "LEDControlManager.h"
#include "Globals.h"
#include "SensorManager.h"
#include "HardwareConfiguration.h"
#include "SerialDebug.h"


#if RGB_DRIVER
#include <RFduinoBLE.h>
#endif


//struct FlashMemoryData FlashMemoryData;
class TimerClass StartupTimer;

#if RGB_DRIVER

void onRadioConnect(void){
 gbl_radioConnectFlag = true;
 onConnectFlash(); 
 DEBUG(Medium,"Bluetooth Connected - Timestamp: ");
 DEBUG_LF(Medium,gbl_systemTimerinMs);

}

void onRadioDisconnect(void){
 gbl_radioConnectFlag = false;
 onDisconnectFlash(); 
 DEBUG(Medium,"Bluetooth Disconnected - Timestamp: ");
 DEBUG(Medium,gbl_systemTimerinMs);

}

void radioSetup(void){
	RFduinoBLE.deviceName = "PORT LED 1";//TODO: FlashMemoryData.driverName;
	RFduinoBLE.advertisementData = "RGB";
	RFduinoBLE.advertisementInterval = 100; //in milliseconds
	RFduinoBLE.txPowerLevel = +4; //in dB

	//Start Radio
	if (RFduinoBLE.begin() == 0){
	DEBUG_LF(Medium,"Radio Booting...");
	}
}

#endif


void configurePins(void){
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}



void initializeSystem(void){

  configurePins();
  Serial.begin(9600);
  
  setRedPWM(0);
  setGreenPWM(0);
  setBluePWM(0);

  //Read items from flash
  loadFlashMemoryValues();

  FlashMemoryData.serialDebuggingLevel = SerialDebugLevel;
  FlashMemoryData.rfTelemetryEnabled = RF_TELEMETRY_ENABLED;
  FlashMemoryData.serialTelemetryEnabled = SERIAL_TELEMETRY_ENABLED;
  FlashMemoryData.debugDataRefreshRateMs = DEBUG_REFRESH_RATE;


#if RGB_DRIVER
  radioSetup();
#endif


}

void printStartUpData(void){   

	TERMINAL_LF(row1);//delay(10);
	TERMINAL_LF(row2);//delay(10);
	TERMINAL_LF(row3);//delay(10);
	TERMINAL_LF(row4);//delay(10);
	TERMINAL_LF(row5);//delay(10);
	TERMINAL_LF(row6);//delay(10);
	TERMINAL("SOFTWARE VERSION: " SOFTWARE_VERSION " - ");
#if RGB_DRIVER
  TERMINAL_LF("RGB LED DRIVER");
#else
  TERMINAL_LF("SINGLE LED DRIVER");
#endif

  TERMINAL_LF("COMPILE DATE: " __DATE__ " " __TIME__);
  TERMINAL_LF();
#if RGB_DRIVER
  TERMINAL(RFduinoBLE.deviceName);
#else
  TERMINAL("Driver Hardware");
#endif
  TERMINAL_LF(" Running...");


	  TERMINAL("Device Iime of Use (Min): ");
	  TERMINAL_LF(FlashMemoryData.timeOfUseMin);

 
}

void checkBootComplete(void){
  
  if (gbl_systemTimerinMs > 1000 && !gbl_systemBootFlag){
    printStartUpData();  
    delay(500);
    gbl_systemBootFlag = true;
  }
}

// What happens in these states
void blueToothDisconnectedState(void){
	DEBUG_LF(High,"BLUETOOTH DISCONNECTED STATE");
	setRGBColors();
}

void blueToothConnectedState(void){
	DEBUG_LF(High,"BLUETOOTH CONNECTED STATE");
}

void lowPowerState(void){
	DEBUG_LF(High,"LOW POWER STATE");
 
}

/////////////

//How to get into these states

States checkState(void){ //this function checks the current inputs and determines the current state
  enum States newState;
  checkSensors();
  

  if (gbl_radioConnectFlag){
    newState = Bluetooth_Connected;  
  }

  else if (!gbl_radioConnectFlag){
    newState = Bluetooth_Disconnected;   
  }

  else {
    newState = Bluetooth_Disconnected;     
  }
  
  return newState;
}

////////////

//Putting system into these states
void setState(void){
gbl_systemState = checkState(); 

switch (gbl_systemState){

#if RGB_DRIVER
case Bluetooth_Connected:
blueToothConnectedState();
break;


case Bluetooth_Disconnected:
blueToothDisconnectedState();
break;

#endif

case Low_Power:
lowPowerState();
break;

default:
blueToothDisconnectedState();
 break;
}

}

///////////////
