/* 
 * File:   MicroIIFinalProjectMain.c
 * Author: KF5RCL
 *
 * Created on November 18, 2014, 11:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include <Generic.h>
#include <uart.h>
#include "MicroIIFinalProjectHeader.h"

double Amp = 0.0;
UINT16 Freq = 0;
UINT8 WaveSelect = 1;
UINT8 UpdateIndex;
UINT8 WaveIndex;
unsigned int Blah = 0;
//void delay(unsigned long DelayCounter);
//initialize Max amplitude signal tables
//these are constants to be multiplied down by the ADC factor
const UINT16 ConstSinSignalTable[DIVISIONS] = {128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111,
                                    128, 144, 159, 175, 189, 203, 215, 226, 236, 243,
                                    249, 253, 255, 255, 253, 249, 243, 236, 226, 215,
                                    203, 189, 175, 159, 144, 128, 111, 96, 80, 66,
                                    52, 40, 29, 19, 12, 6, 2, 0, 0, 2,
                                    6, 12, 19, 29, 40, 52, 66, 80, 96, 111};

const UINT16 ConstSqrSignalTable[DIVISIONS] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const UINT16 ConstTriSignalTable[DIVISIONS] = {0, 5, 10, 15, 20, 26, 31, 36, 41, 46,
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
        OSCIOFNC_OFF &    //set the pin as a clock out
        IOL1WAY_OFF &     //allow multiple configs
        FCKSM_CSDCMD
        );
_FOSCSEL(FNOSC_FRC &        //start off with RC
        IESO_OFF
        );


int main(int argc, char** argv) {

    Initialize();
    StartUp();
    SetupUART();
    //SetupSPI();
    //SetupADC();
    //ModuleDebug();

    INTCON2bits.GIE = 1;
   
    printf("\r\nGood morning Master!\r\n");
    printf("\r\nRX Loop Back test is about to begin\r\n");
    printf("\r\nIf the Screen Fills with 'a' then it worked\r\n");
    TRISBbits.TRISB6    = 0;
    LATBbits.LATB6      = 0;

    EnableIntU1RX;
    printf("a");

    /*
    while(1){
    if(PORTAbits.RA4 == 0)
    {
        LATBbits.LATB6      = 0;
    }
    }
    */

    //_U1RXIF = 1;

    while(1);
    
    while(1)
    {
        GetADC();
        UpdateTable();
        //U1TXREG = 0x5A;
    }
    
    
    return (EXIT_SUCCESS);
}

void __attribute__ ((auto_psv))     _ISR  _U1RXInterrupt(void)
{
    char Dummy;
    static unsigned int DummyCount = 0;
    _U1RXIF = 0;          //clear interrupt flag
    //LATBbits.LATB6 = 1;
    //printf("ISRGET!");
    Dummy = U1RXREG;      //echo recieved character
    U1TXREG = Dummy;
    if(DummyCount < 1000)
    {
        LATBbits.LATB6      = 0;
        DummyCount++;
    }
    else
    {
        LATBbits.LATB6      = 1;
    }

    

    return;
}

