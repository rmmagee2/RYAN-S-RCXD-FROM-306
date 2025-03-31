#include <msp430.h>
#include <string.h>
#include "lcd.h"
#include "ports.h"

static void SPI_send(char byte);
static void LCD_command(char cmd);
static void LCD_data(char data);

// ASCII to position logic could live here later

void Init_LCD(void) {
  // LCD control pins
  P4OUT &= ~LCD_RESET;
  P4DIR |= LCD_RESET;

  P4OUT |= LCD_RESET;

  P4OUT |= LCD_CS;
  P4DIR |= LCD_CS;

  P6OUT |= LCD_BACKLIGHT;
  P6DIR |= LCD_BACKLIGHT;

  // SPI Pins already configured in ports.c:
  // P4.5 = SCLK, P4.6 = SIMO, P4.7 = SOMI

  // SPI Setup (UCB1)
  UCB1CTLW0 = UCSWRST;
  UCB1CTLW0 |= UCSSEL__SMCLK;  // Use SMCLK
  UCB1CTLW0 |= UCCKPH | UCMSB | UCMST | UCSYNC; // 3-pin SPI, MSB first
  UCB1BRW = 0x02;              // Fast as fuck
  UCB1CTLW0 &= ~UCSWRST;

  LCD_command(0x01);  // Clear
  __delay_cycles(3000);
}

// Send SPI byte
static void SPI_send(char byte) {
  while (!(UCB1IFG & UCTXIFG));
  UCB1TXBUF = byte;
  while (!(UCB1IFG & UCRXIFG));  // wait for RX ready (completes TX)
  UCB1RXBUF; // dummy read
}

// Send LCD command byte
static void LCD_command(char cmd) {
  P4OUT &= ~LCD_CS;
  SPI_send(cmd);
  P4OUT |= LCD_CS;
}

// Send LCD data byte (ASCII char)
static void LCD_data(char data) {
  P4OUT &= ~LCD_CS;
  SPI_send(data);
  P4OUT |= LCD_CS;
}

void LCD_Clear(void) {
  LCD_command(0x01); // Clear display
  __delay_cycles(3000);
}

void LCD_Print(char* line1, char* line2, char* line3, char* line4) {
  LCD_Clear();

  LCD_command(0x80); // Line 1
  for (int i = 0; i < strlen(line1); i++) {
    LCD_data(line1[i]);
  }

  LCD_command(0x90); // Line 2
  for (int i = 0; i < strlen(line2); i++) {
    LCD_data(line2[i]);
  }

  LCD_command(0xA0); // Line 3
  for (int i = 0; i < strlen(line3); i++) {
    LCD_data(line3[i]);
  }

  LCD_command(0xB0); // Line 4
  for (int i = 0; i < strlen(line4); i++) {
    LCD_data(line4[i]);
  }
}

