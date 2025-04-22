#ifndef LCD_H_
#define LCD_H_

void Init_LCD(void);

void LCD_Clear(void);
//void LCD_Print(char* line1, char* line2, char* line3, char* line4);
void LCD_Print(const char* str);

#endif // LCD_H_

