#include "interval.h"

int Interval::expected_semi_tones[] = { 0, 0, 2, 4, 5, 7, 9, 11, 12 };

Interval::Interval(Note * first, Note * second){
  int note_diff = first->note_number - second->note_number;
  int note_with_accidental_diff = first->midi_number - second->midi_number;
  this->quantitative = abs(note_diff) + 1;
  this->ascendant = (note_diff < 0);

  if(note_diff > N_NOTES)
    note_diff %= N_NOTES;

  if(note_with_accidental_diff > N_SCALE)
    note_with_accidental_diff %= N_SCALE;

  int expected_for_perfect = Interval::expected_semi_tones[note_diff];
  int expected_for_major = expected_for_perfect;
  int expected_for_minor = expected_for_major - 1;
  if(is_perfect_candidate(note_diff)){
    if(expected_for_perfect == note_with_accidental_diff)
      this->qualitative = "P";
    else{
      //aumentada ou diminuta
    }
  }else{

    if(expected_for_major == note_with_accidental_diff)
      this->qualitative = "M";
    else if(expected_for_minor == note_with_accidental_diff)
      this->qualitative = "m";
    else{
      //aumentada ou diminuta
    }
  }
}

bool Interval::is_perfect_candidate(int diff){
  return (diff == 0 || diff == 3 || diff == 4 || diff == 7);
}
