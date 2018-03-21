#include "interval.h"

int Interval::expected_semi_tones[] = { 0, 0, 2, 4, 5, 7, 9, 11, 12 };
string Interval::diminished_classifications[] = {"", "d", "sd", "3xd", "4xd", "5xd"};
string Interval::augmented_classifications[] = {"", "A", "SA", "3xA", "4xA", "5xA"};

Interval::Interval(string s_interval){

}

Interval::Interval(Note * first, Note * second){
  int note_diff = abs(first->note_number - second->note_number) + 1;
  int note_with_accidental_diff = abs(first->midi_number - second->midi_number);
  this->quantitative = note_diff;
  this->ascendant = (first->note_number - second->note_number < 0);

  if(note_diff > N_NOTES)
    note_diff %= N_NOTES;

  if(note_with_accidental_diff > N_SCALE)
    note_with_accidental_diff %= N_SCALE;

  if(is_perfect_candidate(note_diff)){
    int expected_for_perfect = Interval::expected_semi_tones[note_diff];
    int diff = min(5, abs(note_with_accidental_diff - expected_for_perfect));
    if(note_with_accidental_diff == expected_for_perfect){
      this->qualitative = "P";
    }else if(note_with_accidental_diff > expected_for_perfect){
      this->qualitative = augmented_classifications[diff];
    }else{
      this->qualitative = diminished_classifications[diff];
    }
  }else{
    int expected_for_major = Interval::expected_semi_tones[note_diff];
    int expected_for_minor = expected_for_major - 1;
    int minor_diff = min(5, abs(note_with_accidental_diff - expected_for_minor));
    int major_diff = min(5, abs(note_with_accidental_diff - expected_for_major));
    if(note_with_accidental_diff == expected_for_major){
      this->qualitative = "M";
    }else if(note_with_accidental_diff == expected_for_minor){
      this->qualitative = "m";
    }else if(note_with_accidental_diff > expected_for_major){
      this->qualitative = augmented_classifications[major_diff];
    }else{
      this->qualitative = diminished_classifications[minor_diff];
    }
  }
}

bool Interval::is_perfect_candidate(int diff){
  return (diff == 1 || diff == 4 || diff == 5 || diff == 8);
}

string Interval::description(){
  return this->qualitative + to_string(this->quantitative);
}

Note Interval::interval_to_note(Note * note, Interval * interval){
  // TODO pegar qualitativo e checar enarmonias
  return Note();
}
