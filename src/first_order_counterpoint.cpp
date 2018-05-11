#include "first_order_counterpoint.h"

bool FirstOrderCounterpoint::dp[201][90][5][101];

vector<Note> FirstOrderCounterpoint::dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  FirstOrderCounterpoint::solve(0, paralels, same_movements, song, counterpoint, ascendant);
  return counterpoint;
}

bool FirstOrderCounterpoint::solve(unsigned position, int paralels, int same_movements, Song & song, vector<Note> & counterpoint, bool ascendant){
  if(position == 0){
    memset(dp, true, sizeof dp);
    srand(clock());
  }

  if(position >= song.size()){
    printf("Total: %d %lu\n", paralels, song.size() - same_movements);
    return true;
  }

  if(!dp[position][song.notes[position].midi_number][paralels][same_movements]) return false;

  vector<Interval> possible_intervals;

  Note note = song.notes[position];
  bool reverse_movement = true;

  if(position){
    auto previous_note = song.notes[position - 1];
    auto previous_counterpoint_note = counterpoint[position - 1];
    auto melodic_cantus_interval = Interval(note, previous_note);
    bool melodic_ascendant = (reverse_movement ^ melodic_cantus_interval.ascendant);
    auto previous_interval = Interval(previous_note, previous_counterpoint_note);
    string previous = previous_interval.description();

    if(note.note != "r"){
      if(previous != "P8")
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), song.scale);

      if(previous != "P5" && ascendant)
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), song.scale);

      if(position == song.size() - 1){
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), song.scale);
      }else{
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), song.scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), song.scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), song.scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), song.scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), song.scale);
        analyse_and_add_interval(reverse_movement, melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), song.scale);
      }
      random_shuffle(possible_intervals.begin(), possible_intervals.end());
      int size = possible_intervals.size();

      //intervals with same movement
      if(previous != "P8")
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P8", ascendant), song.scale);
      if(previous != "P5")
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P5", ascendant), song.scale);

      if(position == song.size() - 1){
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("P1", ascendant), song.scale);
      }else{
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m3", ascendant), song.scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M3", ascendant), song.scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m6", ascendant), song.scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M6", ascendant), song.scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("m10", ascendant), song.scale);
        analyse_and_add_interval(!reverse_movement, !melodic_ascendant, possible_intervals, previous_counterpoint_note, note, Interval("M10", ascendant), song.scale);
      }
      random_shuffle(possible_intervals.begin() + size, possible_intervals.end());
    }else{
      possible_intervals.push_back(Interval("P1"));
    }

    //TODO deixar os paralelos por último
    if(possible_intervals.empty()){
      dp[position - 1][song.notes[position - 1].midi_number][paralels][same_movements] = false;
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
      if(solve(position + 1, par, sm, song, counterpoint, ascendant)) return true;
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
      if(solve(position + 1, paralels, same_movements, song, counterpoint, ascendant)) return true;
      counterpoint.pop_back();
    }
  }

  dp[position][song.notes[position].midi_number][paralels][same_movements] = false;
  return false;
}