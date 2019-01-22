
#include "MKL46Z4.h"
#include "uart.h"	
#include "mpu6500.h"

	
int main(void)
{
	struct mpu6500 data;
	initialize_mpu();
	initilize_uart();
	
	while(1)
	{
		read_mpu(&data);
		write_uart(6,(uint8_t*)&data);
		for(uint32_t i=0;i<1500000;i++);
	}
}
