#ifndef STATE_H
#define STATE_H
#include <types.h>


typedef struct {
  /* Configuration */
  float target;
  enum { NONE, LOW, HIGH } target_type;

  /* Status */
  bool target_reached;
  
  /* Sensor data */
  float temp;
  float temp_min;
  float temp_max;

  /* RTC data */
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} state;

#endif
