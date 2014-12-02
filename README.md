# 382-Lab-6
## Prelab
![alt text](https://raw.githubusercontent.com/SeanGavan/382-Lab-6/master/Images/Hardware.png "Prelab Schematic")  

![alt text](https://raw.githubusercontent.com/SeanGavan/382-Lab-6/master/Images/MSP430.png "Prelab MSP430")
## Objectives

## Code
```
#include <msp430.h>

void moveForward(void);
void moveBackward(void);
void smallLeft(void);
void smallRight(void);
void bigLeft(void);
void bigRight(void);
void enable(void);


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
    TA1CCR0 = 0x0100;						// set signal period

    TA1CCR1 = 0x0020;
    TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

    TA1CCR2 = 0x0020;
    TA1CCTL2 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

    while (1) {

    	moveForward();
    	enable();
    	moveBackward();
    	enable();
    	smallLeft();
    	enable();
    	smallRight();
    	enable();
    	bigLeft();
    	enable();
    	bigRight();
    	enable();

//    	if((P1IN & BIT3) != 0){					// if button pressed
//            TA1CCR1 = (TA1CCR1 + 0x010) & 0xFF;	// increase duty cycle
//            TA1CCR2 = (TA1CCR2 + 0x010) & 0xFF;	// decrease duty cycle
//    	}


    } // end loop
} // end main

void enable(void) {
    P2OUT |= BIT0;
    P2OUT |= BIT3;
}
void moveForward(void) {

	int t = 0;
	while (t<0xFFFF){
	    P2OUT |= BIT1;
	    P2OUT &= ~BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;

}

void moveBackward(void) {

    TA1CCR1 = 0x0100;
    TA1CCR2 = 0x0100;

	int t = 0;
	while (t<0xFFFF){
	    P2OUT &= ~BIT1;
	    P2OUT |= BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;

    TA1CCR1 = 0x0020;
    TA1CCR2 = 0x0020;

}

void smallLeft(void) {

	int t = 0;
	while (t<0xAFFF){
		P2OUT &= ~BIT1;
		P2OUT &= ~BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;

}

void smallRight(void) {


	int t = 0;
	while (t<0xAFFF){
		P2OUT |= BIT1;
		P2OUT |= BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;

}

void bigLeft(void) {

	int t = 0;
	while (t<0xFFFF){
		P2OUT &= ~BIT1;
		P2OUT &= ~BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;
}

void bigRight(void) {

	int t = 0;
	while (t<0xFFFF){
		P2OUT |= BIT1;
		P2OUT |= BIT5;
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;
}
```
## Debugging

## Testing Methodology 

## Observations

## Documentation
I worked with C2C Kiernan on getting my hardware working. I took his advice on how to wire the circuitry. Capt. Trimble helped me repair a blown fuse on my bot, and more wiring issues. 
