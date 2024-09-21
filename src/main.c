#include <msp430.h>

int main() {
    WDTCTL = WDTPW + WDTHOLD;
    P1OUT = 0x00;
    P1DIR = BIT0 | BIT6; //LED1/2 are outputs
    int counter = 0;
    while(1) {
        counter ++;
        if (counter == 0) {
            P1OUT ^= BIT0 | BIT6;
        }
    }
    return 0;
}