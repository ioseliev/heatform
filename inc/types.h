#ifndef TYPES_H
#define TYPES_H


typedef char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef uint8_t bool;
static const bool false = 0;
static const bool true = 1;

typedef long ssize_t;
typedef unsigned long size_t;

typedef volatile uint32_t *reg_t;

#endif
