#ifndef SECOND_ORDER_COUNTERPOINT_H
#define SECOND_ORDER_COUNTERPOINT_H

#include "counterpoint.h"

class SecondOrderCounterpoint : public Counterpoint {
public:
  static bool dp[201][32][90][5][101];
  static vector<Note> dfs_generate_counterpoint(vector<Note> & song, bool ascendant, int paralels, int same_movements, Scale & scale);
  static bool solve(unsigned position, unsigned compass_position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale);
  static bool is_thesis(unsigned compass_position);
};

#endif
