#include<lpc21xx.h>
void UART0_INIT(void);
void UART0_TX(unsigned char);
void UART0_STR(unsigned char*);

void UART0_INIT(void)
{
	PINSEL0|=0X5;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
void UART0_TX(unsigned char txbyte)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=txbyte;
}
void UART0_STR(unsigned char*d)
{
	while(*d)
		UART0_TX(*d++);
}
