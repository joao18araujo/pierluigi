#ifndef COUNTERPOINT_H
#define COUNTERPOINT_H

#include "note.h"
#include "interval.h"
#include "scale.h"
#include <vector>
#include <cstring>
#include <algorithm>

using std::vector;
using std::random_shuffle;

class Counterpoint{
public:

  static vector<Note> generate_first_order_counterpoint(vector<Note> & song, bool ascendant = false);

  static bool dp[201][90][5][101];

  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval);

  static vector<Note> dfs_generate_first_order_counterpoint(vector<Note> & song, bool ascendant, int paralels = 4, int same_movements = 40);

  static bool solve(unsigned position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant);
};

#endif
