#ifndef _HARDWARECONFIGURATION_H_
#define _HARDWARECONFIGURATION_H_

#include "Globals.h"
#include "SerialDebug.h"



#define SOFTWARE_VERSION "0.0.0"
#define RGB_DRIVER	false //true means RGB driver type and false if single driver type

//This sets the default/startup values of the certain settings

#define RF_TELEMETRY_ENABLED true
#define SERIAL_TELEMETRY_ENABLED true
#define DEBUG_REFRESH_RATE	1000   //This is only applicable to certain things (to not spam serial)


#define row1	"    ____                    __  __                  ______                            __"
#define row2	"   / __ \\____ ___  ______  / /_/ /__  __________   / ____/___  ____  ________  ____  / /______"
#define row3	"  / / / / __ `/ / / / __ \\/ __/ / _ \\/ ___/ ___/  / /   / __ \\/ __ \\/ ___/ _ \\/ __ \\/ __/ ___/"
#define row4	" / /_/ / /_/ / /_/ / / / / /_/ /  __(__  |__  )  / /___/ /_/ / / / / /__/  __/ /_/ / /_(__  )"
#define row5	"/_____/\\__,_/\\__,_/_/ /_/\\__/_/\\___/____/____/   \\____/\\____/_/ /_/\\___/\\___/ .___/\\__/____/"
#define row6	"                                                                           /_/"




#endif
