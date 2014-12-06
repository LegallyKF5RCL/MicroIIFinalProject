#include <generic.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"

UINT16 SetupADC(void)
{

    OpenADC1(ADC_MODULE_ON &        //config 1
            ADC_IDLE_CONTINUE &
            ADC_AD12B_10BIT &
            ADC_FORMAT_INTG &
            ADC_SSRC_MANUAL &
            ADC_SIMULTANEOUS &
            ADC_AUTO_SAMPLING_OFF
            ,
            ADC_VREF_AVDD_AVSS &    //config 2
            ADC_SELECT_CHAN_0123 &
            ADC_ALT_BUF_OFF &
            ADC_ALT_INPUT_OFF
            ,
            ADC_SAMPLE_TIME_31 &    //config 3
            ADC_CONV_CLK_SYSTEM &
            ADC_CONV_CLK_1Tcy
            ,
            ADC_DMA_DIS &           //config 4
            ADC_CH123_NEG_SAMPLEB_VREFN &
            ADC_CH123_POS_SAMPLEB_0_1_2 &
            ADC_CH123_NEG_SAMPLEA_VREFN &
            ADC_CH123_POS_SAMPLEA_0_1_2 &
            ADC_CH0_NEG_SAMPLEB_VREFN &
            ADC_CH0_POS_SAMPLEB_AN3 &
            ADC_CH0_NEG_SAMPLEA_VREFN &
            ADC_CH0_POS_SAMPLEA_AN3
            ,
            ENABLE_AN0_ANA &        //configport a
            ENABLE_AN1_ANA
            ,
            ENABLE_AN2_ANA &
            ENABLE_AN3_ANA
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            0x0000
            ,
            SCAN_NONE_16_31
            ,
            SCAN_NONE_0_15
            );

    DisableIntADC1();

/*

//AD1CON1: ADC1 Control Register 1
    AD1CON1bits.ADON = 0;   //turn off module
    AD1CON1bits.ADSIDL = 0; //continue in idle mode
    AD1CON1bits.AD12B = 0;  //10-bit operation
    AD1CON1bits.FORM = 0;   //format to integer values
    AD1CON1bits.SSRC = 0b111;    //b'111', internal counter ends sampling and starts conversion
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
    AD1CON2bits.CHPS = 0b11;    //Converts all channels
    AD1CON2bits.BUFM = 1;       //buffer fill mode select
    AD1CON2bits.ALTS = 0;       //Alternate Input Sample Mode
                                    //for channel 0 only inputs specified by CH0SA and CH0NA

//AD1CON3: ADC1 Control Register 3
    AD1CON3bits.ADRC = 1;       //ADC uses system clock
    AD1CON3bits.SAMC = 0x1F;    //Auto sample time bits
    AD1CON3bits.ADCS = 0x00;    //ADC conversion clock select bits
                                    //Tcy and TAD are 1:1
                                //page 17
                                    //minimum of 75ns
                                    //at clock speed of 7.370MHz
                                    //TCY is 271ns

//AD1CON4: ADC1 Control Register 4
    AD1CON4bits.DMABL = 0x00;   //DMA buffer locations per analog input bits


//AD1CHS123: ADC1 Input Channel 1, 2, 3 Select Register
    AD1CHS123bits.CH123NB = 0b00;   //CH1,2,3 Negative input for Sample B is Vrefl
    AD1CHS123bits.CH123SB = 0;      //Positive input for Sample B
                                        //CH1 is AN0
                                        //CH2 is AN1
                                        //CH3 is AN2
    AD1CHS123bits.CH123NA = 0b00;   //CH1,2,3 Negative input for Sample A is Vrefl
    AD1CHS123bits.CH123SA = 0;      //Positive input for Sample A
                                        //CH1 is AN0
                                        //CH2 is AN1
                                        //CH3 is AN2

    AD1CHS0bits.CH0NB = 0;          //CH0 negative input is Vrefl for sample B
    AD1CHS0bits.CH0SB = 0x00;       //CH0 Positive input is AN31 for sample B
    AD1CHS0bits.CH0NA = 0;          //CH0 negative input is Vrefl for sample A
    AD1CHS0bits.CH0SA = 0b00000;



    AD1CSSH = 0x0000;               //Skip input scan
    AD1CSSL = 0x0000;               //skip input scan
    //AD1PCFGH                      //doesnt exist for this chip?
    //AD1PCFGL                      //doesnt exist for this chip?

    AD1CON1bits.ADON = 1;           //now that things are setup, turn module on

 */

    return 0;
}
