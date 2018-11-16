#ifndef FIRST_SPECIES_COUNTERPOINT_H
#define FIRST_SPECIES_COUNTERPOINT_H

#include "counterpoint.h"

class FirstSpeciesCounterpoint : public Counterpoint {
public:
  static Song dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, int paralels, int same_movements, Song & counterpoint, bool ascendant);
};

#endif
