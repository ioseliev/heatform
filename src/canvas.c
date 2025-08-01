#include <canvas.h>
#include <utilities.h>


void canvas_init(uint8_t *buffer) {
  const uint8_t FORMAT[] = "[00:00:00] Obj:        Amb:        Min:        Max:       ";

  memset(buffer, ' ', CANVAS_LINE_LENGTH);
  memcpy(buffer, FORMAT, sizeof(FORMAT) - 1);

  buffer[CANVAS_LINE_LENGTH - 1] = '\0';
}

void canvas_update(uint8_t *buffer, const state *state, bool skip) {
  const size_t FMT_HOURS = 1;
  const size_t FMT_MINUTES = 4;
  const size_t FMT_SECONDS = 7;
  const size_t FMT_OBJ = 16;
  const size_t FMT_AMB = 28;
  const size_t FMT_MIN = 40;
  const size_t FMT_MAX = 52;
  const size_t FMT_CRLF = 62;

  write_bcd(buffer + FMT_HOURS, state->hours);
  write_bcd(buffer + FMT_MINUTES, state->minutes);
  write_bcd(buffer + FMT_SECONDS, state->seconds);

  write_float(buffer + FMT_OBJ, state->temp);
  write_float(buffer + FMT_MIN, state->temp_min);
  write_float(buffer + FMT_MAX, state->temp_max);

  buffer[FMT_CRLF] = (skip == true ? '\n' : '\r');
}
