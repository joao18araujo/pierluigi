#ifndef INTERVAL_H
#define INTERVAL_H

#include <string>
#include <cmath>

#include "note.h"

using std::string;

class Interval{
public:
  static int expected_semi_tones[10];

  int quantitative;
  string qualitative;
  int half_tones;
  bool ascendant;
  Interval(Note * first, Note * second);

private:
  bool is_perfect_candidate(int diff);
};

#endif
