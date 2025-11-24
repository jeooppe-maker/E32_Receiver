#include "gps_parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Шукає значення після prefix, наприклад:
// find_value("Lat:", msg) поверне pointer на число після Lat:
static const char* find_value(const char *prefix, const char *msg)
{
    const char *p = strstr(msg, prefix);
    if (!p) return NULL;
    return p + strlen(prefix);
}

uint8_t GPS_Parse(const char *msg, GPSPacket_t *out)
{
    if (!msg || !out) return 0;

    // LAT
    const char *p = find_value("Lat:", msg);
    if (!p) return 0;
    out->lat = atof(p);

    // LON
    p = find_value("Lon:", msg);
    if (!p) return 0;
    out->lon = atof(p);

    // ALT
    p = find_value("Alt:", msg);
    if (!p) return 0;
    out->alt = atof(p);

    // SPEED
    p = find_value("Speed:", msg);
    if (!p) return 0;
    out->speed = atof(p);

    return 1;
}
