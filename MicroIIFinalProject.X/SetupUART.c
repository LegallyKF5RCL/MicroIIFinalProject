#include <p33EP128GP502.h>
#include <Generic.h>
#include <uart.h>
#include <pps.h>

#include "MicroIIFinalProjectHeader.h"


UINT16 SetupUART(void)
{

    PPSOutput(OUT_FN_PPS_U1TX, OUT_PIN_PPS_RP37);
    PPSInput(IN_FN_PPS_U1RX, IN_PIN_PPS_RP20);


 OpenUART1(UART_EN &
            UART_IDLE_CON &
            UART_IrDA_DISABLE &
            UART_MODE_SIMPLEX &
            UART_UEN_00 &
            UART_EN_WAKE &
            UART_DIS_LOOPBACK &
            UART_DIS_ABAUD &
            UART_UXRX_IDLE_ONE &
            UART_BRGH_SIXTEEN &
            UART_NO_PAR_8BIT &
            UART_1STOPBIT
            ,
            UART_INT_TX_BUF_EMPTY &
            UART_SYNC_BREAK_DISABLED &
            UART_TX_ENABLE &
            UART_INT_RX_CHAR &
            UART_ADR_DETECT_DIS
            ,
            23
            //BAUD = 9600
            );
 
            U1STAbits.UTXINV = 0;           //make TX active low
            //U1STAbits.URXISEL = 0x00;       //force interrupt on every 8 bits recieved

            ConfigIntUART1(UART_RX_INT_EN &
                    UART_RX_INT_PR4 &
                    UART_TX_INT_DIS
                    );

/*This is a copy of UART setup working for TX
  OpenUART1(UART_EN &
            UART_IDLE_CON &
            UART_IrDA_DISABLE &
            UART_MODE_SIMPLEX &
            UART_UEN_00 &
            UART_EN_WAKE &
            UART_DIS_LOOPBACK &
            UART_DIS_ABAUD &
            UART_UXRX_IDLE_ZERO &
            UART_BRGH_SIXTEEN &
            UART_NO_PAR_8BIT &
            UART_1STOPBIT
            ,
            UART_INT_TX_BUF_EMPTY &
            UART_SYNC_BREAK_DISABLED &
            UART_TX_ENABLE &
            UART_INT_RX_BUF_FUL &
            UART_ADR_DETECT_DIS
            ,
            23
            //BAUD = 9600
            );

            U1STAbits.UTXINV = 0;
            */

    return 0;   //return success
}
