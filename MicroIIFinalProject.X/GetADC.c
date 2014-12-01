#include <generic.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"


UINT16 GetADC(void)
{
//assigning hardcoded values to global variables in place of running the ADC temporarily
    Amp = 1.0;
    Freq = 100;

    return 0;
}
