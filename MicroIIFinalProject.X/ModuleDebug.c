#include <stdio.h>
#include <Generic.h>
#include <p33EP128GP502.h>
#include "MicroIIFinalProjectHeader.h"


//ALL DEBUG DEFINES LOCATED IN HEADER

UINT16 ModuleDebug(void)
{
#ifdef DEBUG    //lets all other debug routines turn on
                //if not defined, this entire function should be empty
#warning SYSTEM_IN_DEBUG_MODE


       
#ifdef UART_TX
#warning DEBUG_MODE_UART_TX_ONLY
        UINT16 i, j; //arbitrary counters
        while(1){
        for(i = 0; i < 0x0002; i++)
        {
            for(j = 0; j < 0xFFFF; j++)
            {
                asm("NOP");     //blocking wait
            }
        }
        
        U1TXREG = 0x5A;     //UART printout
        }
#endif  //UART_TX end

#ifdef UART_RX          //echo a recieved character
#warning DEBUG_STATE_UART_RX_ONLY
        printf("GO!");
        while(1);       //wait for user input
                        //ISR should handle the echo
#endif  //UART_RX end

#endif  //main debug end


    return 0; //Return success
}
