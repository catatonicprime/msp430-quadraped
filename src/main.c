#include <msp430.h>

#define PWM_PERIOD 327
#define MIN_PWM 0
#define MAX_PWM 60


void CPU16Mhz();
void CPU1Mhz();

volatile int pwmlength = PWM_PERIOD; // period of 20ms (I think?)
volatile int position = MIN_PWM; // period of 20ms (I think?)
volatile int desiredPos = MAX_PWM; // period of 20ms (I think?)

/* CCR1 Interrupt*/
#ifdef __GNUC__
__attribute__((interrupt(TIMER0_A1_VECTOR)))
#else
#pragma vector = TIMER0_A1_VECTOR
        __interrupt
#endif
void callBack1(void)
{
  switch(TAIV)
  {
    case 2: //CCR1 interrupt.
      // Derement the current length
      pwmlength--;
      if (!pwmlength) {
        // Time to reset the counters
        pwmlength = PWM_PERIOD;
        position = desiredPos + 1;
        P1OUT ^= BIT6;
        // desiredPos++;
        // if (desiredPos > MAX_PWM) {
        //   desiredPos = MIN_PWM;
        // }
      }
      position--;
      if (!position) {
        P1OUT &= ~BIT6;
      } else {
        P1OUT |= ~BIT6;
      }
      break;
    default:
      break;
  }
  __bic_SR_register_on_exit(0); // no sleep change.
}

int main() {
    // Disable the watchdog timer to prevent regular resets.
    WDTCTL = WDTPW + WDTHOLD;
    CPU16Mhz();

    P1OUT = 0x00;
    P1DIR = BIT0 | BIT6; //LED1/2 are outputs

    TA0CTL = TASSEL_1 | MC_1;
    TA0CCR0 = 1; // Fire for every clock cycle.
    // '>> 1' shifts by 1 bit to the right which halves our base yielding a 
    // 50% duty cycle. We actually neead to be between 5% & 10% though...
    TA0CCR1 = TACCR0;
    TA0CCTL1 |= CCIE; //Enable CCR1 interrupt.
    
    //Low power mode.
    __bis_SR_register(LPM0_bits + GIE);
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