#include "interval.h"

int Interval::expected_semi_tones[] = { 0, 0, 2, 4, 5, 7, 9, 11, 12 };
string Interval::diminished_classifications[] = {"", "d", "sd", "3xd", "4xd", "5xd"};
string Interval::augmented_classifications[] = {"", "A", "SA", "3xA", "4xA", "5xA"};

string Interval::intervals[][17] = {
  {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" },
  {"P", "A", "SA", "3xA", "4xA", "", "", "", "", "", "", "", "", "", "", "", "" },
  {"d", "m", "M", "A", "SA", "3xA", "4xA", "", "", "", "", "", "", "", "", "", "" },
  {"3xd", "sd", "d", "m", "M", "A", "SA", "3xA", "4xA", "", "", "", "", "", "", "", "" },
  {"", "4xd", "3xd", "sd", "d", "P", "A", "SA", "3xA", "4xA", "5xA", "", "", "", "", "", "" },
  {"", "", "5xd", "4xd", "3xd", "sd", "d", "P", "A", "3xA", "4xA", "", "", "", "", "", "" },
  {"", "", "", "", "4xd", "3xd", "sd", "d", "m", "M", "A", "SA", "3xA", "4xA", "", "", "" },
  {"", "", "", "", "", "", "4xd", "3xd", "sd", "d", "m", "M", "A", "SA", "3xA", "4xA", "" },
  {"", "", "", "", "", "", "", "", "4xd", "3xd", "sd", "d", "P", "A", "SA", "3xA", "4xA" }
};

Interval::Interval(string s_interval, bool ascendant){
  string s_quantitative = "", s_qualitative = "";
  bool is_on_number = false;
  this->ascendant = ascendant;

  for(auto & c : s_interval){
    if(is_on_number)
      s_quantitative += c;
    else
      s_qualitative += c;

    if(c == 'd' || c == 'A' || c == 'm' || c == 'M' || c == 'P'){
      is_on_number = true;
    }
  }

  this->quantitative = stoi(s_quantitative);

  int note_diff = this->quantitative;
  int octave_diff = 0;
  if(note_diff > N_NOTES + 1){
    octave_diff = (note_diff - 2) / N_NOTES;
    note_diff %= N_NOTES;
  }

  for(int i = 0; i < 17; ++i){
    if(intervals[note_diff][i] == s_qualitative){
      this->half_tones = i + octave_diff * N_SCALE;
      this->qualitative = s_qualitative;
    }
  }
}

Interval::Interval(Note first, Note second){
  this->quantitative = abs(first.note_number - second.note_number) + 1;
  this->ascendant = (first.note_number - second.note_number < 0);
  this->half_tones = abs(first.midi_number - second.midi_number);

  classify_qualitative();
}

bool Interval::operator==(const string & s) const{
  return description() == s;
}

bool Interval::is_perfect_candidate(int diff){
  return (diff == 1 || diff == 4 || diff == 5 || diff == 8);
}

bool Interval::is_dissonant(){
  int quali = this->quantitative % N_NOTES;
  // TODO: avaliar baseado nas half notes
  return quali == 2 || quali == 4 || quali == 7;
}

bool Interval::is_consonant(){
  return !is_dissonant();
}

string Interval::description() const{
  return this->qualitative + to_string(this->quantitative);
}

string Interval::full_description() const{
  return this->qualitative + to_string(this->quantitative) + "(" + to_string(this->half_tones) + ")";
}

Note Interval::interval_to_note(Note note, Interval interval){
  // TODO pegar qualitativo e checar enarmonias
  if(note.note == "r"){
    return note;
  }

  int midi_number = note.midi_number + interval.half_tones * (interval.ascendant ? 1 : -1);
  int note_number = note.note_number + (interval.quantitative - 1) * (interval.ascendant ? 1 : -1);
  Note n(midi_number);

  if(n.note_number == note_number){
    n.duration = note.duration;
    return n;
  }else{
    vector<Note> notes = n.enarmonies();
    for(auto & other_note : notes){
      if(other_note.note_number == note_number){
        other_note.duration = note.duration;
        return other_note;
      }
    }
  }

  return Note();
}

void Interval::classify_qualitative(){
  int note_diff = this->quantitative;
  int note_with_accidental_diff = this->half_tones;

  // printf("%d %d x ", note_diff, note_with_accidental_diff);
  while(note_diff > N_NOTES + 1)
    note_diff -= N_NOTES;

  while(note_with_accidental_diff > min(expected_semi_tones[note_diff] + 5, 16))
    note_with_accidental_diff -= N_SCALE;

  // printf("%d %d\n", note_diff, note_with_accidental_diff);
  this->qualitative = intervals[note_diff][note_with_accidental_diff];
}
