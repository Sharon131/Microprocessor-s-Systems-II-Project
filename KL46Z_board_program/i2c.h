#include "MKL46Z4.h"

void initialize_iic(void);
void write_iic(uint8_t dev_addr, uint8_t reg_addr, uint8_t nbr_bytes, uint8_t * point);
void read_iic(uint8_t dev_addr, uint8_t reg_addr, uint8_t nbr_bytes, uint8_t * point);
void delay(void);

