#include "SensorManager.h"
#include <Arduino.h>
#include "Globals.h"
#include "PinDefinitions.h"
#include "SerialDebug.h"


#if RGB_DRIVER
#include <RFduinoBLE.h>
#endif


class TimerClass VoltageTimer;
class TimerClass TempErrorTimer;

struct sensorFeedback sensorFeedback;



#if RGB_DRIVER
int getRFDuinoTempinC(void){
	return (int)RFduino_temperature(CELSIUS);
}
#endif

int getLEDTempinC(void){
	return (int)(analogRead(LED_BOARD_TEMP_PIN)/ADC_RESOLUTION)*ADC_VOLTAGE_REF;
}

float getInputVoltageinV(void){
	return (int)(analogRead(INPUT_VOLTAGE_PIN)/ADC_RESOLUTION)*ADC_VOLTAGE_REF;
}

void checkSensors(void){

static bool newVoltageFlag = false;


VoltageTimer.timeOutMs = INPUT_VOLTAGE_SAG_TIME_MS;

#if RGB_DRIVER
sensorFeedback.rFDuinoTempinC = getRFDuinoTempinC();

if (sensorFeedback.rFDuinoTempinC > RFDUINO_CRITICAL_TEMP_C){
  sensorFeedback.rFDuinoOverTemp = true; 
}
else{
  sensorFeedback.rFDuinoOverTemp = false;
}
#endif

sensorFeedback.LEDTempinC = getLEDTempinC();

//TIMED_DEBUG DEBUG(Sensor,"LED Temp: ");
//TIMED_DEBUG DEBUG_LF(Sensor,sensorFeedback.rFDuinoTempinC);

if (sensorFeedback.LEDTempinC > LED_WARNING_TEMP_C && sensorFeedback.LEDTempinC  < LED_CRITICAL_TEMP_C){
  sensorFeedback.LEDHitWarningTemp = true;
  sensorFeedback.LEDHitCriticalTemp = false;
}
else{
  sensorFeedback.LEDHitWarningTemp = false;
}


if (sensorFeedback.LEDTempinC > LED_CRITICAL_TEMP_C){
  sensorFeedback.LEDHitWarningTemp = false;
  sensorFeedback.LEDHitCriticalTemp = true;
}
else{
  sensorFeedback.LEDHitCriticalTemp = false;
}

sensorFeedback.inputVoltageinV = getInputVoltageinV();

if (sensorFeedback.inputVoltageinV < INPUT_VOLTAGE_WARNING_V && sensorFeedback.inputVoltageinV > INPUT_VOLTAGE_CRITICAL_V){

  if (!newVoltageFlag){
    VoltageTimer.startTimer();
    newVoltageFlag = true;
  }

  if (VoltageTimer.getElapsedTimeMs() > VoltageTimer.timeOutMs){
   VoltageTimer.stopTimer();
   VoltageTimer.resetTimer();
   newVoltageFlag = false; 
  }
  
  else if (VoltageTimer.getElapsedTimeMs() > INPUT_VOLTAGE_SAG_TIME_MS  && sensorFeedback.inputHitWarningVoltage == false){
    sensorFeedback.inputHitWarningVoltage = true; //this is latched until reset of board
  }

}

//TODO: Have to think about if we want this
//else{  
//  sensorFeedback.inputHitWarningVoltage = false;
//}

else if (sensorFeedback.inputVoltageinV < INPUT_VOLTAGE_CRITICAL_V){
  sensorFeedback.inputHitCriticalVoltage = true; //this is latched until reset of board
  sensorFeedback.inputHitWarningVoltage = false; //this is cleared to take priority for critical voltage
}

}

void ledOverTempBehavior(void){

static bool hitWarningTempBehavior;
static bool hitCriticalTempBehavior;


	if (!hitWarningTempBehavior && sensorFeedback.LEDHitWarningTemp){
		hitWarningTempBehavior = true;
		TempErrorTimer.startTimer();
		gbl_LEDSettings.blueIntensity = (gbl_LEDSettings.blueIntensity) * .75;
		gbl_LEDSettings.greenIntensity = (gbl_LEDSettings.greenIntensity) * .75;
		gbl_LEDSettings.redIntensity = (gbl_LEDSettings.redIntensity) * .75;
	}

	if(TempErrorTimer.getElapsedTimeMs() > 15000){
		if (sensorFeedback.LEDTempinC < LED_WARNING_TEMP_C *.90){
			sensorFeedback.LEDHitWarningTemp = false;
			TempErrorTimer.stopTimer();
			TempErrorTimer.resetTimer();
			hitWarningTempBehavior = false;
		}
		else{
			TempErrorTimer.stopTimer();
			TempErrorTimer.resetTimer();
		}
	}

	if(sensorFeedback.LEDHitCriticalTemp){
	#if RGB_DRIVER
		RFduinoBLE.end();
	#endif
		gbl_LEDSettings.blueIntensity = 0;
		gbl_LEDSettings.greenIntensity = 0;
		gbl_LEDSettings.redIntensity = 0;

		for (int i = 0; i<5; i++){
		gbl_LEDSettings.redIntensity = 50;
		delay(1000);
		gbl_LEDSettings.redIntensity = 0;
		delay(1000);
		}

	}






}

void inputVoltageErrorBehavior(void){

}


void reactToSensors(void){

	if (sensorFeedback.LEDHitWarningTemp || sensorFeedback.LEDHitCriticalTemp){
		ledOverTempBehavior();
	}

	if (sensorFeedback.inputHitWarningVoltage || sensorFeedback.inputHitCriticalVoltage){
		inputVoltageErrorBehavior();
	}

}



