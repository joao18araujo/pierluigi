#include "counterpoint.h"

#include <cstdlib>
#include <ctime>

vector<Note> Counterpoint::generate_first_order_counterpoint(vector<Note> & song, bool ascendant){
  vector <Note> counterpoint;
  vector<Interval> consonant_intervals {Interval("P1", ascendant), Interval("P8", ascendant), Interval("P5", ascendant), Interval("m3", ascendant), Interval("M3", ascendant), Interval("m6", ascendant), Interval("M6", ascendant), Interval("m10", ascendant), Interval("M10", ascendant)};
  vector<Interval> perfect_consonant_intervals {Interval("P1", ascendant), Interval("P8", ascendant), Interval("P5", ascendant)};
  vector<Interval> imperfect_consonant_intervals { Interval("m3", ascendant), Interval("M3", ascendant), Interval("m6", ascendant), Interval("M6", ascendant), Interval("m10", ascendant), Interval("M10", ascendant)};

  vector<Interval> possible_intervals;

  srand(clock());

  int count_imperfects = 0;

  Interval current_interval, previous_interval, interval;
  Interval melodic_cantus_interval, melodic_counterpoint_interval;
  Note previous_note;
  Note counterpoint_note;
  Note previous_counterpoint_note;

  int times_not_reversed = 0;
  for(unsigned i = 0; i < song.size(); ++i){
    possible_intervals.clear();
    auto note = song[i];

    melodic_cantus_interval = Interval(note, previous_note);
    bool reverse_movement = true;

    begin:
    bool melodic_ascendant = (reverse_movement ^ melodic_cantus_interval.ascendant);

    string previous = previous_interval.description();
    if(i == 0 || i == song.size() - 1){
      interval = Interval("P1", ascendant);
      counterpoint_note = Interval::interval_to_note(note, interval);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant));
    }else if(count_imperfects < 4){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant));
    }

    if(previous != "P5" && previous != "P8"){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant));
      if(ascendant)
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant));
    }

    if(possible_intervals.empty() && reverse_movement && times_not_reversed++ < 3){
      reverse_movement = false;
      goto begin;
    }

    if(possible_intervals.empty()) return vector<Note>();
    int index = rand() % possible_intervals.size();

    current_interval = possible_intervals[index];
    counterpoint_note = Interval::interval_to_note(note, current_interval);
    counterpoint.push_back(counterpoint_note);

    string interval_qualitative = current_interval.qualitative;
    if(interval_qualitative == "M" || interval_qualitative == "m")
      count_imperfects++;
    else
      count_imperfects = 0;

    previous_interval = current_interval;
    previous_note = note;
    previous_counterpoint_note = counterpoint_note;
  }

  return counterpoint;
}

void Counterpoint::analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval){
  Note next_note = Interval::interval_to_note(note, interval);
  Interval melodic_interval(previous_counterpoint_note, next_note);
  bool can_jump = (reverse_movement or melodic_interval.quantitative <= 4 or melodic_interval.quantitative == 8);
  if(can_jump and melodic_ascendant == melodic_interval.ascendant)
    possible_intervals.push_back(interval);
}

bool Counterpoint::solve(unsigned position, int thirds, int sixths, int tenths, int reverse_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant){
  if(position >= song.size()) return true;

  vector<Interval> possible_intervals;

  Note note = song[position];
  bool reverse_movement = true;

  if(position){
    auto previous_note = song[position - 1];
    auto previous_counterpoint_note = counterpoint[position - 1];
    auto melodic_cantus_interval = Interval(note, previous_note);
    bool melodic_ascendant = (reverse_movement ^ melodic_cantus_interval.ascendant);
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(previous != "P8"){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant));
    }
    if(previous != "P5" && ascendant){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant));
    }

    if(position != song.size() - 1){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant));
      analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant));
    }

    if(possible_intervals.empty()) return false;

    random_shuffle(possible_intervals.begin(), possible_intervals.end());
    int th, si, te, rm;
    for(auto interval : possible_intervals){
      //analisar terças, quintas e décimas
      auto c_note = Interval::interval_to_note(note, interval);
      Interval melodic_interval(previous_counterpoint_note, note);

      th = thirds + (interval.description() == previous and interval.quantitative == 3); //TODO: criar método retornando qualidade
      si = sixths + (interval.description() == previous and interval.quantitative == 6); //TODO: criar método retornando qualidade
      te = tenths + (interval.description() == previous and interval.quantitative == 10); //TODO: criar método retornando qualidade
      rm = reverse_movements + (melodic_interval.ascendant != melodic_ascendant);
      if(th + si + te > 4 || rm > song.size() / 10.0) continue;
      counterpoint.push_back(c_note);
      if(solve(position + 1, th, si, te, rm, song, counterpoint, ascendant)) return true;
      counterpoint.pop_back();
    }
  }else{
    possible_intervals.push_back(Interval("P1", ascendant));
    possible_intervals.push_back(Interval("P8", ascendant));
    if(ascendant) possible_intervals.push_back(Interval("P5", ascendant));
    random_shuffle(possible_intervals.begin(), possible_intervals.end());

    //TODO: mudar regra de última e primeira nota para reverse
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      counterpoint.push_back(c_note);
      if(solve(position + 1, thirds, sixths, tenths, reverse_movements, song, counterpoint, ascendant)) return true;
      counterpoint.pop_back();
    }
  }

  return false;
}
