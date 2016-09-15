#include "States.h"
#include "Globals.h"
#include "SerialDebug.h"

//#include "Memory.h" //TODO: remove this
#if RGB_DRIVER
#include <RFduinoBLE.h>
#endif

class TimerClass TestTimer;

//Startup Sequence Only - One time shot
void setup() {
  // put your setup code here, to run once:
  initializeSystem();
}


//Main Loop
void loop() {

#if RGB_DRIVER
	while (RFduinoBLE.radioActive);
#endif

  checkBootComplete();
  
  //Main program starts here:
  
 gbl_systemTimerinMs = millis();
 // checkDebugSendTime();
  

  if (gbl_systemBootFlag){
	  setState();
	  

	  //TERMINAL_LF(TestTimer.getElapsedTimeMs()); //REMOVE
  }



}



//////////////////Callback and Interrupt functions//////////////////////
void RFduinoBLE_onConnect() {
onRadioConnect();
}

void RFduinoBLE_onDisconnect() {
onRadioDisconnect();  
}

/////////////////////////////////////////////////////////////////////////
