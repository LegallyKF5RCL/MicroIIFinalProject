/* 
 * File:   Globals.h
 * Author: KF5RCL
 *
 * Created on November 24, 2014, 9:40 PM
 */

//DEFINES
#define DIVISIONS 100

//DEBUG DEFINES
    #define DEBUG
    //#define UART_TX
    #define UART_RX

//GLOBALS
extern UINT8 WaveSelect;
extern UINT8 UpdateIndex;
extern UINT8 WaveIndex;
extern double Amp;
extern UINT16 Freq;
extern const UINT16 ConstSinSignalTable[DIVISIONS];
extern const UINT16 ConstSqrSignalTable[DIVISIONS];
extern const UINT16 ConstTriSignalTable[DIVISIONS];
extern double SinSignalTable[DIVISIONS];
extern double SqrSignalTable[DIVISIONS];
extern double TriSignalTable[DIVISIONS];

//FUNCTION DECLARATIONS
UINT16 GetADC(void);
UINT16 UpdateTable(void);
UINT16 SetupADC(void);
UINT16 SetupSPI(void);
UINT16 SetupUART(void);
UINT16 ModuleDebug(void);
UINT16 Initialize(void);
void StartUp(void);
