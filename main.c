#include "msp.h"
#include "delay.h"

int main(void) {
    int FREQ;
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;    // Stop WDT

    // P1.0 set as GPIO
    P1->SEL0 &= ~BIT0;               // Clear bit 0 of the P1->SEL0 register
    P1->SEL1 &= ~BIT0;               // Clear bit 0 of the P1->SEL1 register

    P2->SEL0 &= ~BIT0;               // Clear bit 0 of the P1->SEL0 register
    P2->SEL1 &= ~BIT0;               // Clear bit 0 of the P1->SEL1 register

    P1->DIR |= BIT0;                 // P1.0 set as output
    P2->DIR |= BIT0;                 // P2.0 set as output

    P2->OUT &= ~BIT0;                //Clear P2.0 LED

    FREQ = FREQ_12_MHZ;
    if(setDCO(FREQ) == -1){
       return -1;
    }
    while (1)                        // continuous loop
   {
       P1->OUT ^= BIT0;                // Toggle P1.0 LED
       if(delay_us(70, FREQ ) == -1){
           P2->OUT |= BIT0; //SET LED2 when delay is unachievable
       }
   }
//    int i;
//    for(i = 0; i < 5; i++){ // Hard coded for 2 pulses
//        P1->OUT ^= BIT0;                // Toggle P1.0 LED
//       if(delay_us(100, FREQ ) == -1){
//           P2->OUT |= BIT0; //SET LED2 when delay is unachievable
//       }
//     }
//    while (1)                        // continuous loop
//    {
//        P1->OUT ^= BIT0;                // Toggle P1.0 LED
//        if(delay_us(1000000, FREQ ) == -1){
//            P2->OUT |= BIT0; //SET LED2 when delay is unachievable
//        }
//    }

}
