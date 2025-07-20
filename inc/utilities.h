#ifndef UTILITIES_H
#define UTILITIES_H
#include <types.h>


void memset(uint8_t *dest, uint8_t value, size_t n);

void memcpy(uint8_t *dest, const uint8_t *restrict src, size_t n);

void reading_to_string(char *buffer, float value);

void write_time(char buffer[6], uint8_t hours, uint8_t minutes, uint8_t seconds);

#endif
