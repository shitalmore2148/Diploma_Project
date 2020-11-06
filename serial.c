#include<reg51.h>		
#include"lcd.h"
#include"serial.h"

serial_init()
{
 	
	TMOD=0x20;
	TH1=0xFD;         //9600 BAUD RATE
	SCON=0x50;		  //SERIAL PORT MODE 1, REN=1 SET BY S/W
	TR1=1;
}

unsigned char rx()
{
		unsigned char t;
		while(RI==0);
		t=SBUF;
		RI=0;
		return t;
}



void transmit(unsigned char value)  // Funtion to transmit serial data
{
	SBUF = value;
	while(TI==0);
	delay(10);
	TI=0;
}

void transmit_str (unsigned char *senpoint)
{

  while(*senpoint != '\0')            // While we havent seen a \0 (esc) go on
  {
    transmit(*senpoint);            // Send 1st char to our char function
    senpoint++;                     // Send next
  }

}
