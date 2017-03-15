
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
  char partNumber[10];
  char driverSerialNumber[8];
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

#if RGB_DRIVER
struct RGBStatus{

	char redIntensity;  //These are in %'s
	char greenIntensity;
	char blueIntensity;
	bool radioConnectFlag;
	bool gbl_RGBdriverFaultFlag;

};

#endif

struct SCStatus{

	char LEDIntensity;
	bool SCdriverFaultFlag;
};





extern bool gbl_systemBootFlag;

#if RGB_DRIVER
extern struct RGBStatus gbl_RGBStatus;
#endif

extern struct SCStatus gbl_SCStatus;

extern enum States gbl_systemState;
extern struct FlashMemoryData FlashMemoryData;
extern unsigned long gbl_systemTimerinMs;







#endif
