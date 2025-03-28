#ifndef PORTS_H_
#define PORTS_H_

// === PORT 1 ===
#define RED_LED        BIT0   // P1.0
#define IR_SENSOR_L    BIT2   // P1.2 (ADC)
#define IR_SENSOR_R    BIT3   // P1.3 (ADC)
#define THUMBWHEEL     BIT5   // P1.5 (ADC)
#define UART0_RX       BIT6   // P1.6
#define UART0_TX       BIT7   // P1.7

// === PORT 2 ===
#define IR_EMITTER     BIT2   // P2.2
#define SW2            BIT3   // P2.3 (optional button)
#define IOT_LED_RED    BIT4   // P2.4 (optional)

#define DAC_ENABLE     BIT5   // P2.5 (keep enabled if needed)

// === PORT 3 ===
#define IOT_LED_GRN    BIT6   // P3.6 (optional)
#define IOT_PWR_EN     BIT7   // P3.7

// === PORT 4 ===
#define LCD_RESET      BIT0   // P4.0
#define SW1            BIT1   // P4.1
#define UART1_RX       BIT2   // P4.2
#define UART1_TX       BIT3   // P4.3
#define LCD_CS         BIT4   // P4.4
#define LCD_CLK        BIT5   // P4.5
#define LCD_SIMO       BIT6   // P4.6
#define LCD_SOMI       BIT7   // P4.7

// === PORT 6 ===
#define LCD_BACKLIGHT  BIT0   // P6.0
#define RIGHT_FWD      BIT1   // P6.1 (TB3.1)
#define RIGHT_REV      BIT2   // P6.2 (TB3.2)
#define LEFT_FWD       BIT3   // P6.3 (TB3.3)
#define LEFT_REV       BIT4   // P6.4 (TB3.4)
#define GREEN_LED      BIT6   // P6.6

void Init_Ports(void);

#endif // PORTS_H_

