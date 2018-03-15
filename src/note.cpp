#include "note.h"

unordered_map<string, int> Note::notes_with_accidental = {
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

unordered_map<string, int> Note::notes = {{"c", 0}, {"d", 1}, {"e", 2}, {"f", 3}, {"g", 4}, {"a", 5}, {"b", 6}};

Note::Note(const string& note, const string& accidental, const int& octave, const int& duration) {
  this->note = note;
  this->accidental = accidental;
  this->octave = octave;
  this->duration = duration;
  this->midi_number = (octave + 1) * N_SCALE + notes_with_accidental[this->full_note()];
}

Note::Note(){
  this->duration = 0;
  this->note = "C";
  this->accidental = "";
  this->octave = BELOW_MIDDLE_C_OCTAVE;
  this->midi_number = 40;
}

string Note::full_note(){
  return this->note + this->accidental;
}

string Note::description(){
  string s = "Duration: ";
  s += to_string(duration) + ", note: " + full_note() + to_string(octave) + ", midi_number: " + to_string(midi_number);
  return s;
}
