/* 
 * File:   MicroIIFinalProjectMain.c
 * Author: KF5RCL
 *
 * Created on November 18, 2014, 11:06 AM
 */

#include "pic24_all.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include <Generic.h>
#include <uart.h>
#include "MicroIIFinalProjectHeader.h"
#include "pic24_util.h"


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

double Amp = 0.0;
double Multiplier = 0.0;
UINT16 Freq = 0;
UINT16 FinalFreq = 50;
UINT8 WaveSelect = 1;
UINT8 UpdateIndex;
UINT8 WaveIndex;

UINT16 FreqSelect[1024];

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

double DoubleSinTable[DIVISIONS] = {128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111,
                                    128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111};

UINT8 FinalSinTable[DIVISIONS] = {128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
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

double DoubleSqrTable[DIVISIONS] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

UINT8 FinalSqrTable[DIVISIONS] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
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

double DoubleTriTable[DIVISIONS] = {0, 5, 10, 15, 20, 26, 31, 36, 41, 46,
                                    51, 56, 61, 66, 71, 77, 82, 87, 92, 97,
                                    102, 107, 112, 117, 122, 127, 132, 137, 142, 147,
                                    153, 158, 163, 168, 173, 178, 183, 188, 193, 198,
                                    204, 209, 214, 219, 224, 229, 234, 239, 244, 250,
                                    250, 244, 239, 234, 229, 224, 219, 214, 209, 204,
                                    198, 193, 188, 183, 178, 173, 168, 163, 158, 153,
                                    147, 142, 137, 132, 127, 122, 117, 112, 107, 102,
                                    97, 92, 87, 82, 77, 71, 66, 61, 56, 51,
                                    46, 41, 36, 31, 26, 20, 15, 10, 5, 0};

UINT8 FinalTriTable[DIVISIONS] = {0, 5, 10, 15, 20, 26, 31, 36, 41, 46,
                                    51, 56, 61, 66, 71, 77, 82, 87, 92, 97,
                                    102, 107, 112, 117, 122, 127, 132, 137, 142, 147,
                                    153, 158, 163, 168, 173, 178, 183, 188, 193, 198,
                                    204, 209, 214, 219, 224, 229, 234, 239, 244, 250,
                                    250, 244, 239, 234, 229, 224, 219, 214, 209, 204,
                                    198, 193, 188, 183, 178, 173, 168, 163, 158, 153,
                                    147, 142, 137, 132, 127, 122, 117, 112, 107, 102,
                                    97, 92, 87, 82, 77, 71, 66, 61, 56, 51,
                                    46, 41, 36, 31, 26, 20, 15, 10, 5, 0};

//Setup Oscilator at nominal 7.37MHz
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

    UINT16 i; //arbitrary counters
    UINT16 AnalogData = 0;
    
    INTCON2bits.GIE = 1;

    Initialize();
    StartUp();
    SetupUART();
    SetupSPI();
    //SetupADC();

    CONFIG_RA0_AS_ANALOG();
    CONFIG_RA1_AS_ANALOG();

    ModuleDebug();

    for(i = 0; i < 1024; i++)
    {
        if(i < 12)
        {
            FreqSelect[i] = 50;
        }
        else if(i > 1009)
        {
            FreqSelect[i] = 20000;
        }
        else
        {
            FreqSelect[i] = 50 + (20 * (i - 12));
        }
    }

    printf("\r\nOhayou Gozaimasu Taicho-sama!\r\n");
    printf("\r\nSend '1' for square wave\r\n");
    printf("\r\nSend '2' for sin wave\r\n");
    printf("\r\nSend '3' for triangle wave\r\n");

    while(1)
    {
        configADC1_ManualCH0(RA0_AN, 31, ADC_12BIT_FLAG );
        AnalogData = convertADC1();
        Amp = (double)AnalogData;
        Multiplier = Amp / 0x3FF;
        for(i = 0; i < DIVISIONS; i++)
        {
            switch (WaveSelect)
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
                    printf("\r\nSOMETHING BAD HAPPENED\n\r");
                    break;
            }

        }
        U1TXREG = DoubleSinTable[0];


        configADC1_ManualCH0(RA1_AN, 31, ADC_12BIT_FLAG );
        AnalogData = convertADC1();
        Freq = (double)AnalogData;
        FinalFreq = (UINT16)(Freq * 1024); 
    }
    
    
    return (EXIT_SUCCESS);
}

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

void __attribute__ ((auto_psv))     _ISR  _U1RXInterrupt(void)
{
    UINT16 Hold;

    _U1RXIF = 0;          //clear interrupt flag

    Hold = U1RXREG;

    switch (Hold)
    {
        case 1:
           WaveSelect = 1;
           printf("\r\n\tSquare wave activated...\r\n");
           break;
        case 2:
            WaveSelect = 2;
            printf("\r\n\tSin wave activated...\r\n");
            break;
        case 3:
            WaveSelect = 3;
            printf("\r\n\tTriangle wave activated...\r\n");
            break;
        default:
           printf("\r\nInvalid Input!\r\n");
           printf("\r\n\tSquare wave defaulted!\r\n");
    }

    return;
}
 

