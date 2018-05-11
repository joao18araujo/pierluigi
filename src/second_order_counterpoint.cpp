#include "second_order_counterpoint.h"

bool SecondOrderCounterpoint::dp[201][32][90][5][101];

vector<Note> SecondOrderCounterpoint::dfs_generate_counterpoint(Song & song, bool ascendant, int paralels, int same_movements){
  vector<Note> counterpoint;
  if(song.size() > 201 || paralels > 4 || same_movements > 101)
    return vector<Note>();

  SecondOrderCounterpoint::solve(0, 0, paralels, same_movements, song, counterpoint, ascendant);
  return counterpoint;
}



bool SecondOrderCounterpoint::is_thesis(unsigned compass_position){
  //TODO desenvolver de acordo com o tempo
  return compass_position % 2;
}

bool SecondOrderCounterpoint::solve(unsigned position, unsigned compass_position, int paralels, int same_movements, Song & song, vector<Note> & counterpoint, bool ascendant){
//   if(position == 0){
//     memset(dp, true, sizeof dp);
//     srand(clock());
//   }
//
//   if(position >= song.size()){
//     printf("Total: %d %lu\n", paralels, song.size() - same_movements);
//     return true;
//   }
//
//   if(!dp[position][compass_position][song[position].midi_number][paralels][same_movements]) return false;
//
//   vector<Interval> possible_intervals;
//
//   Note note = song[position];
//   bool reverse_movement = true;
//
//   if(position || compass_position){
//     //TODO lidar com última nota
//
//   }else{
//     //Primeira nota
//   }
//
  return true;
}
