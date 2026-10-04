#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "main.h"

HAL_StatusTypeDef MPU6050_Init(void);
HAL_StatusTypeDef MPU6050_ReadAngles(float *pitch, float *roll);

#endif
