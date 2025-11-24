#include "e32.h"
#include <string.h>
#include <stdio.h>

static UART_HandleTypeDef *E32_UART = NULL;

static void E32_WaitAUX(void)
{
    uint32_t start = HAL_GetTick();
    while (HAL_GPIO_ReadPin(E32_AUX_PORT, E32_AUX_PIN) == GPIO_PIN_RESET)
    {
        if (HAL_GetTick() - start > 3000)
            return;
    }
    HAL_Delay(5);
}

void E32_Init(UART_HandleTypeDef *uart)
{
    E32_UART = uart;
}

void E32_SetMode(E32_Mode mode)
{
    switch(mode) {
        case E32_MODE_NORMAL:
            HAL_GPIO_WritePin(E32_M0_PORT, E32_M0_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E32_M1_PORT, E32_M1_PIN, GPIO_PIN_RESET);
            break;

        case E32_MODE_WAKEUP:
            HAL_GPIO_WritePin(E32_M0_PORT, E32_M0_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E32_M1_PORT, E32_M1_PIN, GPIO_PIN_RESET);
            break;

        case E32_MODE_POWERDOWN:
            HAL_GPIO_WritePin(E32_M0_PORT, E32_M0_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(E32_M1_PORT, E32_M1_PIN, GPIO_PIN_SET);
            break;

        case E32_MODE_PROGRAM:
            HAL_GPIO_WritePin(E32_M0_PORT, E32_M0_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(E32_M1_PORT, E32_M1_PIN, GPIO_PIN_SET);
            break;
    }

    HAL_Delay(40);
    E32_WaitAUX();
}

void E32_SendString(char *str)
{
    if (!E32_UART) return;
    E32_WaitAUX();
    HAL_UART_Transmit(E32_UART, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void E32_SendByte(uint8_t data)
{
    if (!E32_UART) return;
    E32_WaitAUX();
    HAL_UART_Transmit(E32_UART, &data, 1, HAL_MAX_DELAY);
}

uint8_t E32_IsBusy(void)
{
    return (HAL_GPIO_ReadPin(E32_AUX_PORT, E32_AUX_PIN) == GPIO_PIN_RESET);
}

void Check_AUX(void)
{
    if (HAL_GPIO_ReadPin(E32_AUX_PORT, E32_AUX_PIN))
        printf("AUX HIGH\n");
    else
        printf("AUX LOW\n");
}

// --------------------- CONFIG READ -----------------------

int E32_GetConfiguration(uint8_t *out_buf, uint32_t timeout_ms)
{
    if (!E32_UART || !out_buf) return -1;

    uint8_t cmd[3] = {0xC1,0xC1,0xC1};
    uint8_t tmp[6];

    E32_SetMode(E32_MODE_PROGRAM);

    __HAL_UART_FLUSH_DRREGISTER(E32_UART);

    HAL_UART_Transmit(E32_UART, cmd, 3, 50);

    E32_WaitAUX();

    if (HAL_UART_Receive(E32_UART, tmp, 6, timeout_ms) != HAL_OK)
        return -2;

    memcpy(out_buf, tmp, 6);

    E32_SetMode(E32_MODE_NORMAL);
    return 0;
}

// --------------------- AUTO BAUD DETECT -----------------------

static const uint32_t baud_list[] = {9600,115200,57600,38400,19200,4800,2400,1200};

int E32_AutoDetectSpeed(uint32_t *speed_out, uint8_t *cfg_out)
{
    if (!E32_UART) return -10;

    uint8_t buf[6];

    // MODE 3
    E32_SetMode(E32_MODE_PROGRAM);

    for (int i = 0; i < sizeof(baud_list)/sizeof(baud_list[0]); i++)
    {
        uint32_t br = baud_list[i];

        E32_UART->Init.BaudRate = br;
        HAL_UART_Init(E32_UART);

        uint8_t cmd[3] = {0xC1,0xC1,0xC1};
        HAL_UART_Transmit(E32_UART, cmd, 3, 20);

        if (HAL_UART_Receive(E32_UART, buf, 6, 40) == HAL_OK)
        {
            // примітивна валідація пакету
            if ((buf[0] == 0xC0 || buf[0] == 0xC1) && buf[4] < 32)
            {
                if (speed_out) *speed_out = br;
                if (cfg_out) memcpy(cfg_out, buf, 6);

                E32_SetMode(E32_MODE_NORMAL);
                return 0;
            }
        }
    }

    E32_SetMode(E32_MODE_NORMAL);
    return -1; // не вдалося знайти швидкість
}
