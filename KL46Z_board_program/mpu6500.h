#include "MKL46Z4.h"

struct mpu6500{
	uint16_t accel_X;
	uint16_t accel_Y;
	uint16_t accel_Z;
	uint16_t gyro_X;
	uint16_t gyro_Y;
	uint16_t gyro_Z;
};


void initialize_mpu(void);
void read_mpu(uint8_t* data);
