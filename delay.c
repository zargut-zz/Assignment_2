#include "msp.h"
#include "delay.h"
/*
 * Takes two integers, length of time delay in milliseconds and frequency of the system
 * Returns -1 if delay is unachievable or the given frequency does not match the system
 * Returns 0 when successful
 */
int delay_ms(int ms, int frq){
    int i, delay, factor;
    if(frq  ==  FREQ_1_5_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_0)        // Check DCO for 1.5MHz
            return -1;
    }else if( frq == FREQ_3_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_1)        // Check DCO for 3MHz
            return -1;
    }else if( frq == FREQ_6_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_2)        // Check DCO for 6MHz
            return -1;
    }else if(frq == FREQ_12_MHZ){
        factor =11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_3)        // Check DCO for 12MHz
            return -1;
    }else if(frq == FREQ_24_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_4)        // Check DCO for 24MHz
            return -1;
    }else if(frq == FREQ_48_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_5)        // Check DCO for 3MHz
            return -1;
    }
    frq = frq/1000;
    delay = frq*ms/factor;
    if(delay < 1){
        return -1;
    }
    for(i = 0; i < delay; i ++);
    return 0;
}

/*
 * Takes two integers, length of time delay in microseconds and frequency of the system
 * Returns -1 if delay is unachievable or the given frequency does not match the system
 * Returns 0 when successful
 */
int delay_us(int us, int frq){
    int i, delay, factor;
    factor = 0;
    if(frq  ==  FREQ_1_5_MHZ){
        factor = 18;
        if(CS->CTL0 != CS_CTL0_DCORSEL_0)        // Check DCO for 1.5MHz
            return -1;
    }else if( frq == FREQ_3_MHZ){
        factor = 16;
        if(CS->CTL0 != CS_CTL0_DCORSEL_1)        // Check DCO for 3MHz
            return -1;
    }else if( frq == FREQ_6_MHZ){
        factor = 16;
        if(CS->CTL0 != CS_CTL0_DCORSEL_2)        // Check DCO for 6MHz
            return -1;
    }else if(frq == FREQ_12_MHZ){
        factor = 13;
        if(CS->CTL0 != CS_CTL0_DCORSEL_3)        // Check DCO for 12MHz
            return -1;
    }else if(frq == FREQ_24_MHZ){
        factor = 11;
        if(CS->CTL0 != CS_CTL0_DCORSEL_4)        // Check DCO for 24MHz
            return -1;
    }else if(frq == FREQ_48_MHZ){
        factor = 10;
        if(CS->CTL0 != CS_CTL0_DCORSEL_5)        // Check DCO for 3MHz
            return -1;
    }else{
        return -1;
    }
    frq = frq/1000000;
    delay = us*frq/factor;
    if(frq == FREQ_1_5_MHZ){
       delay+= us/10*5;         //Special condition when frequency is 1.5MHz due integer division
    }
    for(i = 0; i < delay; i ++);
    return 0;
}

/*
 * Takes an integer, clock frequency, and sets DCO to the given frequency
 * Returns -1 if the frequency is not 1.5 MHz, 3MHz, 6MHz, 12MHz, 24 MHz, or 48MHz
 * Returns 0 if successful
 */
int setDCO(int frq){
    CS->KEY = CS_KEY_VAL ;                  // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
    if(frq  ==  FREQ_1_5_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_0;        // Set DCO to 1.5MHz
    else if( frq == FREQ_3_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_1;        // Set DCO to 3MHz
    else if( frq == FREQ_6_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_2;        // Set DCO to 6MHz
    else if(frq == FREQ_12_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_3;        // Set DCO to 12MHz
    else if(frq == FREQ_24_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_4;        // Set DCO to 24MHz
    else if(frq == FREQ_48_MHZ)
        CS->CTL0 = CS_CTL0_DCORSEL_5;        // Set DCO to 48MHz
    else
        return -1;
    // Select ACLK = REFO, SMCLK = MCLK = DCO
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0;
    return 0;
}
