#include "MPU6050.h"

void MPU6050_init()
{
	// Leitura do registrador who-am-i
	// caso dê errado tem algum problema no acelerometro
	uint8_t check;
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);
	if (check != 0x68) {MPU6050_error_handler();}

	// Configuração do registrador de power management
	uint8_t data = POWER_MANAGEMENT_CONFIG;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&data, 1, 1000);

	// Configuração de sample rate
	data = SAMPLE_RATE_CONFIG;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000);

	// Configuração do acelerometro
	data = ACCEL_CONFIG;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);

	// Configuração de sample rate
	data = SAMPLE_RATE_CONFIG;
	HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);
}

void MPU6050_error_handler()
{
	while(1)
	{
		ligar_led_embutido();
		HAL_Delay(200);
		desligar_led_embutido();
		HAL_Delay(200);

		ligar_led_embutido();
		HAL_Delay(2000);
		desligar_led_embutido();
		HAL_Delay(2000);
	}
}


void MPU6050_read()
{
	uint16_t Accel_X_RAW;
	uint16_t Accel_Y_RAW;
	uint16_t Accel_Z_RAW;

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, MPU6050_acc_raw_data, 6, 1000);

	Accel_X_RAW = (int16_t)(MPU6050_acc_raw_data[0] << 8 | MPU6050_acc_raw_data [1]);
	Accel_Y_RAW = (int16_t)(MPU6050_acc_raw_data[2] << 8 | MPU6050_acc_raw_data [3]);
	Accel_Z_RAW = (int16_t)(MPU6050_acc_raw_data[4] << 8 | MPU6050_acc_raw_data [5]);

	MPU6050_data[0] = Accel_X_RAW/SENSIBILITY_ACC;
	MPU6050_data[1] = Accel_Y_RAW/SENSIBILITY_ACC;
	MPU6050_data[2] = Accel_Z_RAW/SENSIBILITY_ACC;

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, MPU6050_gyro_raw_data, 6, 1000);

	uint16_t Gyro_X_RAW;
	uint16_t Gyro_Y_RAW;
	uint16_t Gyro_Z_RAW;


	Gyro_X_RAW = (int16_t)(MPU6050_gyro_raw_data[0] << 8 | MPU6050_gyro_raw_data [1]);
	Gyro_Y_RAW = (int16_t)(MPU6050_gyro_raw_data[2] << 8 | MPU6050_gyro_raw_data [3]);
	Gyro_Z_RAW = (int16_t)(MPU6050_gyro_raw_data[4] << 8 | MPU6050_gyro_raw_data [5]);

	MPU6050_data[3] = Gyro_X_RAW/SENSIBILITY_GYRO;
	MPU6050_data[4] = Gyro_Y_RAW/SENSIBILITY_GYRO;
	MPU6050_data[5] = Gyro_Z_RAW/SENSIBILITY_GYRO;
}
