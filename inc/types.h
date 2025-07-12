#ifndef TYPES_H
#define TYPES_H


typedef char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef enum { false = 0, true = 1 } bool;

typedef long ssize_t;
typedef unsigned long size_t;

typedef volatile uint32_t *reg_t;

#endif
