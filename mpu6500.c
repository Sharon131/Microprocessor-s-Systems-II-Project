#include "mpu6500.h"
#include "i2c.h"

void initialize_mpu(void)
{
		initialize_iic();
}
	
void read_mpu(uint8_t* data)
{
		read_iic(0x68,59,6,(uint8_t*)data);
		read_iic(0x68,67,6,(uint8_t*)(data+6));
}
