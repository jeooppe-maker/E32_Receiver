#include "e32_rx.h"
#include <string.h>

static UART_HandleTypeDef *E32_UART_RX = NULL;

static volatile uint8_t rx_byte;
static volatile uint8_t rx_buf[E32_RX_BUF_SIZE];
static volatile uint16_t rx_len = 0;

static volatile uint8_t msg_ready = 0;

void E32_RX_Init(UART_HandleTypeDef *uart)
{
    E32_UART_RX = uart;
    rx_len = 0;
    msg_ready = 0;

    // Почати прийом у перериванні
//    HAL_UART_Receive_IT(E32_UART_RX, &rx_byte, 1);
    HAL_StatusTypeDef st = HAL_UART_Receive_IT(E32_UART_RX, &rx_byte, 1);
    if (st != HAL_OK) {
        // debug: наприклад, включити світлодіод або printf
    }
}

uint8_t E32_RX_MessageReady(void)
{
    return msg_ready;
}

uint16_t E32_RX_GetMessage(char *buf, uint16_t max_len)
{
    if (!msg_ready) return 0;

    uint16_t n = rx_len;
    if (n > max_len) n = max_len;

    memcpy(buf, rx_buf, n);
    buf[n] = '\0';

    rx_len = 0;
    msg_ready = 0;

    return n;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    E32_RX_UART_RxHandler(huart);
}


void E32_RX_UART_RxHandler(UART_HandleTypeDef *huart)
{
    if (huart == E32_UART_RX)
    {
        if (rx_byte == '\n')
        {
            msg_ready = 1;
        }
        else
        {
            if (rx_len < E32_RX_BUF_SIZE - 1)
            {
                rx_buf[rx_len++] = rx_byte;
            }
        }

        // Знову запустити прийом
        HAL_UART_Receive_IT(E32_UART_RX, &rx_byte, 1);
    }
}
