#ifndef E32_H
#define E32_H

#include "main.h"
#include <stdint.h>

// --- Піни модуля E32 ---
#define E32_M0_PIN   GPIO_PIN_12
#define E32_M0_PORT  GPIOB
#define E32_M1_PIN   GPIO_PIN_13
#define E32_M1_PORT  GPIOB
#define E32_AUX_PIN  GPIO_PIN_14
#define E32_AUX_PORT GPIOB

// --- Режими роботи ---
typedef enum {
    E32_MODE_NORMAL = 0,
    E32_MODE_WAKEUP,
    E32_MODE_POWERDOWN,
    E32_MODE_PROGRAM
} E32_Mode;

// --- Публічні функції ---
void E32_Init(UART_HandleTypeDef *uart);
void E32_SetMode(E32_Mode mode);
void E32_SendString(char *str);
void E32_SendByte(uint8_t data);
uint8_t E32_IsBusy(void);
void Check_AUX(void);

int E32_GetConfiguration(uint8_t *out_buf, uint32_t timeout_ms);
int E32_AutoDetectSpeed(uint32_t *speed_out, uint8_t *cfg_out);

#endif
