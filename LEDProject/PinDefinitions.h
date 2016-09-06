#ifndef _PINDEFINITIONS_H_
#define _PINDEFINITIONS_H_

//#include "HardwareConfiguration.h"


//TODO: make #if for pin definitions and look into what pins for single driver

#if RGB_DRIVER
/////////////////  RGB PINS ////////////////////////

//RGB LED definitions
#define RED_LED_PIN		2
#define GREEN_LED_PIN 	3
#define BLUE_LED_PIN 	4

//Analog definitions
#define LED_BOARD_TEMP_PIN	0
#define	INPUT_VOLTAGE_PIN	1
/////////////////////////////////////////////////////

#else
/////////////////  SINGLE DRIVER PINS ////////////////////////

//RGB LED definitions
#define RED_LED_PIN		4
#define GREEN_LED_PIN 	5
#define BLUE_LED_PIN 	6

//Analog definitions
#define LED_BOARD_TEMP_PIN	2
#define	INPUT_VOLTAGE_PIN	1
/////////////////////////////////////////////////////

#endif

#endif
