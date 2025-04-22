#include <msp430.h>
#include "ports.h"

void Init_Ports(void) {
    // --- PORT 1 ---
    P1OUT &= ~RED_LED;
    P1DIR |= RED_LED;

    P1SEL0 |= IR_SENSOR_LEFT | IR_SENSOR_RIGHT | THUMBWHEEL;
    P1SEL1 |= IR_SENSOR_LEFT | IR_SENSOR_RIGHT | THUMBWHEEL;

    P1SEL0 |= UART0_TX | UART0_RX;
    P1SEL1 &= ~(UART0_TX | UART0_RX);

    // --- PORT 2 ---
    P2OUT &= ~IR_EMITTER;
    P2DIR |= IR_EMITTER;

    P2OUT &= ~IOT_LED_RED;
    P2DIR |= IOT_LED_RED;

    P2OUT |= DAC_ENABLE;
    P2DIR |= DAC_ENABLE;

    P2DIR &= ~SW2;
    P2REN |= SW2;
    P2OUT |= SW2;

    // --- PORT 3 ---
    P3OUT &= ~(IOT_LED_GRN | IOT_PWR_EN);
    P3DIR |= IOT_LED_GRN | IOT_PWR_EN;

    // --- PORT 4 ---
    P4OUT &= ~(LCD_RESET | LCD_CS);
    P4DIR |= LCD_RESET | LCD_CS;

    P4DIR &= ~SW1;
    P4REN |= SW1;
    P4OUT |= SW1;
    P4IES |= SW1;
    P4IFG &= ~SW1;
    P4IE  |= SW1;

    P4SEL0 |= UART1_TX | UART1_RX | LCD_CLK | LCD_SIMO | LCD_SOMI;
    P4SEL1 &= ~(UART1_TX | UART1_RX | LCD_CLK | LCD_SIMO | LCD_SOMI);

    // Set all unused ports to output low to reduce leakage
    P5OUT = 0; P5DIR = 0xFF;
    PAOUT = 0; PADIR = 0xFF;
    PBOUT = 0; PBDIR = 0xFF;
    PCOUT = 0; PCDIR = 0xFF;

    // --- PORT 6 ---
    P6OUT |= LCD_BACKLIGHT;
    P6DIR |= LCD_BACKLIGHT;

    P6OUT &= ~(RIGHT_FWD | RIGHT_REV | LEFT_FWD | LEFT_REV);
    P6DIR |= (RIGHT_FWD | RIGHT_REV | LEFT_FWD | LEFT_REV);

    P6OUT &= ~GREEN_LED;
    P6DIR |= GREEN_LED;
}

