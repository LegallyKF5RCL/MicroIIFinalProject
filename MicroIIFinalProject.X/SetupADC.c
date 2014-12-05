#include <generic.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"

UINT16 SetupADC(void)
{



//AD1CON1: ADC1 Control Register 1
    AD1CON1bits.ADON = 0;   //turn off module
    AD1CON1bits.ADSIDL = 0; //continue in idle mode
    AD1CON1bits.AD12B = 0;  //10-bit operation
    AD1CON1bits.FORM = 0;   //format to integer values
    AD1CON1bits.SSRC = 0x07;    //b'111', internal counter ends sampling and starts conversion
    //AD1CON1bits.SSRC = 0x00;    //b'000', clearing the sample bit ends sampling and starts conversion
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
    AD1CON2bits.CHPS = 0x03;    //Converts all channels
    //AD1CON2bits.BUFS = ?;     //Read only
                                    //1 means access data in first half of the buffer
                                    //0 means access data in second half of the buffer
    //AD1CON2bits.SMPI = ?;     //this is DMA, DoNotCare right now
    AD1CON2bits.BUFM = 1;       //buffer fill mode select
                                    //first half on first interrupt
                                    //second half on next interrupt
    AD1CON2bits.ALTS = 0;       //Alternate Input Sample Mode
                                    //for channel 0 only inputs specified by CH0SA and CH0NA

//AD1CON3: ADC1 Control Register 3
    AD1CON3bits.ADRC = 1;       //ADC uses system clock
    AD1CON3bits.SAMC = 0x0F;    //Auto sample time bits
                                    //b'11111' = 31 TAD
    AD1CON3bits.ADCS = 0x00;    //ADC conversion clock select bits
                                    //Tcy and TAD are 1:1
                                //page 17
                                    //minimum of 75ns
                                    //at clock speed of 7.370MHz
                                    //TCY is 271ns

//AD1CON4: ADC1 Control Register 4
    AD1CON4bits.DMABL = 0x00;   //DMA buffer locations per analog input bits
                                    //DNC right now
                                    //Current setting
                                        //Sets 1 word of buffer to each analog input

//AD1CHS123: ADC1 Input Channel 1, 2, 3 Select Register
    AD1CHS123bits.CH123NB = 0x00;   //CH1,2,3 Negative input for Sample B is Vrefl
    AD1CHS123bits.CH123SB = 0;      //Positive input for Sample B
                                    //CH1 is AN0
                                    //CH2 is AN1
                                    //CH3 is AN2
    AD1CHS123bits.CH123NA = 0x00;   //CH1,2,3 Negative input for Sample A is Vrefl
    AD1CHS123bits.CH123SA = 0;      //Positive input for Sample A
                                    //CH1 is AN0
                                    //CH2 is AN1
                                    //CH3 is AN2

    AD1CHS0bits.CH0NB = 0;          //CH0 negative input is Vrefl for sample B
    AD1CHS0bits.CH0SB = 0x1F;       //CH0 Positive input is AN31 for sample B
    AD1CHS0bits.CH0NA = 0;          //CH0 negative input is Vrefl for sample A
    AD1CHS0bits.CH0SA = 0x1F;       //CH0 positive input is AN31 for Sample A



    AD1CSSH = 0x0000;               //Skip input scan
    AD1CSSL = 0x0000;               //skip input scan
    //AD1PCFGH                      //doesnt exist for this chip?
    //AD1PCFGL                      //doesnt exist for this chip?

    AD1CON1bits.ADON = 1;           //now that things are setup, turn module on
   


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
