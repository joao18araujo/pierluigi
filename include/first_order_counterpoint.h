#ifndef FIRST_ORDER_COUNTERPOINT_H
#define FIRST_ORDER_COUNTERPOINT_H

#include "counterpoint.h"

class FirstOrderCounterpoint : public Counterpoint {
public:
  static bool dp[201][90][5][101];
  static vector<Note> dfs_generate_counterpoint(vector<Note> & song, bool ascendant, int paralels, int same_movements, Scale & scale);
  static bool solve(unsigned position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale);
};

#endif
