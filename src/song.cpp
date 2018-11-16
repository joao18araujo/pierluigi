#include "song.h"

unsigned Song::size(){
  return notes.size();
}

unsigned Song::size_without_rest(){
   return notes.size() - trailing_rests();
}

unsigned Song::trailing_rests(){
  int tr = 0;

  for(int i = (int) notes.size() - 1; i >= 0; ++i){
    if(notes[i].note == "r") tr++;
    else break;
  }

  return tr;
}

Note Song::back() {
  return notes.back();
}
