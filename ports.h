#ifndef PORTS_H_
#define PORTS_H_

// === PORT 1 ===
#define RED_LED         BIT0   // P1.0
#define IR_SENSOR_LEFT  BIT2   // P1.2
#define IR_SENSOR_RIGHT BIT3   // P1.3
#define THUMBWHEEL      BIT5   // P1.5
#define UART0_RX        BIT6   // P1.6
#define UART0_TX        BIT7   // P1.7

// === PORT 2 ===
#define IR_EMITTER      BIT2   // P2.2
#define SW2             BIT3   // P2.3
#define IOT_LED_RED     BIT4   // P2.4
#define DAC_ENABLE      BIT5   // P2.5

// === PORT 3 ===
#define IOT_LED_GRN     BIT6   // P3.6
#define IOT_PWR_EN      BIT7   // P3.7

// === PORT 4 ===
#define LCD_RESET       BIT0
#define SW1             BIT1
#define UART1_RX        BIT2
#define UART1_TX        BIT3
#define LCD_CS          BIT4
#define LCD_CLK         BIT5
#define LCD_SIMO        BIT6
#define LCD_SOMI        BIT7

// === PORT 6 ===
#define LCD_BACKLIGHT   BIT0
#define RIGHT_FWD       BIT1
#define RIGHT_REV       BIT2
#define LEFT_FWD        BIT3
#define LEFT_REV        BIT4
#define GREEN_LED       BIT6

void Init_Ports(void);

#endif // PORTS_H_




