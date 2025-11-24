// bt.h
#ifndef BT_H
#define BT_H

#include <stdint.h>
#include <string.h>
#include "main.h"

void BT_Init(UART_HandleTypeDef *uart);
void BT_Send(const char *msg);
float rand_float(float min, float max);

#endif
