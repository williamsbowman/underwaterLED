/*
 * SerialDebug.c
 *
 *  Created on: Feb 3, 2016
 *      Author: scott
 */

#include "SerialDebug.h"

enum DebugLevels SerialDebugLevel = Low;

void checkSerial(void){


	//while (Serial.print("foo")){

	//}
}

void checkDebugSendTime(void)
{
	static unsigned int timeCheck = 0;

	if(gbl_systemTimerinMs-timeCheck > FlashMemoryData.debugDataRefreshRateMs)
	{
		FlashMemoryData.dataRefreshTimeMet = true;
		timeCheck = gbl_systemTimerinMs;
	}

	else
	{
		FlashMemoryData.dataRefreshTimeMet = false;
	}
}




