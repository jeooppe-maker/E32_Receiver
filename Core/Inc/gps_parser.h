#ifndef GPS_PARSER_H
#define GPS_PARSER_H

#include <stdint.h>

typedef struct {
    float lat;
    float lon;
    float alt;
    float speed;
} GPSPacket_t;

// Повертає 1 — успіх, 0 — помилка
uint8_t GPS_Parse(const char *msg, GPSPacket_t *out);

#endif
