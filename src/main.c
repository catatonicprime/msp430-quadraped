#include <msp430.h>

void CPU16Mhz();
void CPU1Mhz();

int main() {
    // Disable the watchdog timer to prevent regular resets.
    WDTCTL = WDTPW + WDTHOLD;

    
    CPU16Mhz();

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

void CPU16Mhz()
{
  DCOCTL = DCO0 | DCO1;
  BCSCTL1 = RSEL3 | RSEL2 | RSEL1 | RSEL0;
}

void CPU1Mhz()
{
  DCOCTL = DCO0 | DCO1;
  BCSCTL1 = RSEL2 | RSEL1 | RSEL0;
}