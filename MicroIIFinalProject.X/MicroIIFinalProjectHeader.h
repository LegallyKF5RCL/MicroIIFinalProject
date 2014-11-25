/* 
 * File:   Globals.h
 * Author: KF5RCL
 *
 * Created on November 24, 2014, 9:40 PM
 */

//DEFINES
#define DIVISIONS 1

//GLOBALS
double Amp;
UINT16 Freq;
UINT16 SignalTable[DIVISIONS] = {0x00};

//FUNCTION DECLARATIONS
UINT16 GetADC(void);
UINT16 UpdateTable(double AmpUpdate, UINT16 FreqUpdate);
UINT16 SetupADC(void);
void StartUp(void);
