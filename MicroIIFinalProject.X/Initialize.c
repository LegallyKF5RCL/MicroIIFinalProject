#include <p33EP128GP502.h>
#include <Generic.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"


UINT16 Initialize(void)
{
    TRISA = 0x0000; //initialize all digital outs
    TRISB = 0x0000;
    ANSELA = 0xFFFF;
    ANSELB = 0xFFFF;
    LATA = 0x0000;
    LATB = 0x0000;

    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA0 = 0;       //Make AN0 analog
    ANSELAbits.ANSA1 = 0;       //Make AN1 analog



    TRISBbits.TRISB4 = 1;   //make the RB4 pin a digital input (RX)
    TRISBbits.TRISB9 = 1;   //make RB9 a digital input (SDI)

    return 0;
}

