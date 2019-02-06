
#include "MKL46Z4.h"
#include "uart.h"	
#include "mpu6500.h"

	
int main(void)
{
	struct mpu6500 data;
	uint8_t array[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
	
	initialize_mpu();
	initilize_uart();
	
	while(1)
	{
		read_mpu(array);
		write_uart(12,array);
		for(uint32_t i=0;i<1000000;i++);
	}
}
