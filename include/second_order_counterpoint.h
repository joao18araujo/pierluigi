#ifndef SECOND_ORDER_COUNTERPOINT_H
#define SECOND_ORDER_COUNTERPOINT_H

#include "counterpoint.h"

class SecondOrderCounterpoint : public Counterpoint {
public:
  static bool dp[201][32][90][5][101];
  static vector<Note> dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements);
  static bool solve(unsigned position, unsigned compass_position, int paralels, int same_movements, Song & song, vector<Note> & counterpoint, bool ascendant);
  static bool is_thesis(Note & note, Song & song);
};

#endif
