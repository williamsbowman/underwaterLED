#include "FaultHandler.h"
#include "Globals.h"
#include "SensorManager.h"

#if RGB_DRIVER
#include <RFduinoBLE.h>
#endif

class TimerClass VoltageTimer;
class TimerClass TempErrorTimer;


void processSCFault(void){
	checkSensors();
}



void processRGBFault(void){

}


void ledOverTempBehavior(void){

static bool hitWarningTempBehavior;
static bool hitCriticalTempBehavior;


	if (!hitWarningTempBehavior && sensorFeedback.LEDHitWarningTemp){
		hitWarningTempBehavior = true;
		TempErrorTimer.startTimer();

		#if RGB_DRIVER
		gbl_RGBStatus.blueIntensity = (char)(((float) gbl_RGBStatus.blueIntensity) * (float) LED_OVERTEMP_FIRST_REDUCTION_PERCENTAGE);
		gbl_RGBStatus.greenIntensity = (char)(((float) gbl_RGBStatus.greenIntensity) * (float) LED_OVERTEMP_FIRST_REDUCTION_PERCENTAGE);
		gbl_RGBStatus.redIntensity = (char)((float)(gbl_RGBStatus.redIntensity) * (float)LED_OVERTEMP_FIRST_REDUCTION_PERCENTAGE);

		#else
		gbl_SCStatus.LEDIntensity = (char)((float)(gbl_SCStatus.LEDIntensity) * (float)LED_OVERTEMP_FIRST_REDUCTION_PERCENTAGE);
		#endif

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

		gbl_RGBStatus.blueIntensity = 0;
		gbl_RGBStatus.greenIntensity = 0;
		gbl_RGBStatus.redIntensity = 0;

		for (int i = 0; i<5; i++){
		gbl_RGBStatus.redIntensity = 50;
		delay(1000);
		gbl_RGBStatus.redIntensity = 0;
		delay(1000);
		}
	#endif

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
