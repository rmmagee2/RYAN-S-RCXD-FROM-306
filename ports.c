#include <msp430.h>
#include "ports.h"

void Init_Ports(void) {
    // --- PORT 1 ---
    P1OUT &= ~RED_LED;
    P1DIR |= RED_LED;

    // ADC Inputs: IR L, IR R, Thumbwheel
    P1SEL0 |= IR_SENSOR_LEFT | IR_SENSOR_RIGHT | THUMBWHEEL;
    P1SEL1 |= IR_SENSOR_LEFT | IR_SENSOR_RIGHT | THUMBWHEEL;

    // UART0 TX/RX for PC Debug
    P1SEL0 |= UART0_TX | UART0_RX;
    P1SEL1 &= ~(UART0_TX | UART0_RX);

    // --- PORT 2 ---
    P2OUT &= ~IR_EMITTER;
    P2DIR |= IR_EMITTER;

    P2OUT &= ~IOT_RED_LED;
    P2DIR |= IOT_RED_LED;

    P2OUT |= DAC_ENABLE;    // Power to DAC on
    P2DIR |= DAC_ENABLE;

    P2DIR &= ~SW2;          // Optional input
    P2REN |= SW2;
    P2OUT |= SW2;

    // --- PORT 3 ---
    P3OUT &= ~(IOT_GRN_LED | IOT_PWR_EN);
    P3DIR |= IOT_GRN_LED | IOT_PWR_EN;

    // --- PORT 4 ---
    P4OUT &= ~(LCD_RESET | LCD_CS);
    P4DIR |= LCD_RESET | LCD_CS;

    P4DIR &= ~SW1;
    P4REN |= SW1;
    P4OUT |= SW1;
    P4IES |= SW1;       // High to low
    P4IFG &= ~SW1;
    P4IE  |= SW1;

    // UART1 & LCD SPI Setup
    P4SEL0 |= UART1_TX | UART1_RX | LCD_SCK | LCD_SIMO | LCD_SOMI;
    P4SEL1 &= ~(UART1_TX | UART1_RX | LCD_SCK | LCD_SIMO | LCD_SOMI);

    // --- PORT 6 ---
    P6OUT |= LCD_BACKLIGHT;
    P6DIR |= LCD_BACKLIGHT;

    // Motor PWM Direction Pins (All OFF initially)
    P6OUT &= ~(R_FORWARD | R_REVERSE | L_FORWARD | L_REVERSE);
    P6DIR |= (R_FORWARD | R_REVERSE | L_FORWARD | L_REVERSE);

    P6OUT &= ~GRN_LED;
    P6DIR |= GRN_LED;
}
