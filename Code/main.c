#include <msp430.h>

void moveForward(void);
void moveBackward(void);
void smallLeft(void);
void smallRight(void);
void bigLeft(void);
void bigRight(void);


void main(void) {
    WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

    P1DIR &= ~BIT3;
    P1REN |= BIT3;

    P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
    P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

    P2DIR |= BIT4;							// P2.4 is associated with TA1CCR2
    P2SEL |= BIT4;							// P2.4 is associated with TA1CCTL2

    P2DIR |= BIT0;							// Enable for L motor
    P2OUT |= BIT0;

    P2DIR |= BIT1;						    // Set output pin for L motor
    P2OUT |= BIT1;

    P2DIR |= BIT3;							// Enable for R motor
    P2OUT |= BIT3;

    P2DIR |= BIT5;							// Set output pin for R motor
    P2OUT |= BIT5;

	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
    TA1CCR0 = 0x0100;						// set signal period (changed from 0x0100)

    TA1CCR1 = 0x0020;
    TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

    TA1CCR2 = 0x0020;
    TA1CCTL2 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

    while (1) {

//    	moveForward();
//    	moveBackward();
//    	smallLeft();
//    	smallRight();
//    	bigLeft();
//    	bigRight();

    	while((P1IN & BIT3) != 0);			// Wait for a button press
    	while((P1IN & BIT3) == 0);			// and release

        TA1CCR1 = (TA1CCR1 + 0x010) & 0xFF;	// increase duty cycle
        TA1CCR2 = (TA1CCR2 + 0x010) & 0xFF;	// decrease duty cycle

    } // end loop
} // end main

void moveForward(void) {

    P2OUT |= BIT1;
    P2OUT &= ~BIT5;

}

void moveBackward(void) {

    P2OUT &= ~BIT1;
    P2OUT |= BIT5;

}

void smallLeft(void) {

	P2OUT &= ~BIT1;
	P2OUT &= ~BIT5;
}

void smallRight(void) {

	P2OUT |= BIT1;
	P2OUT |= BIT5;
}

void bigLeft(void) {

	P2OUT &= ~BIT1;
	P2OUT &= ~BIT5;
}

void bigRight(void) {

	P2OUT |= BIT1;
	P2OUT |= BIT5;
}

