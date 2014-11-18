#include <stdio.h>
#include <stdlib.h>

#include <Generic.h>
#include <p33EP128GP502.h>
#include <uart.h>
#include <timer.h>

//#define GPIO_TEST       //all GPIOs digital and high
//#define GPIO_BLINK      //all GPIOs digital and blink every half second


#ifdef GPIO_BLINK
UINT16 i,j,k;
#endif

void StartUp (void)
{
#ifdef GPIO_TEST
#warning DEBUG_GPIO_TEST
    TRISA = 0;
    TRISB = 0;
    AD1PCFGL = 0xFFFF;
    LATA = 0xFFFF;
    LATB = 0xFFFF;
#endif

#ifdef GPIO_BLINK
#warning DEBUG_GPIO_BLINK
    TRISA = 0;          //PORTA - output
    TRISB = 0;          //PORTB - output
    LATA = 0xFFFF;      //write HIGH to all A latches
    LATB = 0xFFFF;      //write HIGH to all B latches
    //AD1PCFGL = 0xFFFF;      //make all gpios digital
    ANSELA = 0xFFFF;
    ANSELB = 0xFFFF;

    while(1)
    {
        
        for(i = 0; i < 0x0001; i++)
        {
            for(j = 0; j < 0xFFFF; j++)
            {
                //for(k = 0; k < 0xFFFF; k++)
                //{
                   asm("NOP");
                //}
            }
        }
        
        LATA ^= 0xFFFF;
        LATB ^= 0xFFFF;

    }
#endif

    return;
}
