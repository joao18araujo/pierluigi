#ifndef FIRST_ORDER_COUNTERPOINT_H
#define FIRST_ORDER_COUNTERPOINT_H

#include "counterpoint.h"

class FirstSpeciesCounterpoint : public Counterpoint {
public:
  static bool dp[201][90][5][101];
  static Song dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, int paralels, int same_movements, Song & song, vector<Note> & counterpoint, bool ascendant);
};

#endif
