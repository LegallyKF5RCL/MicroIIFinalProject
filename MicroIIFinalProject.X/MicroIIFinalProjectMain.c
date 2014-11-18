/* 
 * File:   MicroIIFinalProjectMain.c
 * Author: KF5RCL
 *
 * Created on November 18, 2014, 11:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p33EP128GP502.h>

void StartUp(void);

//Setup Oscilator at nominal 7.37MHz
_FICD(ICS_PGD1 &            //programming pins
        JTAGEN_OFF          //no jtag
        );
_FPOR(ALTI2C1_OFF &
        ALTI2C2_OFF &
        WDTWIN_WIN75
        );
_FWDT(FWDTEN_OFF &          //watchdog timer off
        WDTPOST_PS32768 &   //make it really long incase
        WDTPRE_PR128        //something turns the WDT on
        );
_FOSC(POSCMD_NONE &       //no external osc
        OSCIOFNC_OFF &    //set the pin as a clock out
        IOL1WAY_OFF &     //allow multiple configs
        FCKSM_CSDCMD
        );
_FOSCSEL(FNOSC_FRC &        //start off with RC
        IESO_OFF
        );

int main(int argc, char** argv) {

    StartUp();

    return (EXIT_SUCCESS);
}

