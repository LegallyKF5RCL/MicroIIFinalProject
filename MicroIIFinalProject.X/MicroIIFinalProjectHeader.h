/* 
 * File:   Globals.h
 * Author: KF5RCL
 *
 * Created on November 24, 2014, 9:40 PM
 */

//DEFINES
#define DIVISIONS 100
#define Fosc        7370000


//GLOBALS
extern UINT8 WaveSelect;
extern UINT8 WaveIndex;
extern UINT16 DacConfig;
extern double Amp;
extern double Multiplier;
extern UINT16 FreqSelect[1024];
extern const UINT8 ConstSinSignalTable[DIVISIONS];
extern const UINT8 ConstSqrSignalTable[DIVISIONS];
extern const UINT8 ConstTriSignalTable[DIVISIONS];
extern UINT8 DoubleSinTable[DIVISIONS];
extern UINT8 DoubleSqrTable[DIVISIONS];
extern UINT8 DoubleTriTable[DIVISIONS];

//FUNCTION DECLARATIONS
UINT16 GetADC(void);
UINT16 UpdateTable(void);
UINT16 SetupADC(void);
UINT16 SetupSPI(void);
void SetupUART(void);
UINT16 ModuleDebug(void);
UINT16 Initialize(void);
void StartUp(void);
void configSPI1(void);
void FreqSelectTable(void);
UINT16 SetupTimer(void);

