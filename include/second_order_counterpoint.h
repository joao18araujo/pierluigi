#ifndef SECOND_ORDER_COUNTERPOINT_H
#define SECOND_ORDER_COUNTERPOINT_H

#include "counterpoint.h"

class SecondOrderCounterpoint : public Counterpoint {
public:
  static bool dp[201][32][90][5][101];
  static vector<Note> counterpoint;
  static Song * song;

  static vector<Note> dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, unsigned compass_position, int paralels, int same_movements, bool ascendant);
  static bool is_thesis(Note & note, int offset);
  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_note, Note note, Interval interval);

};

#endif
