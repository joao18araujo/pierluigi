#include "second_order_counterpoint.h"

bool SecondOrderCounterpoint::dp[201][32][90][5][101];

vector<Note> SecondOrderCounterpoint::dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  SecondOrderCounterpoint::solve(0, 0, paralels, same_movements, song, counterpoint, ascendant);
  return counterpoint;
}

void SecondOrderCounterpoint::analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note previous_note, Note note, Interval interval, Scale & scale){
  Note next_note;
  if(interval.is_consonant())
    next_note = Scale::interval_to_note_on_scale(note, interval, scale);
  else
    next_note = Interval::interval_to_note(note, interval);

  if(!next_note.valid){
    return;
  }

  auto previous_interval = Interval(previous_note, previous_counterpoint_note);
  Interval melodic_interval(previous_counterpoint_note, next_note);

  bool is_valid_or_passing = (interval.is_consonant() and previous_interval.is_consonant()) or
                             (melodic_interval == "m2") or
                             (melodic_interval == "M2");

  bool can_jump = (reverse_movement or
                  melodic_interval.quantitative <= 4 or
                  melodic_interval.quantitative == 8);

  if(((can_jump and melodic_ascendant == melodic_interval.ascendant and note.valid) or
      previous_counterpoint_note.note == "r") and is_valid_or_passing)
    possible_intervals.push_back(interval);
}

bool SecondOrderCounterpoint::is_thesis(Note & note, int offset, Song & song){
  int compass_position = (note.absolute_time + offset) % song.time.compass_duration();
  int time = compass_position / song.time.base_note_duration() + 1;

  if(song.time.times == 4){
    return (time == 1 || time == 3);
  }else if(song.time.times == 2 || song.time.times == 3){
    return time ==  1;
  }

  return true;
}

bool SecondOrderCounterpoint::solve(unsigned position, unsigned compass_position, int paralels, int same_movements, Song & song, vector<Note> & counterpoint, bool ascendant){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song.size()){
    printf("Total: %d %lu\n", paralels, song.size() - same_movements);
    return true;
  }

  if(!dp[position][compass_position][song.notes[position].midi_number][paralels][same_movements]) return false;

  vector<Interval> possible_intervals;

  Note note = song.notes[position];

  if((position || compass_position) && (position < song.size() - 1)){

    auto previous_note = song.notes[position - 1];
    auto previous_counterpoint_note = counterpoint.back();
    auto melodic_cantus_interval = Interval(note, previous_note);
    bool melodic_ascendant = !melodic_cantus_interval.ascendant; // XOR with true
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(is_thesis(note, (note.duration / 2) * compass_position, song)){
      //Tempo forte
      if(note.note != "r"){
        if(previous != "P8")
          analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("P8", ascendant), song.scale);

        if(previous != "P5" && ascendant)
          analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("P5", ascendant), song.scale);

        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m3", ascendant), song.scale);
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M3", ascendant), song.scale);
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m6", ascendant), song.scale);
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M6", ascendant), song.scale);
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m10", ascendant), song.scale);
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M10", ascendant), song.scale);

        random_shuffle(possible_intervals.begin(), possible_intervals.end());
        int size = possible_intervals.size();

        //intervals with same movement
        if(previous != "P8")
          analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("P8", ascendant), song.scale);
        if(previous != "P5")
          analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("P5", ascendant), song.scale);

        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m3", ascendant), song.scale);
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M3", ascendant), song.scale);
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m6", ascendant), song.scale);
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M6", ascendant), song.scale);
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m10", ascendant), song.scale);
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M10", ascendant), song.scale);

        random_shuffle(possible_intervals.begin() + size, possible_intervals.end());
      }else{
        possible_intervals.push_back(Interval("P1"));
      }
    }else{
      //Tempo fraco
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("P4", ascendant), song.scale);
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m2", ascendant), song.scale);
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M2", ascendant), song.scale);
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("m7", ascendant), song.scale);
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_counterpoint_note, previous_note, note, Interval("M7", ascendant), song.scale);
      // TODO: m9?
    }

    if(possible_intervals.empty()){
      if(compass_position == 0)
        dp[position - 1][1][song.notes[position - 1].midi_number][paralels][same_movements] = false;
      else
        dp[position][0][song.notes[position].midi_number][paralels][same_movements] = false;

      return false;
    }

    int par, sm;
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      c_note.duration /= 2;
      Interval melodic_interval(previous_counterpoint_note, note);

      par = paralels - (interval.quantitative == previous_interval.quantitative and (interval.quantitative == 3 || interval.quantitative == 6 || interval.quantitative == 10)); //TODO: criar método retornando qualidade
      sm = same_movements - (melodic_interval.ascendant != melodic_ascendant);
      if(par < 0 || sm < 0) continue;
      counterpoint.push_back(c_note);
      if(solve(position + compass_position, (compass_position + 1)%2, par, sm, song, counterpoint, ascendant)) return true;
      counterpoint.pop_back();
    }

  }else if(position == song.size() - 1){
    //Última nota
  }else{
    //Primeira nota
    possible_intervals.push_back(Interval("P1", ascendant));
    possible_intervals.push_back(Interval("P8", ascendant));
    if(ascendant) possible_intervals.push_back(Interval("P5", ascendant));
    random_shuffle(possible_intervals.begin(), possible_intervals.end());

    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      c_note.duration /= 2;
      counterpoint.push_back(c_note);
      if(solve(position, 1, paralels, same_movements, song, counterpoint, ascendant)) return true;
      counterpoint.pop_back();
    }
  }

  return true;
}
