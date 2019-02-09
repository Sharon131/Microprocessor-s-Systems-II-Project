#include "i2c.h"

#define I2C0_IRQn_NBR (IRQn_Type) 8
volatile _Bool status = 0;

void initialize_iic(void)
{
    SIM->SCGC5 |=  SIM_SCGC5_PORTC_MASK; //clock to PTE24 and PTE25 for I2C0
    SIM->SCGC4 |=   SIM_SCGC4_I2C0_MASK; //clock to I2C0
		I2C0->F |= I2C_F_MULT(2); //some kind of clocking mumbo-jumbo
		I2C0->C1 |=I2C_C1_IICEN_MASK;	//iic enable
		I2C0->C1 |=I2C_C1_IICIE_MASK; //interrupt enable
		I2C0->FLT|= I2C_FLT_STOPIE_MASK;//generate interrupt on stop condition
		PORTC->PCR[8] = PORT_PCR_MUX(2); //alternate pin func
		PORTC->PCR[9] = PORT_PCR_MUX(2);
	
		NVIC_SetPriority(I2C0_IRQn_NBR, 2);		
		NVIC_ClearPendingIRQ(I2C0_IRQn_NBR);
		NVIC_EnableIRQ(I2C0_IRQn_NBR);	
}

//uint8_t dev_addr -> i2c device address
//uint8_t reg_addr -> register address to be read
//uint8_t nbr_bytes-> number of bytes to be read
//uint8_t * point		-> pointer to an array where data is to be stored

void read_iic(uint8_t dev_addr, uint8_t reg_addr, uint8_t nbr_bytes, uint8_t * point)
{
	I2C0->C1 |=I2C_C1_TX_MASK;	//master configured in transmit mode
	I2C0->C1 |=I2C_C1_MST_MASK;	//start condition

	I2C0->D = (dev_addr<<1); //send slave addr in write mode
	wait_for_acknowledgement(); //wait until interrupt clears flag

	I2C0->D = reg_addr;	//write slave addr
	wait_for_acknowledgement();
	
	I2C0->C1 |=I2C_C1_RSTA_MASK;	//restart cond
	I2C0->D = (dev_addr<<1)|1;	//send slave addr in read mode
	wait_for_acknowledgement();

	I2C0->C1 &=~I2C_C1_TX_MASK;	//master configured in rx mode
	for(int32_t i=0;i<nbr_bytes;i++)
	{
		if(i==nbr_bytes-1)I2C0->C1 |=I2C_C1_TXAK_MASK;	//last byte must be without ack
		if(i)*(point+i-1) = I2C0->D;else I2C0->D;	//you have to read data from buffer to start reading data from slave, therefore first byte is garbage
		wait_for_acknowledgement();
	}


	I2C0->C1 &=~I2C_C1_MST_MASK;	//first stop transmission in order not to transmit last byte
	*(point+nbr_bytes-1)=I2C0->D; //read last byte 
	I2C0->C1 &=~I2C_C1_TXAK_MASK;
	wait_for_acknowledgement();
}

//uint8_t dev_addr -> i2c device address
//uint8_t reg_addr -> register address to be written
//uint8_t nbr_bytes-> number of bytes to be written
//uint8_t * point		-> pointer to an array where data is stored

void write_iic(uint8_t dev_addr, uint8_t reg_addr, uint8_t nbr_bytes, uint8_t * point)
{
	I2C0->C1 |=I2C_C1_TX_MASK;	//master configured in transmit mode
	I2C0->C1 |=I2C_C1_MST_MASK;	//start condition

	I2C0->D = (dev_addr<<1); //send slave addr in write mode
	wait_for_acknowledgement(); //wait until interrupt clears flag

	I2C0->D = reg_addr;	//write slave addr
	wait_for_acknowledgement();
	
	for(int32_t i=0;i<nbr_bytes;i++)
	{
		I2C0->D = *(point+i);
		wait_for_acknowledgement();
	}

	I2C0->C1 &=~I2C_C1_MST_MASK;	//first stop transmission in order not to transmit last byte
	wait_for_acknowledgement();
}
void wait_for_acknowledgement(void)
{
	while(!status);
	status=0;
}
void I2C0_IRQHandler(void)
{
	I2C0->FLT|= I2C_FLT_STOPF_MASK; //clear stopf flag
	I2C0->S |=I2C_S_IICIF_MASK; // clear interrupt flag
	if((I2C0->S & I2C_S_TCF_MASK))//enter if full byte sent
	{
		status = 1; //clears flag when byte has been sent
	} 
}

