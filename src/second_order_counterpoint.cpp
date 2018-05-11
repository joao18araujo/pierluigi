#include "second_order_counterpoint.h"

bool SecondOrderCounterpoint::dp[201][32][90][5][101];

vector<Note> SecondOrderCounterpoint::dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  SecondOrderCounterpoint::solve(0, 0, paralels, same_movements, song, counterpoint, ascendant);
  return counterpoint;
}



bool SecondOrderCounterpoint::is_thesis(Note & note, Song & song){
  int compass_position = note.absolute_time % song.time.compass_duration();
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
  bool reverse_movement = true;

  if(position || compass_position && position < song.size() - 1){
    if(is_thesis(note, song)){
      //Tempo forte
    }else{
      //Tempo fraco
    }
  }else if(position == song.size() - 1){
    //Última nota
  }else{
    //Primeira nota
  }

  return true;
}
