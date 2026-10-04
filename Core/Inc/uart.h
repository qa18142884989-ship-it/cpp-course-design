#ifndef __UART_H__
#define __UART_H__

#include "main.h"

extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);
HAL_StatusTypeDef UART_PrintAngles(float pitch, float roll);

#endif
