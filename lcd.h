#ifndef LCD_H
#define LCD_H 1

sfr lcd_data_pin = 0x0A0;  // data port P2
sbit rs=P2^0; 	// Register select pin
sbit rw=P2^1; 	// Read write pin
sbit en=P2^2; 	// Enable pin

void lcd_init(void);
void line2(void);
void lcd_clr(void);
void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_datastr(unsigned char *disp); 
void delay(unsigned int msec ); 
#endif
