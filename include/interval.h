#ifndef INTERVAL_H
#define INTERVAL_H

#include <string>
#include <cmath>
#include <cctype>

#include "note.h"

using std::string;
using std::to_string;
using std::min;

class Interval{
public:
  static int expected_semi_tones[10];
  static string diminished_classifications[10];
  static string augmented_classifications[10];
  static string intervals[9][17];

  int quantitative;
  string qualitative;
  int half_tones;
  bool ascendant;

  Interval(Note * first, Note * second);
  Interval(string s_interval, bool ascendant);
  string description();
  string full_description();

  static Note * interval_to_note(Note * note, Interval * interval);
private:
  bool is_perfect_candidate(int diff);
  void classificate_qualitative();
};

#endif