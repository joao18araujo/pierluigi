#include "scale.h"

Scale::Scale(){
  Note note("c", "");
  permitted_notes.insert(note.full_note());
  Interval m2 = Interval("m2");
  for(int i = 1; i < N_SCALE; ++i){
    note = Interval::interval_to_note(note, m2);
    permitted_notes.insert(note.full_note());
  }
}

Scale::Scale(Note note, string mode){
  if(mode == "major"){
    permitted_notes.insert(note.full_note());
    Interval m2 = Interval("m2");
    Interval M2 = Interval("M2");
    vector<Interval> intervals {M2, M2, m2, M2, M2, M2};
    for(auto & interval : intervals){
      note = Interval::interval_to_note(note, interval);
      permitted_notes.insert(note.full_note());
    }
  }
}

bool Scale::is_valid_note(Note note){
  return (permitted_notes.find(note.full_note()) != permitted_notes.end());
}
