// lcd.c — Cleaned and integrated display logic
#include <msp430.h>
#include <string.h>
#include <stdint.h>
#include "lcd.h"
#include "ports.h"  // 🔥 REQUIRED to resolve LCD_* macros

char display_line[4][11];

char display_line[4][11] = {
    "          ",
    "          ",
    "          ",
    "          "
};
uint8_t display_changed = 0;
uint8_t update_display = 0;

static void SPI_send(char byte);

static void LCD_setCursor(uint8_t row, uint8_t col);

void Init_LCD(void) {
    P4DIR |= LCD_RESET | LCD_CS;
    P4OUT &= ~LCD_RESET;
    __delay_cycles(10000);
    P4OUT |= LCD_RESET;

    P6OUT |= LCD_BACKLIGHT;
    P6DIR |= LCD_BACKLIGHT;

    UCB1CTLW0 = UCSWRST;
    UCB1CTLW0 |= UCSSEL__SMCLK;
    UCB1CTLW0 |= UCCKPH | UCMSB | UCMST | UCSYNC;
    UCB1BRW = 2;
    UCB1CTLW0 &= ~UCSWRST;

    LCD_command(0x01); // clear
    __delay_cycles(3000);
}

void Display_Process(void) {
    if (!update_display) return;

    uint8_t line;
    uint8_t c;

    for (line = 0; line < 4; line++) {
        LCD_setCursor(line, 0);
        for (c = 0; c < 10; c++) {
            LCD_data(display_line[line][c]);
        }
    }

    display_changed = 0;
    update_display = 0;
}


static void SPI_send(char byte) {
    while (!(UCB1IFG & UCTXIFG));
    UCB1TXBUF = byte;
    while (!(UCB1IFG & UCRXIFG));
    (void)UCB1RXBUF;
}

static void LCD_command(char cmd) {
    P4OUT &= ~LCD_CS;
    SPI_send(cmd);
    P4OUT |= LCD_CS;
}

static void LCD_data(char data) {
    P4OUT &= ~LCD_CS;
    SPI_send(data);
    P4OUT |= LCD_CS;
}

static void LCD_setCursor(uint8_t row, uint8_t col) {
    // Example addresses: line 0 = 0x80, line 1 = 0x90, etc.
    uint8_t addr = 0x80 + row * 0x10 + col;
    LCD_command(addr);
}
