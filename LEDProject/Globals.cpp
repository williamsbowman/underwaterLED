#include "Globals.h"



unsigned long elapsedTimeMs = 0;
unsigned long startTimeMs = 0;
unsigned long stopTimeMs = 0;

enum States gbl_systemState = Bluetooth_Disconnected;

bool gbl_systemBootFlag = false;
bool gbl_radioConnectFlag = false; //not connected
struct LEDControl gbl_LEDSettings = {0, 0, 0};
unsigned long gbl_systemTimerinMs = 0;

struct FlashMemoryData FlashMemoryData = {};


TimerClass::TimerClass()
{
  timeOutMs = 0;
  elapsedTimeMs = 0;
}

void TimerClass::startTimer(void){
  startTimeMs = gbl_systemTimerinMs;
}
void TimerClass::stopTimer(void){ 
 stopTimeMs = gbl_systemTimerinMs;
}

void TimerClass::resetTimer(void){
elapsedTimeMs = 0;
startTimeMs = 0;
stopTimeMs = 0;  
}

unsigned long TimerClass::getElapsedTimeMs(void){
return (gbl_systemTimerinMs - startTimeMs);
}

void loadFlashMemoryValues(void){

}


