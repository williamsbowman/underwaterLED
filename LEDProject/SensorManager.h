#ifndef _SENSORMANAGER_H_
#define _SENSORMANAGER_H_

#define ADC_RESOLUTION	1024
#define ADC_VOLTAGE_REF	3.3

//Thresholds

//Temperatures
#define RFDUINO_CRITICAL_TEMP_C   60  
#define LED_WARNING_TEMP_C        60
#define LED_CRITICAL_TEMP_C       70

//Voltages
#define INPUT_VOLTAGE_WARNING_V   12.7
#define INPUT_VOLTAGE_CRITICAL_V  12.1
#define INPUT_VOLTAGE_SAG_TIME_MS 7000 //This is the time that the analog measurement of the Input voltage has before declaring low

struct sensorFeedback{
      int   rFDuinoTempinC;
      bool  rFDuinoOverTemp; 
      int   LEDTempinC;
      bool  LEDHitWarningTemp;
      bool  LEDHitCriticalTemp; 
      float inputVoltageinV;
      bool  inputHitWarningVoltage;
      bool  inputHitCriticalVoltage;
};

extern sensorFeedback sensorFeedback;

int getRFDuinoTempinC(void);
int getLEDTempinC(void);
int getInputVoltageinmV(void);

void checkSensors(void);
void reactToSensors(void);

void ledOverTempBehavior(void);
void inputVoltageErrorBehavior(void);


#endif
