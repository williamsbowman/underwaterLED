/*
 * SerialDebug.h
 *
 *  Created on: Feb 3, 2016
 *      Author: scott
 */


#ifndef SERIALDEBUG_H_
#define SERIALDEBUG_H_

#include "HardwareConfiguration.h"

#define TERMINAL_LF Serial.println
#define TERMINAL Serial.print
#define DEBUG_LF(level,message) if(SerialDebugLevel!=Off && level <= SerialDebugLevel) Serial.println(message)
#define DEBUG(level,message) if(SerialDebugLevel!=Off && level <= SerialDebugLevel) Serial.print(message)
#define TIMED_DEBUG if(FlashMemoryData.dataRefreshTimeMet)



enum DebugLevels
{
	Off,
	Sensor,
	Low,
	Medium,
	High

};

extern enum DebugLevels SerialDebugLevel;

void checkSerial(void);
void checkDebugSendTime(void);


#endif /* SERIALDEBUG_H_ */
