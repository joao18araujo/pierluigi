#include "note.h"

unordered_map<string, int> Note::notes_with_accidental_to_number = {
  {"c", 0}, {"bis", 0}, {"deses", 0},
  {"cis", 1}, {"des", 1}, {"bisis", 1},
  {"d", 2}, {"cisis", 2}, {"eeses", 2},
  {"dis", 3}, {"ees", 3}, {"feses", 3},
  {"e", 4}, {"fes", 4}, {"disis", 4},
  {"eis", 5}, {"f", 5}, {"geses", 5},
  {"fis", 6}, {"ges", 6}, {"eisis", 6},
  {"g", 7}, {"fisis", 7}, {"aeses", 7},
  {"gis", 8}, {"aes", 8},
  {"a", 9}, {"gisis", 9}, {"beses", 9},
  {"ais", 10}, {"bes", 10}, {"ceses", 10},
  {"b", 11}, {"ces", 11}, {"aisis", 11}
};

unordered_map<string, int> Note::notes_to_number = {{"c", 0}, {"d", 1}, {"e", 2}, {"f", 3}, {"g", 4}, {"a", 5}, {"b", 6}};

string Note::number_to_notes[] = {"c", "d", "e", "f", "g", "a", "b"};
string Note::number_to_notes_with_accidental[] = {"c", "cis", "d", "dis", "e", "f", "fis", "g", "gis", "a", "ais", "b"};

Note::Note(const string note, const string accidental, const int octave, const int duration) {
  this->valid = true;
  this->note = note;
  this->accidental = accidental;
  this->octave = octave;
  this->duration = duration;
  this->midi_number = (octave + 1) * N_SCALE + notes_with_accidental_to_number[this->full_note()];
  this->note_number = (octave + 1) * N_NOTES + notes_to_number[this->note];
}

Note::Note(const Note & note){
  this->valid = true;
  this->duration = note.duration;
  this->note = note.note;
  this->accidental = note.accidental;
  this->octave = note.octave;
  this->midi_number = note.midi_number;
  this->note_number = note.note_number;
}

//TODO criar construtor que só recebe uma string
Note::Note(){
  this->valid = false;
  this->duration = 0;
  this->note = "C";
  this->accidental = "";
  this->octave = BELOW_MIDDLE_C_OCTAVE;
  this->midi_number = (octave + 1) * N_SCALE + notes_with_accidental_to_number[this->full_note()];
  this->note_number = (octave + 1) * N_NOTES + notes_to_number[this->note];
}

Note::Note(int midi_number, int duration){
  this->valid = true;
  this->duration = duration;
  this->midi_number = midi_number;
  this->octave = (midi_number / N_SCALE) - 1;
  string note_with_accidental = number_to_notes_with_accidental[midi_number % N_SCALE];
  this->set_full_note(note_with_accidental);
  this->note_number = (octave + 1) * N_NOTES + notes_to_number[this->note];
}

string Note::full_note(){
  return this->note + this->accidental;
}

string Note::full_note_with_octave(){
  return this->full_note() + to_string(this->octave);
}

string Note::description(){
  string s = "d:";
  s += to_string(duration) + ",n:" + full_note() + to_string(octave) + ",mn:" + to_string(midi_number)+ ",nn:" + to_string(note_number);
  return s;
}

void Note::set_full_note(string s){
  string only_note = "";
  only_note += s[0];
  this->note = only_note;
  s.erase(s.begin());
  this->accidental = s;
  this->midi_number = (octave + 1) * N_SCALE + notes_with_accidental_to_number[this->full_note()];
  this->note_number = (octave + 1) * N_NOTES + notes_to_number[this->note];
}

vector<Note> Note::enarmonies(){
  vector<Note> v;
  for(auto & p : notes_with_accidental_to_number){
    if(p.first != this->full_note() && p.second == notes_with_accidental_to_number[this->full_note()]){
      Note n(*this);
      n.set_full_note(p.first);
      v.push_back(n);
    }
  }

  return v;
}
