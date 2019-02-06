#include "uart.h"	
	
void initilize_uart(void)
{
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK;
	
	PORTA->PCR[1] = PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_MUX(2);
	
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(2); 		//clock source: OSCERCLK
	UART0->C4 |= UART0_C4_OSR(31); 					//oversampling ratio: 31
	UART0->BDL=26;													//clock divider to obtain 9600 baud
	UART0->BDH&=~UART_BDH_SBNS_MASK;				//one stop bit
	
	//C1 default: one start bit, 8 data bit, 1 stop bit, no parity bit		
	
	UART0->C2 |= UART0_C2_TE_MASK;					//enable uart transmit
	UART0->C2 |= UART0_C2_RE_MASK;					//enable uart receive
}

//uint8_t nbr_bytes -> number of bytes to be send
//uint8_t * point		-> pointer to an array with data

void write_uart(uint8_t nbr_bytes, uint8_t * point)			
{
	for(uint8_t i=0;i<nbr_bytes;i++)
	{
		while(!(UART0->S1& UART0_S1_TDRE_MASK));//wait until end of one byte transmission
		UART0->D=*(point+i);
	}
	
}
