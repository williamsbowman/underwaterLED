#ifndef _STATES_H_
#define _STATES_H_


enum States{
  RGB_Disconnected,
  RGB_Connected,
  RGB_Fault,
  SC_Nominal,
  SC_Fault,
  Boot
};


//Interrupt Functions
void onRadioConnect(void);
void onRadioDisconnect(void);
////////////////////

//Startup Functions
void configurePins(void);
void initializeSystem(void);
void printStartUpData(void);
void checkBootComplete(void);
//////

//States checkState(void);
void setState(void);




#endif
