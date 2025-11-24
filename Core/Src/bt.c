// bt.c
#include "bt.h"
#include <stdlib.h>

static UART_HandleTypeDef *BT_UART = NULL;

void BT_Init(UART_HandleTypeDef *uart){
	BT_UART = uart;
}

void BT_Send(const char *msg)
{
    HAL_UART_Transmit(BT_UART, (uint8_t*)msg, strlen(msg), 100);
}

float rand_float(float min, float max)
{
    return min + (float)rand() / (float)RAND_MAX * (max - min);
}
