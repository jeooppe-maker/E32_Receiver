#ifndef E32_RX_H
#define E32_RX_H

#include "main.h"
#include <stdint.h>

// Максимальний розмір отриманого повідомлення
#define E32_RX_BUF_SIZE 128

// Ініціалізація прийому
void E32_RX_Init(UART_HandleTypeDef *uart);

// Перевірка — чи є готовий пакет
uint8_t E32_RX_MessageReady(void);

// Отримання повного повідомлення (копіює в buf)
// Повертає довжину
uint16_t E32_RX_GetMessage(char *buf, uint16_t max_len);

// Викликається з HAL_UART_RxCpltCallback
void E32_RX_UART_RxHandler(UART_HandleTypeDef *huart);

#endif
