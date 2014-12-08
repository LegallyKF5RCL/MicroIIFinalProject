/*
 * Project: MicroII final project
 * Brian McRee
 * 1000736556
 * 12/7/2014
 *
 * File:   MicroIIFinalProjectMain.c
 * Author: KF5RCL
 *
 * Created on November 18, 2014, 11:06 AM
 */

#include "pic24_all.h"
#include <stdio.h>
#include <stdlib.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include <Generic.h>
#include <uart.h>
#include <timer.h>
#include "MicroIIFinalProjectHeader.h"

//#define USE_12BIT_ADC

#ifdef  USE_12BIT_ADC
#define   ADC_LEN           12
#define   ADC_NSTEPS        4096
#define   ADC_12BIT_FLAG    1
#else
#define   ADC_LEN           10
#define   ADC_NSTEPS        1024
#define   ADC_12BIT_FLAG    0
#endif



double Amp = 0.0;                       //Holds floating point amplitude
double Multiplier = 0.0;                //amplitude multiplier
UINT8 WaveSelect = 1;                   //Indicates which of the 3 waves
UINT8 WaveIndex = 0;                    //Index to the signal table arrays
UINT16 DacConfig = 0b0000000100000000;  //Config byte for the DAC
UINT16 FreqSelect[1024];                //table of frequencies


//initialize Max amplitude signal tables
//these are constants to be multiplied down by the ADC factor
const UINT8 ConstSinSignalTable[DIVISIONS] = {128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111,
                                    128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111};

UINT8 DoubleSinTable[DIVISIONS] = {128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111,
                                    128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111};

const UINT8 ConstSqrSignalTable[DIVISIONS] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

UINT8 DoubleSqrTable[DIVISIONS] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const UINT8 ConstTriSignalTable[DIVISIONS] = {0, 5, 10, 15, 20, 26, 31, 36, 41, 46,
                                    51, 56, 61, 66, 71, 77, 82, 87, 92, 97,
                                    102, 107, 112, 117, 122, 127, 132, 137, 142, 147,
                                    153, 158, 163, 168, 173, 178, 183, 188, 193, 198,
                                    204, 209, 214, 219, 224, 229, 234, 239, 244, 250,
                                    250, 244, 239, 234, 229, 224, 219, 214, 209, 204,
                                    198, 193, 188, 183, 178, 173, 168, 163, 158, 153,
                                    147, 142, 137, 132, 127, 122, 117, 112, 107, 102,
                                    97, 92, 87, 82, 77, 71, 66, 61, 56, 51,
                                    46, 41, 36, 31, 26, 20, 15, 10, 5, 0};

UINT8 DoubleTriTable[DIVISIONS] = {0, 5, 10, 15, 20, 26, 31, 36, 41, 46,
                                    51, 56, 61, 66, 71, 77, 82, 87, 92, 97,
                                    102, 107, 112, 117, 122, 127, 132, 137, 142, 147,
                                    153, 158, 163, 168, 173, 178, 183, 188, 193, 198,
                                    204, 209, 214, 219, 224, 229, 234, 239, 244, 250,
                                    250, 244, 239, 234, 229, 224, 219, 214, 209, 204,
                                    198, 193, 188, 183, 178, 173, 168, 163, 158, 153,
                                    147, 142, 137, 132, 127, 122, 117, 112, 107, 102,
                                    97, 92, 87, 82, 77, 71, 66, 61, 56, 51,
                                    46, 41, 36, 31, 26, 20, 15, 10, 5, 0};



_FICD(ICS_PGD1 &            //programming pins
        JTAGEN_OFF          //no jtag
        );
_FPOR(ALTI2C1_OFF &
        ALTI2C2_OFF &
        WDTWIN_WIN75
        );
_FWDT(FWDTEN_OFF &          //watchdog timer off
        WDTPOST_PS32768 &   //make it really long incase
        WDTPRE_PR128        //something turns the WDT on
        );
_FOSC(POSCMD_NONE &       //no external osc
        OSCIOFNC_ON &    //set the pin as a clock out
        IOL1WAY_OFF &     //allow multiple configs
        FCKSM_CSDCMD
        );
_FOSCSEL(FNOSC_FRC &        //start off with RC
        IESO_OFF
        );


