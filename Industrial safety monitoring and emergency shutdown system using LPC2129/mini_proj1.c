#include<lpc21xx.h>
#include"lcd_header.h"
#include"uart_header.h"
#define LED   1<<14
#define IR    15
#define MOT_1 1<<18
#define MOT_2 1<<19
void UART0_INIT(void);
void UART0_TX(unsigned char);
void UART0_STR(unsigned char*);
unsigned char a[]="Industrial Safety Monitoring and Emergency Shutdown System Using LPC2129\r\n";
int flag=0,flag1=0;
void INTR_ISR(void) __irq
{
	EXTINT=1<<0;
	flag1=1;
	flag=0;
	VICVectAddr=0;
}
int main()
{
	
	UART0_INIT();
	LCD_INIT();
	PINSEL1|=0X1;
	IODIR0|=LED|IR|MOT_1|MOT_2;
	VICIntSelect=0;
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)INTR_ISR;
	EXTMODE=0X01;
	EXTPOLAR=0X00;
	VICIntEnable=1<<14;
	UART0_STR(a);
	LCD_ROT(a);
	while(1)
	{
		IOSET0=LED;
		if(flag1)
		{
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			LCD_STR("MOTOR OFF");
			UART0_STR("MOTOR OFF\r\n");
			IOCLR0=LED;
			IOCLR0=MOT_1|MOT_2;
			delay_ms(5000);
			flag1=0;
		}
		
		if(flag==0)
		{
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			LCD_STR("MOTOR ON");
			UART0_STR("MOTOR ON\r\n");
			flag=1;
		}
	    if(((IOPIN0>>IR)&1)==0)
	    {
		 	if(flag)
			{
				LCD_CMD(0X01);
				LCD_CMD(0X80);
				LCD_STR("MOTOR OFF");
				UART0_STR("MOTOR OFF\r\n");
				IOCLR0=MOT_1|MOT_2;
				flag=0;
				while(((IOPIN0>>IR)&1)==0);
				
			}
		}
		
		IOSET0=MOT_1;
	    IOCLR0=MOT_2;

		
	}
		
}
