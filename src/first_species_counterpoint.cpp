#include "first_species_counterpoint.h"

Song FirstSpeciesCounterpoint::dfs_generate_counterpoint(Song & c_song, bool ascendant, int paralels, int same_movements){
  song = &c_song;
  Song counterpoint(c_song.scale, c_song.time);
  if(song->size() > 200 || paralels > 4 || same_movements > 600)
    return Song();

  FirstSpeciesCounterpoint::solve(0, paralels, same_movements, counterpoint, ascendant);
  printf("First species generated\n");
  return counterpoint;
}

bool FirstSpeciesCounterpoint::solve(unsigned position, int paralels, int same_movements, Song & counterpoint, bool ascendant){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song->size()){
    // printf("Total: %d %lu\n", paralels, song->size() - same_movements);
    return true;
  }

  // printf("size: %d\n", (int) counterpoint.size());
  // if(position) printf("[%d][%d][%d][%d][%d]\n", position, 0, counterpoint.back().midi_number, paralels, same_movements);
  if(position && !dp[position][0][counterpoint.back().midi_number][paralels][same_movements]) return false;

  vector<Interval> possible_intervals;

  Note note = song->notes[position];
  bool reverse_movement = true;

  if(position){
    auto previous_note = song->notes[position - 1];
    auto previous_counterpoint_note = counterpoint.back();
    auto melodic_cantus_interval = Interval(previous_note, note);
    bool melodic_ascendant = !melodic_cantus_interval.ascendant();
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(not note.rest()){
      if(previous != "P8")
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), nullptr);

      if(previous != "P5" && ascendant)
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), nullptr);

      if(position == song->size() - 1){
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), nullptr);
      }else{
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), nullptr);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), nullptr);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), nullptr);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), nullptr);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), nullptr);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), nullptr);
      }
      random_shuffle(possible_intervals.begin(), possible_intervals.end());
      int size = possible_intervals.size();

      //intervals with same movement
      if(previous != "P8")
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), nullptr);
      if(previous != "P5" && ascendant)
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), nullptr);

      if(position == song->size() - 1){
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), nullptr);
      }else{
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), nullptr);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), nullptr);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), nullptr);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), nullptr);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), nullptr);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), nullptr);
      }
      random_shuffle(possible_intervals.begin() + size, possible_intervals.end());
    }else{
      possible_intervals.push_back(Interval("P1"));
    }

    int par, sm;
    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      Interval melodic_interval(previous_counterpoint_note, note);

      // FIXME confirmar regra de sextas paralelas
      par = paralels - (interval.quantitative == previous_interval.quantitative and (interval.quantitative == 3 || interval.quantitative == 6 || interval.quantitative == 10)); //TODO: criar método retornando qualidade
      sm = same_movements - (melodic_interval.ascendant() != melodic_ascendant);
      if(par < 0 || sm < 0) continue;
      counterpoint.notes.push_back(c_note);
      if(solve(position + 1, par, sm, counterpoint, ascendant)) return true;
      counterpoint.notes.pop_back();
    }
  }else{
    possible_intervals.push_back(Interval("P1", ascendant));
    possible_intervals.push_back(Interval("P8", ascendant));
    if(ascendant) possible_intervals.push_back(Interval("P5", ascendant));
    random_shuffle(possible_intervals.begin(), possible_intervals.end());

    for(auto interval : possible_intervals){
      auto c_note = Interval::interval_to_note(note, interval);
      counterpoint.notes.push_back(c_note);
      if(solve(position + 1, paralels, same_movements, counterpoint, ascendant)) return true;
      counterpoint.notes.pop_back();
    }
  }

  dp[position][0][counterpoint.back().midi_number][paralels][same_movements] = false;
  return false;
}
