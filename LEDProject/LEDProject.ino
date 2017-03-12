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
	while (RFduinoBLE.radioActive); //Don't do anything else if radio is busy
#endif

 //Main program starts here:

  checkBootComplete();
  
 
  
 gbl_systemTimerinMs = millis();
 // checkDebugSendTime();
  
//This code runs when system has finished booting and running nominally
  if (gbl_systemBootFlag){
	  //setState();
	  

	  //TERMINAL_LF(TestTimer.getElapsedTimeMs()); //REMOVE
  }



}



//////////////////Callback and Interrupt functions//////////////////////

#if RGB_DRIVER
void RFduinoBLE_onConnect() {
onRadioConnect();
}

void RFduinoBLE_onDisconnect() {
onRadioDisconnect();  
}
#endif

/////////////////////////////////////////////////////////////////////////
