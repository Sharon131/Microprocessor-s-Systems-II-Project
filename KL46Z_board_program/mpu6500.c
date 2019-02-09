#include "mpu6500.h"
#include "i2c.h"

const int mpu_addr = 0x68;
const int acceler_reg_addr = 59;
const int gyroscope_reg_addr = 67;

void initialize_mpu(void)
{
		initialize_iic();
}
	
void read_mpu(uint8_t* data)
{
		read_iic(mpu_addr,acceler_reg_addr,6,(uint8_t*)data);
		read_iic(mpu_addr,gyroscope_reg_addr,6,(uint8_t*)(data+6));
}
