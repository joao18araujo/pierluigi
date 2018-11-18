#ifndef COUNTERPOINT_H
#define COUNTERPOINT_H

#include "note.h"
#include "interval.h"
#include "scale.h"
#include "song.h"
#include <vector>
#include <cstring>
#include <algorithm>

using std::vector;
using std::random_shuffle;

class Counterpoint{
public:
  static bool dp[151][4][90][5][601];
  static Song * song;

  static vector<Note> generate_first_species_counterpoint(Song & song, bool ascendant);

  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval, Song * counterpoint);

  static bool is_thesis(Note & note, int offset);
  static bool is_thesis(Note & note, int offset, Song * song);
  static void add_trailing_rests(Song & counterpoint);
};

#endif
