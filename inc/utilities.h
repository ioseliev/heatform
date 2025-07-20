#ifndef UTILITIES_H
#define UTILITIES_H
#include <types.h>


void memset(uint8_t *dest, uint8_t value, size_t n);

void memcpy(uint8_t *dest, const uint8_t *restrict src, size_t n);

void write_float(uint8_t buffer[5], float value);

void write_time(uint8_t buffer[6], uint8_t hours, uint8_t minutes, uint8_t seconds);

#endif
