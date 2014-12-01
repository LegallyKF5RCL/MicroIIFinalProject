#include <p33EP128GP502.h>
#include <Generic.h>
#include "MicroIIFinalProjectHeader.h"


UINT16 Initialize(void)
{
    TRISA = 0x0000; //initialize all digital outs
    TRISB = 0x0000;
    ANSELA = 0xFFFF;
    ANSELB = 0xFFFF;

    TRISAbits.TRISA4 = 1;   //make the RX pin an input

    return 0;
}

