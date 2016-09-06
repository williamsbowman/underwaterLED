#ifndef _STATES_H_
#define _STATES_H_


enum States{
  Bluetooth_Disconnected,
  Bluetooth_Connected,
  Low_Power
};


//Interrupts
void onRadioConnect(void);
void onRadioDisconnect(void);
////////////////////

void configurePins(void);
void initializeSystem(void);
void printStartUpData(void);
void checkBootComplete(void);

//States checkState(void);
void setState(void);




#endif
