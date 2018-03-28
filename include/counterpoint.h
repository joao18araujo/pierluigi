#ifndef COUNTERPOINT_H
#define COUNTERPOINT_H

#include "note.h"
#include "interval.h"
#include <vector>

using std::vector;

class Counterpoint{
public:

  static vector<Note> generate_first_order_counterpoint(vector<Note> & song, bool ascendant = false);

  static void analyse_and_add_interval(bool reverse_movement, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval);
};

#endif
