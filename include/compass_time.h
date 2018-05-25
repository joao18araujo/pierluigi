#ifndef COMPASS_TIME_H
#define COMPASS_TIME_H

#include "constants.h"

class CompassTime{
public:
  int times;
  int base_note;

  CompassTime() : times(4), base_note(4) {}
  CompassTime(int t_times, int t_base_note) : times(t_times), base_note(t_base_note) {}

  int base_note_duration() {
    printf("Base note %d\n", base_note);
    return QUANT / base_note;
  }
  int compass_duration() { return base_note_duration() * times; }
};

#endif
