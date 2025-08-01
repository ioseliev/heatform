#include <utilities.h>
#include <types.h>


void memset(uint8_t *dest, uint8_t value, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    dest[i] = value;
  }
}

void memcpy(uint8_t *dest, const uint8_t *restrict src, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    dest[i] = src[i];
  }
}

void write_float(uint8_t buffer[5], float value) {
  const float SENSOR_MIN = -40.0;
  const float SENSOR_MAX = 125.0;
  
  if (SENSOR_MIN <= value && value <= SENSOR_MAX) {
    size_t pos = 5;
    uint8_t is_negative = 0;

    if (value < 0) {
      is_negative = 1;
      value = -value;
    }

    uint8_t integer = (uint8_t) value;
    uint8_t decimal = (uint8_t) ((value - integer) * 10);

    buffer[--pos] = '0' + decimal;
    buffer[--pos] = '.';
    if (integer == 0) {
      buffer[--pos] = '0';
    } else {
      while (integer != 0) {
        buffer[--pos] = '0' + (integer % 10);
        integer /= 10;
      }
      if (is_negative == 1) {
        buffer[--pos] = '-';
      }
    }

    while (pos > 0) {
      buffer[--pos] = ' ';
    }
  } else {
    const char *ERROR_STRING = "ERROR";
    for (size_t i = 0; i < 5; ++i) {
      buffer[i] = ERROR_STRING[i];
    }
  }
}

void write_bcd(uint8_t buffer[2], uint8_t value) {
  buffer[0] = '0' + (value >> 4);
  buffer[1] = '0' + (value & 0x0F);
}
