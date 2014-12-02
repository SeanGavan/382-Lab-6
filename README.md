# 382-Lab-6
## Prelab
![alt text](https://raw.githubusercontent.com/SeanGavan/382-Lab-6/master/Images/Hardware.png "Prelab Schematic")  

![alt text](https://raw.githubusercontent.com/SeanGavan/382-Lab-6/master/Images/MSP430.png "Prelab MSP430")
## Objectives
The goal of the lab was to gain experience with pulse width modulation with the MSP430. It also allowed some hardware setup between the MSP430 and a robot. The software component came into play by making the bot move forward, backward, left, and right.
## Code
```
#include <msp430.h>

void moveForward(void);		// declaring methods for later
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

    	moveForward();		// what the bot will do
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


    } // end loop
} // end main

void enable(void) {			// sets the enables for the motors
    P2OUT |= BIT0;
    P2OUT |= BIT3;
}
void moveForward(void) {

	int t = 0;				// sets time for moving forward
	while (t<0xFFFF){
	    P2OUT |= BIT1;		// L motor CCW
	    P2OUT &= ~BIT5;		// R motor CW
		t++;
	}

    P2OUT &= ~BIT0;			// stop motors to show next step is working
    P2OUT &= ~BIT3;

}

void moveBackward(void) {

    TA1CCR1 = 0x0100;		// set motors to be the same speed
    TA1CCR2 = 0x0100;

	int t = 0;
	while (t<0xFFFF){
	    P2OUT &= ~BIT1;		// L motor CW
	    P2OUT |= BIT5;		// R motor CCW
		t++;
	}

    P2OUT &= ~BIT0;
    P2OUT &= ~BIT3;

    TA1CCR1 = 0x0020;		// set the motors back to normal speed
    TA1CCR2 = 0x0020;

}

void smallLeft(void) {

	int t = 0;
	while (t<0xAFFF){		// less time for <45 degree angle
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
	while (t<0xFFFF){		// more time for a >45 degree angle
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
The biggest ordeal was to overcome hardware issues with the bot and wiring. After coming up with the proper schematics, I then needed to solve the issue of a blown fuse. Capt. Trimble told me to add in more capacitors to divert voltage, and that a fuse needed to be replaced on the bot itself. After solving this issue with Capt. Trimble's help, I was able to continue working on code. From here I needed to work on getting the motors spinning at the same speed. This meant adjusting the PWM intervals so that the wheels turned at the same rate. 
## Testing Methodology 
In order to test the code, I placed the methods required in the while loop. I then tested them one at a time to ensure that the code worked for what I had intended. In order to make sure the timing was right (especially for the turning methods) I created while loops within the methods that would take up time and also accomplish what movement I wanted. After the loops were finished, the motors were turned off so that the bot would stop--showing that another movement method was starting. Once the methods had been shown to work, I had to ensure that they lasted long enough to be evident in the functionality check. This meant slowing the intervals and increasing the time taken by the while loops.
## Observations
Upon conclusion of the lab, the uses of timers has been shown to be quite expansive once again. It also allowed me to gain experience on wiring something and actually implementing the MSP430 using both hardware and software. 
## Documentation
I worked with C2C Kiernan on getting my hardware working. I took his advice on how to wire the circuitry. Capt. Trimble helped me repair a blown fuse on my bot, and more wiring issues. 
