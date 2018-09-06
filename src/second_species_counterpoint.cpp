#include "second_species_counterpoint.h"

bool SecondSpeciesCounterpoint::dp[201][32][90][5][101];
vector<Note> SecondSpeciesCounterpoint::counterpoint;
Song * SecondSpeciesCounterpoint::song;

vector<Note> SecondSpeciesCounterpoint::dfs_generate_counterpoint(Song & c_song, bool ascendant, int paralels, int same_movements){
  song = &c_song;
  if(song->size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  SecondSpeciesCounterpoint::solve(0, 0, paralels, same_movements, ascendant);
  return counterpoint;
}

void SecondSpeciesCounterpoint::analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_note, Note note, Interval interval){
  Note next_note;
  auto previous_counterpoint_note = counterpoint.back();

  if(interval.is_consonant())
    next_note = Scale::interval_to_note_on_scale(note, interval, song->scale);
  else
    next_note = Interval::interval_to_note(note, interval);

  auto previous_interval = Interval(previous_note, previous_counterpoint_note);

  if(!next_note.valid or (interval.is_dissonant() and previous_interval.is_dissonant())){
    return;
  }

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

bool SecondSpeciesCounterpoint::is_thesis(Note & note, int offset){
  // printf("%d %d\n", song->time.compass_duration(), song->time.base_note_duration());
  int compass_position = (note.absolute_time + offset) % song->time.compass_duration();
  int time = compass_position / song->time.base_note_duration() + 1;

  if(song->time.times == 4){
    return (time == 1 || time == 3);
  }else if(song->time.times == 2 || song->time.times == 3){
    return time ==  1;
  }

  return true;
}

bool SecondSpeciesCounterpoint::solve(unsigned position, unsigned compass_position, int paralels, int same_movements, bool ascendant){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song->size()){
    // printf("Total: %d %lu\n", paralels, song->size() - same_movements);
    return true;
  }

  if(!dp[position][compass_position][song->notes[position].midi_number][paralels][same_movements]) return false;

  vector<Interval> possible_intervals;

  Note note = song->notes[position];

  if((position || compass_position) && (position < song->size() - 1)){
    auto previous_note = song->notes[position - 1 + compass_position];
    auto previous_counterpoint_note = counterpoint.back();
    auto melodic_cantus_interval = Interval(note, previous_note);
    bool melodic_ascendant = !melodic_cantus_interval.ascendant; // XOR with true
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(note.note != "r"){
      if(previous != "P8")
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("P8", ascendant));

      if(previous != "P5" && ascendant)
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("P5", ascendant));

      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("M10", ascendant));

      random_shuffle(possible_intervals.begin(), possible_intervals.end());
      int size = possible_intervals.size();

      //intervals with same movement
      if(previous != "P8")
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P8", ascendant));
      if(previous != "P5" && ascendant)
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P5", ascendant));

      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("m3", ascendant));
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("M3", ascendant));
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("m6", ascendant));
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("M6", ascendant));
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("m10", ascendant));
      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("M10", ascendant));

      random_shuffle(possible_intervals.begin() + size, possible_intervals.end());

      if(!is_thesis(note, (note.duration / 2) * compass_position)){
        //Tempo fraco
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P4", ascendant));
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("m2", ascendant));
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("M2", ascendant));
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("m7", ascendant));
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("M7", ascendant));
        // TODO: m9?
      }
    }else{
      possible_intervals.push_back(Interval("P1"));
    }

    // printf("[%u][%u][%d][%d][%d]\n", position - 1 + compass_position, compass_position, song->notes[position - 1 + compass_position].midi_number, paralels, same_movements);
    if(possible_intervals.empty()){
      dp[position - 1 + compass_position][(compass_position+1)%2][song->notes[position - 1 + compass_position].midi_number][paralels][same_movements] = false;

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
      if(solve(position + compass_position, (compass_position + 1)%2, par, sm, ascendant)) return true;
      counterpoint.pop_back();
    }

  }else if(position == song->size() - 1){
    //Última nota
    auto previous_note = song->notes[position - 1];
    auto previous_counterpoint_note = counterpoint.back();
    auto melodic_cantus_interval = Interval(note, previous_note);
    bool melodic_ascendant = !melodic_cantus_interval.ascendant; // XOR with true
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(note.note != "r"){
      analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("P1", ascendant));
      if(previous != "P8")
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("P8", ascendant));
      if(previous != "P5" && ascendant)
        analyse_and_add_interval(true, melodic_ascendant, possible_intervals, previous_note, note, Interval("P5", ascendant));

      random_shuffle(possible_intervals.begin(), possible_intervals.end());
      int size = possible_intervals.size();

      analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P1", ascendant));
      if(previous != "P8")
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P8", ascendant));
      if(previous != "P5" && ascendant)
        analyse_and_add_interval(false, !melodic_ascendant, possible_intervals, previous_note, note, Interval("P5", ascendant));

      random_shuffle(possible_intervals.begin() + size, possible_intervals.end());
    }else{
      possible_intervals.push_back(Interval("P1"));
    }

    int par, sm;
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      Interval melodic_interval(previous_counterpoint_note, note);

      par = paralels - (interval.quantitative == previous_interval.quantitative and (interval.quantitative == 3 || interval.quantitative == 6 || interval.quantitative == 10)); //TODO: criar método retornando qualidade
      sm = same_movements - (melodic_interval.ascendant != melodic_ascendant);
      if(par < 0 || sm < 0) continue;
      counterpoint.push_back(c_note);
      if(solve(position + 1, 0, par, sm, ascendant)) return true;
      counterpoint.pop_back();
    }
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
      if(solve(position + compass_position, (compass_position + 1)%2, paralels, same_movements, ascendant)) return true;
      counterpoint.pop_back();
    }
  }

  dp[position][compass_position][song->notes[position].midi_number][paralels][same_movements] = false;
  return false;
}
