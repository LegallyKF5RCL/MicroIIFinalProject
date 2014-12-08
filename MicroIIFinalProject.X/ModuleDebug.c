#include <stdio.h>
#include <Generic.h>
#include <p33EP128GP502.h>
#include <spi.h>
#include "MicroIIFinalProjectHeader.h"



//DEBUG DEFINES
    //#define UART_TX
    //#define UART_RX
    //#define SPI_DEBUG
    //#define ADC_DEBUG

UINT16 ModuleDebug(void)
{
  
#ifdef UART_TX
#warning DEBUG_MODE_UART_TX_ONLY
        UINT16 i, j; //arbitrary counters
        while(1){
        for(i = 0; i < 0x000F; i++)
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
        UINT16 i, j, TESTING = 0x0000; //arbitrary counters
        while(1){
        for(i = 0; i < 0x0002; i++)
        {
            for(j = 0; j < 0xFFFF; j++)
            {
                asm("NOP");     //blocking wait
            }
        }
        //WriteSPI1(0x5AA5);
        TESTING++;
        SPI1BUF = TESTING;      //write to the SPI Buffer
        }
#endif  //SPI_DEBUG end

#ifdef ADC_DEBUG
        UINT16 i, j; //arbitrary counters
        UINT16 HighByte;
        UINT16 LowByte;
        while(1)
        {
            AD1CON1bits.SAMP = 1;

            for(i = 0; i < 0x0003; i++)
            {
                for(j = 0; j < 0xFFFF; j++)
                {
                    asm("NOP");
                }
            }

            AD1CON1bits.SAMP = 0;
            while(!AD1CON1bits.DONE);
            LATBbits.LATB15 ^= 1;

            LowByte = ADC1BUF0 & 0x00FF;
            HighByte = (ADC1BUF0 & 0xFF00) >> 8;

            U1TXREG = HighByte;
            U1TXREG = LowByte;
            
        }
#endif  //ADC_DEBUG end

return 0; //Return success
}
