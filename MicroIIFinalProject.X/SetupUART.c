#include <p33EP128GP502.h>
#include <Generic.h>
#include <uart.h>

UINT16 SetupUART(void)
{

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
            //unsigned int ubrg
            );

    return 0;   //return success
}
