#ifndef INTERVAL_H
#define INTERVAL_H

#include <string>
#include <cmath>

#include "note.h"

using std::string;
using std::to_string;
using std::min;

class Interval{
public:
  static int expected_semi_tones[10];
  static string diminished_classifications[10];
  static string augmented_classifications[10];

  int quantitative;
  string qualitative;
  int half_tones;
  bool ascendant;
  Interval(string s_interval);
  Interval(Note * first, Note * second);
  string description();

  static Note interval_to_note(Note * note, Interval * interval);
private:
  bool is_perfect_candidate(int diff);
};

#endif
