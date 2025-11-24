#ifndef E32_CONFIG_H
#define E32_CONFIG_H

// --- UART PARAMS (8 біт) ---
typedef enum {
    UART_8N1   = (0x00 << 6),
    UART_8O1   = (0x01 << 6),
    UART_8E1   = (0x02 << 6)
} E32_UARTMode_t;

typedef enum {
    BAUD_1200   = (0x00 << 3),
    BAUD_2400   = (0x01 << 3),
    BAUD_4800   = (0x02 << 3),
    BAUD_9600   = (0x03 << 3),
    BAUD_19200  = (0x04 << 3),
    BAUD_38400  = (0x05 << 3),
    BAUD_57600  = (0x06 << 3),
    BAUD_115200 = (0x07 << 3)
} E32_BaudRate_t;

// --- AIR DATA RATE ---
typedef enum {
    AIR_300  = (0x00 << 0),
    AIR_1200 = (0x01 << 0),
    AIR_2400 = (0x02 << 0),
    AIR_4800 = (0x03 << 0),
    AIR_9600 = (0x04 << 0),
    AIR_19200 = (0x05 << 0)
} E32_AirRate_t;

// --- OPTION BYTE ---
typedef enum {
    TRANS_MODE   = (0x00 << 7),
    FIXED_MODE   = (0x01 << 7),

    PUSH_PULL    = (0x01 << 6),
    OPEN_COLLECTOR = (0x00 << 6),

    WAKEUP_250   = (0x00 << 3),
    WAKEUP_500   = (0x01 << 3),
    WAKEUP_750   = (0x02 << 3),
    WAKEUP_1000  = (0x03 << 3),
    WAKEUP_1250  = (0x04 << 3),
    WAKEUP_1500  = (0x05 << 3),
    WAKEUP_1750  = (0x06 << 3),
    WAKEUP_2000  = (0x07 << 3),

    FEC_OFF      = (0x00 << 2),
    FEC_ON       = (0x01 << 2),

    PWR_30DBM    = (0x00 << 0),
    PWR_27DBM    = (0x01 << 0),
    PWR_24DBM    = (0x02 << 0),
    PWR_21DBM    = (0x03 << 0)
} E32_Option_t;

#endif
