#ifndef MPU6050
#define MPU6050

#include "i2c.h"
#include "DigitalDevices.h"

// 	Esse driver é baseado no seguinte datasheet
//	https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
// 	Links Uteis:
//	https://controllerstech.com/how-to-interface-mpu6050-gy-521-with-stm32/
//	https://medium.com/@kavindugimhanzoysa/lets-work-with-mpu6050-gy-521-part1-6db0d47a35e6
// 	https://space.stackexchange.com/questions/52354/correcting-accelerometer-readings-when-offset-from-center-of-mass-how
// 	https://ece.montana.edu/seniordesign/archive/SP14/UnderwaterNavigation/kalman_filter.html


#define POWER_MANAGEMENT_CONFIG 0x00 // Essa config ativa o sensor num clock de 8MHz
#define SAMPLE_RATE_CONFIG 0x07 // Sample rate = output rate / (1 + SAMPLE_RATE_CONFIG)
#define ACCEL_CONFIG 0x08 // Configuração do acelerômetro
#define GYRO_CONFIG 0x00 // Configuração do giroscópio

// Endereço registradores internos
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define ACCEL_YOUT_H_REG 0x3D
#define ACCEL_ZOUT_H_REG 0x3F
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define	GYRO_YOUT_H_REG 0x45
#define	GYRO_ZOUT_H_REG 0x47
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75
#define MPU6050_ADDR 0xD0

// Fatores de correção
#define SENSIBILITY_ACC		16384.0 / 2
#define SENSIBILITY_GYRO	131.0 / 1
#define MSB					33024.0

uint8_t MPU6050_acc_raw_data[6]; // [Ax, Ay, Az]
uint8_t MPU6050_gyro_raw_data[6]; // [Gx, Gy, Gz]
float MPU6050_data[6]; // [Ax, Ay, Az, Gx, Gy, Gz]

void MPU6050_init();
void MPU6050_error_handler();

void MPU6050_read();
void MPU6050_selftest();

#endif
