#include "mpu6050.h"
#include "i2c.h"
#include <math.h>

#define MPU6050_ADDR       (0x68U << 1)
#define MPU6050_REG_ACCEL  0x3BU
#define MPU6050_REG_PWR1   0x6BU

HAL_StatusTypeDef MPU6050_Init(void)
{
  uint8_t wake = 0;
  HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c1, MPU6050_ADDR, 3, 100);
  if (status != HAL_OK)
  {
    return status;
  }

  status = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, MPU6050_REG_PWR1,
                             I2C_MEMADD_SIZE_8BIT, &wake, 1, 100);
  if (status == HAL_OK)
  {
    HAL_Delay(100);
  }
  return status;
}

HAL_StatusTypeDef MPU6050_ReadAngles(float *pitch, float *roll)
{
  uint8_t data[6];
  int16_t ax_raw, ay_raw, az_raw;
  float ax, ay, az;
  HAL_StatusTypeDef status;

  if (pitch == NULL || roll == NULL)
  {
    return HAL_ERROR;
  }

  status = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, MPU6050_REG_ACCEL,
                            I2C_MEMADD_SIZE_8BIT, data, sizeof(data), 100);
  if (status != HAL_OK)
  {
    return status;
  }

  ax_raw = (int16_t)((uint16_t)data[0] << 8 | data[1]);
  ay_raw = (int16_t)((uint16_t)data[2] << 8 | data[3]);
  az_raw = (int16_t)((uint16_t)data[4] << 8 | data[5]);

  /* Default accelerometer range is +/-2 g; scale cancels in angle ratios. */
  ax = (float)ax_raw;
  ay = (float)ay_raw;
  az = (float)az_raw;

  *pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * (180.0f / 3.14159265f);
  *roll = atan2f(ay, az) * (180.0f / 3.14159265f);
  return HAL_OK;
}
