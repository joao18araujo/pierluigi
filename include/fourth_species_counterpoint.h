#ifndef FOURTH_SPECIES_COUNTERPOINT_H
#define FOURTH_SPECIES_COUNTERPOINT_H

#include "counterpoint.h"

class FourthSpeciesCounterpoint : public Counterpoint {
public:
  static Song dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, unsigned compass_position, int paralels, int same_movements, bool ascendant, Song & counterpoint);
  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_note, Note note, Interval interval, Song * counterpoint);
};

#endif
