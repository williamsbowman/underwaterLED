#include "LEDControlManager.h"
#include "Globals.h"
#include "PinDefinitions.h"
#include <Arduino.h>




void setRedPWM(char percent){
  analogWrite(RED_LED_PIN, (char)(255*(float)percent/100));  
}


#if RGB_DRIVER

void setRedPWM(char percent){
  analogWrite(RED_LED_PIN, (char)(255*(float)percent/100));
}

void setGreenPWM(char percent){
  analogWrite(GREEN_LED_PIN, (char)(255*(float)percent/100)); 
}
void setBluePWM(char percent){
  analogWrite(BLUE_LED_PIN, (char)(255*(float)percent/100)); 
}

void setRGBColors(void){
  setRedPWM(gbl_RGBStatus.redIntensity);
  setGreenPWM(gbl_RGBStatus.greenIntensity);
  setBluePWM(gbl_RGBStatus.blueIntensity);
}

void onConnectFlash(void){
  setRedPWM(0);
  setGreenPWM(0);
  setBluePWM(50);
  delay(300);
  setBluePWM(0);
}

void onDisconnectFlash(void){
  setRedPWM(50);
  setGreenPWM(0);
  setBluePWM(0);
  delay(300);
  setRedPWM(0);
}

#endif

void setSCIntensity(void){
	setRedPWM(gbl_SCStatus.LEDIntensity);
}


