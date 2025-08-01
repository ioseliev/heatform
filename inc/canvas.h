#ifndef CANVAS_H
#define CANVAS_H
#include <types.h>
#include <state.h>


#define CANVAS_LINE_LENGTH 64

void canvas_init(uint8_t *buffer);

void canvas_update(uint8_t *buffer, const state *state, bool skip);

#endif
