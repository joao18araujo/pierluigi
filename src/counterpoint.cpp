#include "counterpoint.h"

#include <cstdlib>
#include <ctime>

vector<Note *> Counterpoint::generate_first_order_counterpoint(vector<Note *> & song, bool ascendant){
  vector <Note *> counterpoint;
  vector<Interval> consonant_intervals {Interval("P1"), Interval("P8"), Interval("P5"), Interval("m3"), Interval("M3"), Interval("m6"), Interval("M6"), Interval("m10"), Interval("M10")};
  vector<Interval> perfect_consonant_intervals {Interval("P1"), Interval("P8"), Interval("P5")};
  vector<Interval> imperfect_consonant_intervals { Interval("m3"), Interval("M3"), Interval("m6"), Interval("M6"), Interval("m10"), Interval("M10")};

  vector<Interval> possible_intervals;

  srand(clock());

  int count_imperfects = 0;

  Interval current_interval, previous_interval;
  for(unsigned i = 0; i < song.size(); ++i){
    possible_intervals.clear();
    auto note = song[i];

    string previous = previous_interval.description();
    if(i == 0 || i == song.size()){
      possible_intervals.push_back(Interval("P1"));
    }else if(count_imperfects < 4){
      possible_intervals.insert(possible_intervals.begin(), imperfect_consonant_intervals.begin(),  imperfect_consonant_intervals.end());
    }

    if(previous != "P5" && previous != "P8"){
      possible_intervals.push_back(Interval("P8"));
      if(ascendant)
        possible_intervals.push_back(Interval("P5"));
    }
    int index = rand() % possible_intervals.size(); // TODO: checar se não é 0

    current_interval = possible_intervals[index];
    Note * counterpoint_note = Interval::interval_to_note(note, current_interval);
    counterpoint.push_back(counterpoint_note);

    char interval_qualitative = current_interval.description()[0];
    if(interval_qualitative == 'M' || interval_qualitative == 'm')
      count_imperfects++;
    else
      count_imperfects = 0;

    previous_interval = current_interval;
  }

  return vector<Note *>();
}
