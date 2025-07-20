#ifndef CANVAS_H
#define CANVAS_H
#include <types.h>
#include <state.h>
#include <ansi.h>


#define CANVAS_ROWS 22
#define CANVAS_COLS 64
#define CANVAS_BUFFER_SIZE ((CANVAS_ROWS) * (CANVAS_COLS))
#define CANVAS_BUFFER_START_OFFSET ((sizeof(ACS_CLEAR)) - 1)

typedef struct {
  uint8_t current_line;
  uint8_t *buffer;
} canvas_info;

void init_canvas(canvas_info *info, uint8_t *buffer);

void update_canvas(canvas_info *info, state *state, bool push_line);

#endif
