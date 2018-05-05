#include "counterpoint.h"

#include <cstdlib>
#include <ctime>

bool Counterpoint::dp[201][32][90][5][101];

vector<Note> Counterpoint::generate_first_order_counterpoint(vector<Note> & song, bool ascendant, Scale & scale){
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
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), scale);
    }else if(count_imperfects < 4){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), scale);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), scale);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), scale);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), scale);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), scale);
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), scale);
    }

    if(previous != "P5" && previous != "P8"){
      analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), scale);
      if(ascendant)
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), scale);
    }

    if(possible_intervals.empty() && reverse_movement && times_not_reversed++ < 3){
      reverse_movement = false;
      goto begin;
    }

    if(possible_intervals.empty()) return vector<Note>();
    int index = rand() % possible_intervals.size();

    current_interval = possible_intervals[index];
    counterpoint_note = Interval::interval_to_note(note, current_interval);
    if(note.valid) counterpoint.push_back(counterpoint_note);

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

void Counterpoint::analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval, Scale & scale){
  Note next_note = Scale::interval_to_note_on_scale(note, interval, scale);
  if(!next_note.valid){
    return;
  }
  Interval melodic_interval(previous_counterpoint_note, next_note);
  bool can_jump = (reverse_movement or melodic_interval.quantitative <= 4 or melodic_interval.quantitative == 8);
  if((can_jump and melodic_ascendant == melodic_interval.ascendant and note.valid) or previous_counterpoint_note.note == "r")
    possible_intervals.push_back(interval);
}

vector<Note> Counterpoint::dfs_generate_first_order_counterpoint(vector<Note> & song, bool ascendant, int paralels, int same_movements, Scale & scale){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  Counterpoint::solve(0, paralels, same_movements, song, counterpoint, ascendant, scale);
  return counterpoint;
}

vector<Note> Counterpoint::dfs_generate_second_order_counterpoint(vector<Note> & song, bool ascendant, int paralels, int same_movements, Scale & scale){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  Counterpoint::solve(0, paralels, same_movements, song, counterpoint, ascendant, scale);
  return counterpoint;
}

bool Counterpoint::is_thesis(unsigned compass_position){
  //TODO desenvolver de acordo com o tempo
  return compass_position % 2;
}

bool Counterpoint::solve(unsigned position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song.size()){
    printf("Total: %d %lu\n", paralels, song.size() - same_movements);
    return true;
  }

  if(!dp[position][0][song[position].midi_number][paralels][same_movements]) return false;

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

    if(note.note != "r"){
      if(previous != "P8")
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), scale);

      if(previous != "P5" && ascendant)
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), scale);

      if(position == song.size() - 1){
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), scale);
      }else{
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), scale);
      }
      random_shuffle(possible_intervals.begin(), possible_intervals.end());
      int size = possible_intervals.size();

      //intervals with same movement
      if(previous != "P8")
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), scale);
      if(previous != "P5")
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), scale);

      if(position == song.size() - 1){
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), scale);
      }else{
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), scale);
      }
      random_shuffle(possible_intervals.begin() + size, possible_intervals.end());
    }else{
      possible_intervals.push_back(Interval("P1"));
    }

    //TODO deixar os paralelos por último
    if(possible_intervals.empty()){
      dp[position - 1][0][song[position - 1].midi_number][paralels][same_movements] = false;
      return false;
    }

    int par, sm;
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      Interval melodic_interval(previous_counterpoint_note, note);

      par = paralels - (interval.quantitative == previous_interval.quantitative and (interval.quantitative == 3 || interval.quantitative == 6 || interval.quantitative == 10)); //TODO: criar método retornando qualidade
      sm = same_movements - (melodic_interval.ascendant != melodic_ascendant);
      if(par < 0 || sm < 0) continue;
      counterpoint.push_back(c_note);
      if(solve(position + 1, par, sm, song, counterpoint, ascendant, scale)) return true;
      counterpoint.pop_back();
    }
  }else{
    possible_intervals.push_back(Interval("P1", ascendant));
    possible_intervals.push_back(Interval("P8", ascendant));
    if(ascendant) possible_intervals.push_back(Interval("P5", ascendant));
    random_shuffle(possible_intervals.begin(), possible_intervals.end());

    //TODO: mudar regra de última e primeira nota para reverse
    //TODO: analisar note pra não inserir fora de escala ou inválido
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      counterpoint.push_back(c_note);
      if(solve(position + 1, paralels, same_movements, song, counterpoint, ascendant, scale)) return true;
      counterpoint.pop_back();
    }
  }

  dp[position][0][song[position].midi_number][paralels][same_movements] = false;
  return false;
}

bool Counterpoint::solve_2(unsigned position, unsigned compass_position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song.size()){
    printf("Total: %d %lu\n", paralels, song.size() - same_movements);
    return true;
  }

  if(!dp[position][compass_position][song[position].midi_number][paralels][same_movements]) return false;

  vector<Interval> possible_intervals;

  Note note = song[position];
  bool reverse_movement = true;

  if(position || compass_position){
    //TODO lidar com última nota

  }else{
    //Primeira nota
  }

  return true;
}
