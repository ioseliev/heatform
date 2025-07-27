#include <canvas.h>
#include <utilities.h>


void canvas_init(canvas_info *info, uint8_t *buffer) {
  info->current_line = 2;
  info->buffer = buffer;

  memcpy(buffer, (const uint8_t *) ACS_CLEAR, sizeof(ACS_CLEAR) - 1);
  
  buffer += CANVAS_BUFFER_START_OFFSET;
  memset(buffer, ' ', CANVAS_BUFFER_SIZE);
  memcpy(buffer, (const uint8_t *) "HEATFORM", sizeof("HEATFORM") - 1);

  for (uint8_t i = 0; i < CANVAS_ROWS; ++i) {
    buffer[i * CANVAS_COLS + CANVAS_COLS - 1] = '\n';
  }

}

static inline void write_header(uint8_t *buffer, state *s) {
  const uint8_t FORMAT[] = "     NOW Current:        Min:        Max:       " ACS_RESET;

  const size_t FMT_CUR_OFF = 18;
  const size_t FMT_MIN_OFF = 30;
  const size_t FMT_MAX_OFF = 42;
  
  memcpy(buffer, FORMAT, sizeof(FORMAT) - 1);

  write_float(buffer + FMT_CUR_OFF, s->temp);
  write_float(buffer + FMT_MIN_OFF, s->temp_min);
  write_float(buffer + FMT_MAX_OFF, s->temp_max);

  buffer[CANVAS_COLS - 1] = '\n';
}

static inline void write_line(uint8_t *place, state *s) {
  const uint8_t FORMAT[] = "     [      ] Current:        Min:        Max:       " ACS_RESET;
  
  const size_t FMT_ACS_OFF = 0;
  const size_t FMT_TIME_OFF = 6;
  const size_t FMT_CURRENT_OFF = 23;
  const size_t FMT_MIN_OFF = 35;
  const size_t FMT_MAX_OFF = 47;
  
  memcpy(place, FORMAT, sizeof(FORMAT) - 1);

  memcpy(place + FMT_ACS_OFF, (const uint8_t *) (s->target_reached ? ACS_YELLOW : ACS_RESET), 5);

  write_time(place + FMT_TIME_OFF, s->hours, s->minutes, s->seconds);

  write_float(place + FMT_CURRENT_OFF, s->temp);
  write_float(place + FMT_MIN_OFF, s->temp_min);
  write_float(place + FMT_MAX_OFF, s->temp_max);

  place[CANVAS_COLS - 1] = '\n';
}

void canvas_update(canvas_info *info, state *state, bool push_line) {
  uint8_t *const buffer = info->buffer + CANVAS_BUFFER_START_OFFSET;
  
  write_header(buffer + CANVAS_COLS, state);
  if (push_line) {
    if (info->current_line == CANVAS_ROWS) {
      memcpy(buffer + 2 * CANVAS_COLS, buffer + 3 * CANVAS_COLS, (CANVAS_ROWS - 3) * CANVAS_COLS);
      --info->current_line;
    }
    write_line(buffer + info->current_line * CANVAS_COLS, state);
    ++info->current_line;
  }
}
