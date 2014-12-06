#include <generic.h>
#include <p33EP128GP502.h>
#include <adc.h>
#include "MicroIIFinalProjectHeader.h"

UINT16 SetupADC(void)
{

    /*
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
            ADC_CONV_CLK_128Tcy
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

     */



//AD1CON1: ADC1 Control Register 1
    AD1CON1bits.ADON = 0;           //turn off module
    AD1CON1bits.ADSIDL = 0;         //continue in idle mode
    AD1CON1bits.AD12B = 0;          //10-bit operation
    AD1CON1bits.FORM = 0;           //format to integer values
    AD1CON1bits.SSRC = 0b000;       //b'111', internal counter ends sampling and starts conversion
    AD1CON1bits.SIMSAM = 0;         //sample all channels simultaneously
    AD1CON1bits.ASAM = 0;           //Sampling begins when SAMP is set

//AD1CON2: ADC1 Control Register 2
    AD1CON2bits.VCFG = 0b000;       //Voltage References
    AD1CON2bits.CSCNA = 0;          //do not scan inputs
    AD1CON2bits.CHPS = 0b00;        //converts CH0
    AD1CON2bits.SMPI = 0b0000;      //generates interrupt after completion of every sample/conversion operation
    AD1CON2bits.ALTS = 0;           //Alternate Input Sample Mode

//AD1CON3: ADC1 Control Register 3
    AD1CON3bits.ADRC = 1;       //Clock select
    AD1CON3bits.SAMC = 0x02;    //Auto sample time bits
    AD1CON3bits.ADCS = 0x02;    //ADC conversion clock select bits, doesnt apply when ADRC is 1

//AD1CON4: ADC1 Control Register 4
    AD1CON4bits.DMABL = 0x00;   //DMA buffer locations per analog input bits

//AD1CHS123: ADC1 Input Channel 1, 2, 3 Select Register
    AD1CHS123bits.CH123NB = 0b00;   //CH1,2,3 Negative input for Sample B is Vrefl
    AD1CHS123bits.CH123SB = 1;      //Positive input for Sample B
    AD1CHS123bits.CH123NA = 0b00;   //CH1,2,3 Negative input for Sample A is Vrefl
    AD1CHS123bits.CH123SA = 1;      //Positive input for Sample A

//AD1CHS0: ADCx Input Channel 0 Select Register
    AD1CHS0bits.CH0NB = 0;          //CH0 negative input is Vrefl for sample B
    AD1CHS0bits.CH0SB = 0b00000;       //CH0 Positive input is AN31 for sample B
    AD1CHS0bits.CH0NA = 0;          //CH0 negative input is Vrefl for sample A
    AD1CHS0bits.CH0SA = 0b00000;



    AD1CSSH = 0x0000;               //Skip input scan
    AD1CSSL = 0x0000;               //skip input scan
    //AD1PCFGH                      //doesnt exist for this chip?
    //AD1PCFGL                      //doesnt exist for this chip?

    AD1CON1bits.ADON = 1;           //now that things are setup, turn module on


    return 0;
}
