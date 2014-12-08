#include <generic.h>
#include <p33EP128GP502.h>
#include <timer.h>
#include "MicroIIFinalProjectHeader.h"


UINT16 SetupTimer(void)
{
    OpenTimer2(T2_ON &
            T2_IDLE_CON &
            T2_GATE_OFF &
            T2_PS_1_1 &
            T2_32BIT_MODE_OFF &
            T2_SOURCE_INT
            ,
            0x0FFF
            );



    ConfigIntTimer2(T2_INT_PRIOR_2 &
            T2_INT_ON);

    return 0;
}
