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
    if(notes[i].rest()) tr++;
    else break;
  }

  return tr;
}

Note Song::back() {
  if(notes.size() > 0)
    return notes.back();
  else
    return Note();
}
