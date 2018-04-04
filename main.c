#include "msp.h"

    int main(void) {
        int i;

        WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;    // Stop WDT

        // P1.0 set as GPIO
        P1->SEL0 &= ~BIT0;               // Clear bit 0 of the P1->SEL0 register
        P1->SEL1 &= ~BIT0;               // Clear bit 0 of the P1->SEL1 register

        P1->DIR |= BIT0;                 // P1.0 set as output

        while (1){                        // continuous loop

            P1->OUT ^= BIT0;                // Toggle P1.0 LED
            for (i = 20000; i > 0; i--);    // Delay
        }
    }
