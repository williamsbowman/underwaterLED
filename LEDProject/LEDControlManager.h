#ifndef _LEDCONTROLMANAGER_H_
#define _LEDCONTROLMANAGER_H_


void setSCIntensity(void);

void setRedPWM(char percent);
void setGreenPWM(char percent);
void setBluePWM(char percent);
void setRGBColors(void);


void onConnectFlash(void);
void onDisconnectFlash(void);


#endif
