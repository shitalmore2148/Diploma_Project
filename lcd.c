#include<reg51.h>		
#include"lcd.h"
#include"serial.h"

 void lcd_init()     //Function to inisialize the LCD
{

		lcd_cmd1(0x03);

			delay(5);
		lcd_cmd1(0x03);
			delay(5);
		lcd_cmd1(0x03);
			delay(5);
		lcd_cmd1(0x02);
			delay(5);//	Set for 4-bit LCD mode
     	lcd_cmd1(0x28);//	Set for 4-bit LCD mode
			delay(5);
		lcd_cmd1(0x08);//	Turn display off
			delay(5);
		lcd_cmd1(0x01);//Clear Disp Screen
			delay(5);
		lcd_cmd1(0x0c);//	Turn on display
			delay(5);
		lcd_cmd1(0x80);
		    delay(5);
  

}
void lcd_clr(void)
 {
 	lcd_cmd1(0x01);
 }


void lcd_cmd(unsigned char comm) // function to send command to LCD
{
    
	lcd_data_pin=comm;
	en=1;
	rs=0;
	rw=0;
	delay(1);
	en=0;
}

void lcd_cmd1(unsigned char value)	// function to send command to LCD in 4 bit mode
{
	
	unsigned char temp;
	P2=0x00;				// set P2 as o/p port as ctrl lines on port P2
	
	temp =value & 0xf0;
	temp =((temp>>1) & 0x78);		  //send higher nibble 
	
	lcd_cmd(temp);
	temp=(value & 0x0f);
	temp=((temp<<3) & 0x78);		  //send lower nibble 


	
	lcd_cmd(temp);
}





void lcd_data(unsigned char disp)    // function to send data on LCD
{
	
	lcd_data_pin=disp;
	en=1;
	rs=1;
	rw=0;
	delay(1);
	en=0;
}




void lcd_data1(unsigned char value)			 // function to send data to LCD in 4 bit mode
{
    
	unsigned char temp;
	P2=0x00;
	
	temp =value & 0xf0;
	temp =((temp>>1) & 0x78);
	
	lcd_data(temp);
	temp=(value & 0x0f);
	temp=((temp<<3) & 0x78);


	//temp= ((value<<4) & 0xf0);
	
	lcd_data(temp);
	
}


void lcd_datastr(unsigned char *disp)    // function to send string to LCD
{
//int x;
	while(*disp!='\0')
	{
		lcd_data1(*disp);
		disp++;

	}

}

void delay(unsigned int msec)    //delay function
{
	int i,j;
	for(i=0;i<msec;i++)
	for(j=0;j<1275;j++);

}




void line2(void)
{
	lcd_cmd1(0xc0);

}

