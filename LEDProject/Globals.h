
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "States.h"
#include "LEDControlManager.h"
#include "SerialDebug.h"




class TimerClass
{

public:
  TimerClass();
  void startTimer(void);
  void stopTimer(void); 
  void resetTimer(void);
  unsigned long getElapsedTimeMs(void);
  unsigned long timeOutMs;

};

struct FlashMemoryData{
  char driverSerialNumber[12];
  char driverName[11];
  char redLEDValue;
  char greenLEDValue;
  char blueLEDValue;
  unsigned char mode;
  unsigned int modeTiming1;
  unsigned int modeTiming2;
  unsigned int modeTiming3;
  unsigned long int timeOfUseMin;

  bool rfTelemetryEnabled;
  bool serialTelemetryEnabled;
  bool serialDebuggingLevel;
  bool testDataOutputEnabled;
  bool voltageProtectionEnabled;
  bool temperatureProtectionEnabled;
  bool dataRefreshTimeMet;
  unsigned int debugDataRefreshRateMs;
};

extern bool gbl_radioConnectFlag;
extern bool gbl_systemBootFlag;
extern struct LEDControl gbl_LEDSettings;
extern enum States gbl_systemState;
extern struct FlashMemoryData FlashMemoryData;
extern unsigned long gbl_systemTimerinMs;
extern void loadFlashMemoryValues(void);
extern void writeNewTimeofUseToFlash(void);
extern void writeAllSettingsToFlash(void);





#endif
