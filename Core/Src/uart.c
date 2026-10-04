#include "uart.h"
#include <stdio.h>

UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}

HAL_StatusTypeDef UART_PrintAngles(float pitch, float roll)
{
  char message[64];
  int32_t pitch_cdeg = (int32_t)(pitch * 100.0f);
  int32_t roll_cdeg = (int32_t)(roll * 100.0f);
  long pitch_abs = (pitch_cdeg < 0) ? -(long)pitch_cdeg : (long)pitch_cdeg;
  long roll_abs = (roll_cdeg < 0) ? -(long)roll_cdeg : (long)roll_cdeg;
  int length = snprintf(message, sizeof(message),
                        "Pitch: %s%ld.%02ld, Roll: %s%ld.%02ld\r\n",
                        (pitch_cdeg < 0) ? "-" : "", pitch_abs / 100,
                        pitch_abs % 100, (roll_cdeg < 0) ? "-" : "",
                        roll_abs / 100, roll_abs % 100);

  if (length <= 0 || (size_t)length >= sizeof(message))
  {
    return HAL_ERROR;
  }

  return HAL_UART_Transmit(&huart1, (uint8_t *)message, (uint16_t)length, 100);
}
