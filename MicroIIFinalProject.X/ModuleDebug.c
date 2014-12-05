#include <stdio.h>
#include <Generic.h>
#include <p33EP128GP502.h>
#include <spi.h>
#include "MicroIIFinalProjectHeader.h"



//DEBUG DEFINES
    //#define DEBUG
    //#define UART_TX
    //#define UART_RX
    //#define SPI_DEBUG
    #define ADC_DEBUG

UINT16 ModuleDebug(void)
{
  
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

#ifdef SPI_DEBUG
#warning DEBUG_MODE_SPI_ONLY
        UINT16 i, j; //arbitrary counters
        while(1){
        for(i = 0; i < 0x0002; i++)
        {
            for(j = 0; j < 0xFFFF; j++)
            {
                asm("NOP");     //blocking wait
            }
        }
        WriteSPI1(0x5AA5);
        //SPI1BUF = 0x5AA5;     //write to the SPI Buffer
        }
#endif  //SPI_DEBUG end

#ifdef ADC_DEBUG
        UINT16 i, j; //arbitrary counters
        while(1)
        {
            AD1CON1bits.SAMP = 1;
            for(i = 0; i < 0x0002; i++)
            {
                for(j = 0; j < 0xFFFF; j++)
                {
                    asm("NOP");     //blocking wait
                }
            }
            AD1CON1bits.SAMP = 0;
            //LATBbits.LATB12 = 1;
            //U1TXREG = ADC1BUF0 << 6;
            U1TXREG = ADC1BUF0;
            
        }
#endif  //ADC_DEBUG end

return 0; //Return success
}
