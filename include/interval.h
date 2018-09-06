#ifndef INTERVAL_H
#define INTERVAL_H

#include <string>
#include <cmath>
#include <unordered_set>
#include <cctype>

#include "note.h"

using std::string;
using std::to_string;
using std::min;
using std::unordered_set;

class Interval{
public:
  static int expected_semi_tones[10];
  static string diminished_classifications[10];
  static string augmented_classifications[10];
  static string intervals[9][17];
  static unordered_set<int> dissonant_half_tones;

  int quantitative;
  string qualitative;
  int half_tones;
  bool ascendant;

  Interval(Note first, Note second);
  Interval(){}; // TODO: implement empty constructor
  Interval(string s_interval, bool ascendant = true);
  string description() const;
  string full_description() const;

  bool is_dissonant();
  bool is_consonant();

  static Note interval_to_note(Note note, Interval interval);
  bool operator==(const string & s) const;

private:
  bool is_perfect_candidate(int diff);
  void classify_qualitative();
};

#endif
