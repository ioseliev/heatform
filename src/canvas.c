#include <canvas.h>
#include <utilities.h>


void canvas_init(uint8_t *buffer) {
  const uint8_t FORMAT[] = " [00:00:00] Obj:        Amb:        Min:        Max:      ";

  memset(buffer, ' ', CANVAS_LINE_LENGTH);
  memcpy(buffer, FORMAT, sizeof(FORMAT) - 1);

  buffer[CANVAS_LINE_LENGTH] = '\0';
}

void canvas_update(uint8_t *buffer, const state *state, bool skip) {
  const size_t FMT_CRLF = 0;
  const size_t FMT_HOURS = 2;
  const size_t FMT_MINUTES = 5;
  const size_t FMT_SECONDS = 8;
  const size_t FMT_OBJ = 17;
  const size_t FMT_AMB = 29;
  const size_t FMT_MIN = 41;
  const size_t FMT_MAX = 53;

  buffer[FMT_CRLF] = (skip == true ? '\n' : '\r');

  write_bcd(buffer + FMT_HOURS, state->hours);
  write_bcd(buffer + FMT_MINUTES, state->minutes);
  write_bcd(buffer + FMT_SECONDS, state->seconds);

  write_float(buffer + FMT_OBJ, state->temp);
  write_float(buffer + FMT_MIN, state->temp_min);
  write_float(buffer + FMT_MAX, state->temp_max);
}
