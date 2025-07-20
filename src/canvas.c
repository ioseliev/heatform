#include <canvas.h>
#include <utilities.h>


void init_canvas(canvas_info *info, uint8_t *buffer) {
  info->current_line = 2;
  info->buffer = buffer;

  memcpy(buffer, ACS_CLEAR, sizeof(ACS_CLEAR) - 1);
  
  buffer += CANVAS_BUFFER_START_OFFSET;
  memset(buffer, ' ', CANVAS_BUFFER_SIZE);
  memcpy(buffer, "HEATFORM", sizeof("HEATFORM") - 1);
  buffer[CANVAS_COLS - 1] = '\n';
  buffer[CANVAS_BUFFER_SIZE - 1] = '\0';
}

static inline void write_header(uint8_t *buffer) {
  const int8_t FORMAT[] = "Current:       Min:       Max:      " ACS_RESET;
  memcpy(buffer, FORMAT, sizeof(FORMAT) - 1);
  buffer[CANVAS_COLS - 1] = '\n';
}

static inline void write_line(uint8_t *place, state *s) {
  const uint8_t FORMAT[] = "     [      ] Current:        Min:        Max:       "ACS_RESET;
  
  const size_t FMT_ACS_OFF = 0;
  const size_t FMT_TIME_OFF = 6;
  const size_t FMT_CURRENT_OFF = 23;
  const size_t FMT_MIN_OFF = 35;
  const size_t FMT_MAX_OFF = 47;
  
  memcpy(place, FORMAT, sizeof(FORMAT) - 1);

  memcpy(place + FMT_ACS_OFF, s->target_reached ? ACS_YELLOW : ACS_RESET, 5);

  write_time(place + FMT_TIME_OFF, s->hours, s->minutes, s->seconds);

  reading_to_string(place + FMT_CURRENT_OFF, s->temp);
  reading_to_string(place + FMT_MIN_OFF, s->temp_min);
  reading_to_string(place + FMT_MAX_OFF, s->temp_max);

  place[CANVAS_COLS - 1] = '\n';
}

void push_line(canvas_info *info, state *state) {
  uint8_t *const buffer = info->buffer + CANVAS_BUFFER_START_OFFSET;
  if (info->current_line == CANVAS_ROWS) {
    memcpy(buffer + 2 * CANVAS_COLS, buffer + 3 * CANVAS_COLS, 19 * CANVAS_COLS);
    --info->current_line;
  }
  write_header(buffer + 1 * CANVAS_COLS);
  write_line(buffer + info->current_line * CANVAS_COLS, state);
  ++info->current_line;
}
