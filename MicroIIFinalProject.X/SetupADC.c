#include <generic.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"

UINT16 SetupADC(void)
{

//AD1CON1: ADC1 Control Register 1
    AD1CON1bits.ADON = 1;   //turn on module
    AD1CON1bits.ADSIDL = 0; //continue in idle mode
    AD1CON1bits.AD12B = 0;  //10-bit operation
    AD1CON1bits.FORM = 0;   //format to integer values
    AD1CON1bits.SSRC = 0x07;    //b'111', internal counter ends sampling and starts conversion
    AD1CON1bits.SSRC = 0x00;    //b'000', clearing the sample bit ends sampling and starts conversion
    AD1CON1bits.SIMSAM = 1;     //sample all channels simultaneously
    AD1CON1bits.ASAM = 1;       //Sampling begins immediately after last conversion
                                    //so just sample as much as possible.
                                    //SAMP bit is autoset by hardware
    //AD1CON1bits.SAMP = ?;     //this should be set by hardware from the line above
                                    //but its able to be software written so what does that mean?

//AD1CON2: ADC1 Control Register 2
    AD1CON2bits.VCFG = 0x00;    //Voltage References
                                    //AVDD for Vref-High
                                    //AVSS for Vref-Low
    AD1CON2bits.CSCNA = 0;      //do not scan inputs
                                    //Not sure if this is applicable
    AD1CON2bits.CHPS = 0x00;    //Converts CH0
                                    //so right now we are using one channel
    //AD1CON2bits.BUFS = ?;     //Read only
                                    //1 means access data in first half of the buffer
                                    //0 means access data in second half of the buffer
    //AD1CON2bits.SMPI = ?;     //this is DMA, DoNotCare right now
    AD1CON2bits.BUFM = 1;       //buffer fill mode select
                                    //first half on first interrupt
                                    //second half on next interrupt
    AD1CON2bits.ALTS = 0;       //Alternate Input Sample Mode
                                    //Always use channel input selects for Sample A

//AD1CON3: ADC1 Control Register 3
    AD1CON3bits.ADRC = 1;       //ADC uses internal RC clock
    AD1CON3bits.SAMC = 0x00;    //Auto sample time bits
                                    //b'11111' = 31 TAD
                                    //Need to read up on this
    AD1CON3bits.ADCS = 0x00;    //ADC conversion clock select bits
                                    //Tcy and TAD are 1:1

//AD1CON4: ADC1 Control Register 4
    AD1CON4bits.DMABL = 0x00;   //DMA buffer locations per analog input bits
                                    //DNC right now
                                    //Current setting
                                        //Sets 1 word of buffer to each analog input

//TO BE CONTINUED

    /*
    OpenADC1(//config1
            ADC_MODULE_ON &     //turn on the module
            ADC_IDLE_CONTINUE & //continue in idle mode
            ADC_AD12B_10BIT &    //10 bit mode - 4 channel
            ADC_FORMAT_INTG &        //ADC formatted as unsigned integer
                                    //header says just integer (assuming unsigned)
            ADC_SSRC_AUTO &     //i have no idea what these do
                                //I need to read family ref
                                //until then ill just try to fill out the config
            ADC_SIMULTANEOUS &  //sample all channels imultaneously
            ADC_AUTO_SAMPLING_ON      //keep sampling over and over
            ,
            //config2
            ,
            //config3
            ,
            //config4
            ,
            //configport_l
            ,
            //configport_h
            ,
            //configscan_h
            ,
            //configscan_l
            );
    */

    return 0;
}
