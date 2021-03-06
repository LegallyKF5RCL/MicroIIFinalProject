#include <Generic.h>
#include <p33EP128GP502.h>
#include <spi.h>
#include <pps.h>

UINT16 SetupSPI(void)
{


    PPSOutput(OUT_FN_PPS_SCK2,OUT_PIN_PPS_RP42);
    PPSOutput(OUT_FN_PPS_SDO2,OUT_PIN_PPS_RP43);



    OpenSPI2(ENABLE_SCK_PIN
            ,
            ENABLE_SDO_PIN &
            FRAME_ENABLE_OFF &          //not using frames
            FIFO_BUFFER_DISABLE &       //single word transmission - fifo not needed
            ENABLE_SDO_PIN &            //use the SPI_DATA_OUT pin for what I can only assume to be the Data out pin...
            SPI_MODE16_ON &             //Communication is 16 bit -> 8 bits of config and 8 bits of data
            SPI_SMP_OFF &               //sample input data in middle of data output time
            SPI_CKE_OFF &               //setting up with clock mode 1 found in the SPI family ref
                                        //transmit happens from idle state to active state
                                        //the Periph reads data on the rising edge of the SCLK
                                        //clock is ACTIVE HIGH (I hope this doesnt destroy everything)
            SLAVE_ENABLE_OFF &          //Dont use slave select
                                        //Page 14 of fam ref told me to in step 3.C
            CLK_POL_ACTIVE_HIGH &       //set clock to active high
            MASTER_ENABLE_ON &          //I AM THE MASTER NOW
            SEC_PRESCAL_1_1 &           //
            PRI_PRESCAL_64_1
            ,
            SPI_ENABLE &                //enable the module
            SPI_IDLE_CON                //continue in idle mode
            );

    ConfigIntSPI2(SPI_INT_DIS & SPI_INT_PRI_3);         //disable interrupts (assuming these are interrupts generated by SDI, which I am not using)

    return 0;
}