int main(int argc, char** argv) {

    UINT16 i, j; //arbitrary counters
    UINT16 AnalogData = 0;  //place holder for ADC
    double Numer;           //place holder for Calculations
    double Denom;           //place holder for Calculations
    UINT16 FreqHold;        //Holds casted periodic reset

    INTCON2bits.GIE = 1;    //enable global interrupts

    //non-working clock select for PLL
    /*
    OSCCONbits.NOSC = 0b001;        //write FRCPLL setting
    OSCCONbits.OSWEN = 1;           //initiate clock switch
    while(OSCCONbits.OSWEN == 1);    //wait for clock switch to finish
    */

    Initialize();       //setupt pins
    StartUp();          //Last line of defense for debugging
    SetupUART();        //Setup uart
    SetupSPI();         //Setup SPI
    SetupTimer();       //Setup timer

    CONFIG_RA0_AS_ANALOG();     //pin setup from textbook
    CONFIG_RA1_AS_ANALOG();     //pin setup from textbook

    ModuleDebug();              //debug routines for chip modules

    FreqSelectTable();          //generate a table of frequencies

    printf("\r\nOhayou Gozaimasu Taicho-sama!\r\n");    //hello world
    printf("\r\nSend '1' for square wave\r\n");
    printf("\r\nSend '2' for sin wave\r\n");
    printf("\r\nSend '3' for triangle wave\r\n");

    while(1)        //loop forever
    {
        configADC1_ManualCH0(RA0_AN, 31, ADC_12BIT_FLAG );      //config ADC for AN0
        AnalogData = convertADC1();         //get ADC
        Amp = (double)AnalogData;           //cast it into a double
        Multiplier = Amp / 0x3FF;           //do some math
        for(i = 0; i < DIVISIONS; i++)      //go through the array
        {
            switch (WaveSelect)             //depending on which array is active
            {
                case 1:
                    DoubleSinTable[i] = (UINT8)(ConstSinSignalTable[i] * Multiplier);
                    break;
                case 2:
                    DoubleSqrTable[i] = (UINT8)(ConstSqrSignalTable[i] * Multiplier);
                    break;
                case 3:
                    DoubleTriTable[i] = (UINT8)(ConstTriSignalTable[i] * Multiplier);
                    break;
                default:
                    printf("\r\nSOMETHING BAD HAPPENED\n\r");       //this should never print out
                    break;
            }
        }

        configADC1_ManualCH0(RA1_AN, 31, ADC_12BIT_FLAG );      //config AN1 for ADC
        AnalogData = convertADC1();             //get the ADC value
        Numer = 3685000.0;                      //this is Fp
        Denom = (double)(FreqSelect[AnalogData] * 1.0 * 2);     //Math to find periodic timer reset
        FreqHold = (UINT16)(((Numer) / (Denom)));               //calculate final timer reset
        
        for(i = 0; i < 0x0008; i++)
        {
            for(j = 0; j < 0xFFFF; j++)
            {
                asm("NOP");     //blocking wait so we dont flood the timer
            }
        }

        T2CONbits.TON = 0;      //turn off the timer
        DisableIntT2;           //disable interrupts
        PR2 = FreqHold;         //change period reset
        EnableIntT2;            //enable interrupts
        T2CONbits.TON = 1;      //turn on the module

        

    }
    
    
    return (EXIT_SUCCESS);
}

//this function is from the adc2pots1 project given by the book
#ifndef BUILT_ON_ESOS // Excluded from ESOS builds due to a busy loop
uint16_t convertADC1(void) {
  uint8_t u8_wdtState;

  //sz_lastTimeoutError = "convertADC1()";
  u8_wdtState = _SWDTEN;                  //save WDT state
  _SWDTEN = 1;                            //enable WDT since we block
  SET_SAMP_BIT_ADC1();                    //start sampling
  asm("NOP");                                  //takes one clock to clear previous DONE flag, delay before checking.
  WAIT_UNTIL_CONVERSION_COMPLETE_ADC1();  //wait for conversion to finish
  _SWDTEN = u8_wdtState;                  //restore WDT
  //sz_lastTimeoutError = NULL;             //reset error message
  return(ADC1BUF0);
}
#endif

void __attribute__ ((auto_psv))     _ISR  _U1RXInterrupt(void)      //ISR for UART RX
{
    char Hold;        //holds input

    _U1RXIF = 0;          //clear interrupt flag

    Hold = U1RXREG;         //load recieved character

    switch (Hold)           //based on the input, change the wave form selector
    {
        case '1':
           WaveSelect = 1;
           printf("\r\n\tSin wave activated...\r\n");
           break;
        case '2':
            WaveSelect = 2;
            printf("\r\n\tSquare wave activated...\r\n");
            break;
        case '3':
            WaveSelect = 3;
            printf("\r\n\tTriangle wave activated...\r\n");
            break;
        default:
           printf("\r\nInvalid Input!\r\n");
           printf("\r\n\tSquare wave defaulted!\r\n");
           break;
    }

    return;
}
 
void __attribute__ ((auto_psv))     _ISRFAST  _T2Interrupt(void)
{
    
    
    LATBbits.LATB15 ^= 1;       //audio test
    
    LATBbits.LATB14 = 0;        //chip select
    switch (WaveSelect)         //depending on the wave selected
    {                           //write to the DAC Config + Data
        case 1:
            SPI1BUF = DacConfig | DoubleSinTable[WaveIndex];
            break;
        case 2:
            SPI1BUF = DacConfig | DoubleSqrTable[WaveIndex];
            break;
        case 3:
            SPI1BUF = DacConfig | DoubleTriTable[WaveIndex];
            break;
        default:
            break;
    }
    LATBbits.LATB14 = 1;        //un-chip select

    WaveIndex++;
    if(WaveIndex >= 100)        //if we have exceeded index bound
    {
        WaveIndex = 0;          //roll it back to 0
    }

    _T2IF = 0;                  //clear the interrupt flag

    return;
}



