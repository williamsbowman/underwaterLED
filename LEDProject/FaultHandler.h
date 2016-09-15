
#ifndef _FAULTHANDLER_H_
#define _FAULTHANDLER_H_

#include "Globals.h"

void processSCFault(void);
void processRGBFault(void);


#define LED_OVERTEMP_FIRST_REDUCTION_PERCENTAGE		75


#endif
