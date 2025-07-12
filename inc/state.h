#ifndef STATE_H
#define STATE_H
#include <types.h>


typedef struct {
  float current;
  float min;
  float max;
  float target;
  enum { LOW = 0, HIGH = 1 } target_type;
  uint16_t time;
} state;

#endif
