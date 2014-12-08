#include <Generic.h>
#include "MicroIIFinalProjectHeader.h"


void FreqSelectTable(void)
{
    UINT16 i;

    for(i = 0; i < 1024; i++)       //generate frequency table
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

    /*
    for(i = 0; i < 1024; i++)
    {
        Numer = 3685000.0 * DIVISIONS;
        Denom = FreqSelect[i] * 1.0;
        Final = (UINT16)((Numer / Denom) - 1.0);
        FreqSelect[i] = Final;
    }
    */

    return;
}
