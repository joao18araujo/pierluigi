#include "counterpoint.h"

#include <cstdlib>
#include <ctime>

vector<Note *> Counterpoint::generate_first_order_counterpoint(vector<Note *> & song, bool ascendant){
  vector <Note *> counterpoint;
  vector<Interval> consonant_intervals {Interval("P1", ascendant), Interval("P8", ascendant), Interval("P5", ascendant), Interval("m3", ascendant), Interval("M3", ascendant), Interval("m6", ascendant), Interval("M6", ascendant), Interval("m10", ascendant), Interval("M10", ascendant)};
  vector<Interval> perfect_consonant_intervals {Interval("P1", ascendant), Interval("P8", ascendant), Interval("P5", ascendant)};
  vector<Interval> imperfect_consonant_intervals { Interval("m3", ascendant), Interval("M3", ascendant), Interval("m6", ascendant), Interval("M6", ascendant), Interval("m10", ascendant), Interval("M10", ascendant)};

  vector<Interval> possible_intervals;

  srand(clock());

  int count_imperfects = 0;

  Interval current_interval, previous_interval, interval;
  Interval melodic_cantus_interval, melodic_counterpoint_interval;
  Note * previous_note;
  Note * counterpoint_note;
  Note * previous_counterpoint_note;

  for(unsigned i = 0; i < song.size(); ++i){
    possible_intervals.clear();
    auto note = song[i];

    melodic_cantus_interval = Interval(note, previous_note);
    bool reverse_movement = (rand() % 100 < 80); // 80% de chances de ser movimento contrário
    bool melodic_ascendant = (reverse_movement ^ melodic_cantus_interval.ascendant);

    if(reverse_movement){

    }else{

    }

    string previous = previous_interval.description();
    if(i == 0 || i == song.size() - 1){
      interval = Interval("P1", ascendant);
      counterpoint_note = Interval::interval_to_note(note, interval);
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant));
    }else if(count_imperfects < 4){
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant));
    }

    if(previous != "P5" && previous != "P8"){
      analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant));
      if(ascendant)
        analyse_and_add_interval(reverse_movement, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant));
    }
    if(possible_intervals.empty()) return vector<Note *>();
    int index = rand() % possible_intervals.size(); // TODO: checar se não é 0

    current_interval = possible_intervals[index];
    counterpoint_note = Interval::interval_to_note(note, current_interval);
    counterpoint.push_back(counterpoint_note);

    char interval_qualitative = current_interval.description()[0];
    if(interval_qualitative == 'M' || interval_qualitative == 'm')
      count_imperfects++;
    else
      count_imperfects = 0;

    previous_interval = current_interval;
    previous_note = note;
    previous_counterpoint_note = counterpoint_note;
  }

  return counterpoint;
}

void Counterpoint::analyse_and_add_interval(bool reverse_movement, vector<Interval> & possible_intervals, Note * previous_counterpoint_note, Note * note, Interval interval){
  if(true)
    possible_intervals.push_back(interval);
}
