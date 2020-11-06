#include<reg51.h>
#include<stdio.h>
#include<lcd.h>
#include"serial.h"
#define input P0  	//Input port to read the values of ADc

sbit ale=P1^0;  		//address latch enable
sbit oe=P1^3;  			//output enable
sbit sc=P1^1;  			//start conversion
sbit eoc=P1^2;  		//end of conversion

sbit ADD_A=P1^4;  // Address pins for selecting input channels.
sbit ADD_B=P1^5;
sbit ADD_C=P1^6; 

sbit pulse=P3^5;

sbit sw=P3^6;
unsigned int ps; 
typedef void v;
unsigned char buff[16],buff3[18];
unsigned int x_data,y_data,z_data;
bit a=0,b=0,c=0;
v adc_init();
v adc_set();
void sense(); 
v chan0();
void chan1();
v chan2();
void check();
void check_pulse();	
void gsm(void);
void gsm1(void);
void call();

void main()
{
	//adc_init();
	lcd_init();
	serial_init();
	lcd_datastr("Water Distribution");
	line2();
	lcd_datastr("System");
	delay(200);
	while(1)
	{
		//if()
		check_pulse();
	}
}
void check_pulse()
{
	static int count=0;
	lcd_clr();
	lcd_datastr("Scanning....");
	delay(100);			
	count=0;
	while(count<30)
	{
		if(pulse==0)
		{
			ps++;
	     	delay(10);	
		}
		count++;
		lcd_clr();
		sprintf(buff,"Time=%d Sec",count);
		lcd_datastr(buff);
		delay(200);	
	}	
	/*if(ps==8 || ps==9 || 	ps==10)
			ps*=8;
		else if(ps==11 || ps==12 || ps==13)
			ps*=6;
		else if(ps==14 || ps==15 || ps== 16)
			ps*=5;							 
		else if(ps==17 || ps==18 || ps==19)
			ps*=4;*/	
	/*	if(ps>22 || ps<31)
		{
		ps=0;
		}*/
		sprintf(buff,"Pulses=%d",ps);		 
		delay(200);		
		lcd_clr();
		lcd_datastr(buff);	
		delay(200);
		delay(200);
		if(ps>80 || ps<65)
		{
		sprintf(buff3,"Abnormal Beat Rate");
		gsm();
		}
		count=0;
		ps=0;

}
/*void adc_init()
{
	eoc=1;				//conversion completed
	ale=0;
	oe=0;
	sc=0;	
}

v adc_set()
{
	 ale=1;
	 delay(2);
	 sc=1;						//conversion start
	 delay(1);
	 ale=0;
	 delay(1);
	 sc=0;		
	 while(eoc==1);
	 while(eoc==0);
 	 oe=1;
	 if(a==1)			//temp sensor o/p
	 {
	 	x_data=input;
		x_data*=2;		
		x_data=x_data+17;		
		x_data=100-x_data;
	}
	 if(b==1)			//humi sensor o/p
	 {
	 	y_data=input;
		
	}
	  if(c==1)
	 		z_data=input;		//ldr
			//z_data=255-z_data;
	 delay(2);
	 oe=0;
}

void sense()
{
		chan0();
		//chan1();
		lcd_clr();
		sprintf(buff,"T=%dC",x_data);
		lcd_datastr(buff);
		delay(150);

}								 
void chan0()
{
		ADD_A=0;					//channel 0 select
		ADD_B=0;
		ADD_C=0;
		a=1;
		adc_set();	 
		eoc=1;				//conversion completed
		ale=0;
		oe=0;
		sc=0;
		a=0;
}								 
void chan1()
{
		ADD_A=1;					//channel 0 select
		ADD_B=0;
		ADD_C=0;
		b=1;
		adc_set();	 
		eoc=1;				//conversion completed
		ale=0;
		oe=0;
		sc=0;
		b=0;
}								
void check()
{
	if(x_data>42)
	{
		sprintf(buff3,"Body Temp Exceeds");
		call();
		delay(50);
		gsm();
	}
}
void call()
{
		lcd_clr();
	 	lcd_datastr("Calling");
		transmit_str("ATD");	   
		transmit_str("+919075680609");        //Enter mobile number here
		transmit(';');
		transmit(0x0d);
		delay(200);
}*/		
void send(void)
{
  	transmit_str ("AT");
  	transmit(0x0D);
  	delay(200);
	lcd_clr();
	lcd_datastr("Msg sending....");
  	transmit_str ("AT+CMGF=1");
  	transmit (0x0D);
  	delay(200);	
	transmit_str ("AT+CMGS=");
	transmit('"');
	transmit_str ("+919075680609");
	transmit('"');
	transmit(0x0D);
	delay(200);	
	transmit_str (buff3);
	transmit_str ("\n\r");
	transmit(0x1A);
	delay(200);	
	lcd_clr();
	 lcd_datastr("Msg sent....");
	delay(200);
	
}
