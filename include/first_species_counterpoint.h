#ifndef FIRST_SPECIES_COUNTERPOINT_H
#define FIRST_SPECIES_COUNTERPOINT_H

#include "counterpoint.h"

class FirstSpeciesCounterpoint : public Counterpoint {
public:
  static Song dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, int paralels, int same_movements, Song & counterpoint, bool ascendant);
  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval, Song * counterpoint);
};

#endif
