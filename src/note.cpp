#include "note.h"

unordered_map<string, int> Note::notes_with_accidental_to_number = {
  {"c\u266D\u266D", -2},
  {"c\u266D", -1},
  {"c", 0}, {"d\u266D\u266D", 0},
  {"c#", 1}, {"d\u266D", 1},
  {"d", 2}, {"c##", 2}, {"e\u266D\u266D", 2},
  {"d#", 3}, {"e\u266D", 3}, {"f\u266D\u266D", 3},
  {"e", 4}, {"f\u266D", 4}, {"d##", 4},
  {"e#", 5}, {"f", 5}, {"g\u266D\u266D", 5},
  {"f#", 6}, {"g\u266D", 6}, {"e##", 6},
  {"g", 7}, {"f##", 7}, {"a\u266D\u266D", 7},
  {"g#", 8}, {"a\u266D", 8},
  {"a", 9}, {"g##", 9}, {"b\u266D\u266D", 9},
  {"a#", 10}, {"b\u266D", 10},
  {"b", 11}, {"a##", 11},
  {"b#", 12},
  {"b##", 13}
};

unordered_map<string, int> Note::notes_to_number = {{"c", 0}, {"d", 1}, {"e", 2}, {"f", 3}, {"g", 4}, {"a", 5}, {"b", 6}};

string Note::number_to_notes[] = {"c", "d", "e", "f", "g", "a", "b"};
string Note::number_to_notes_with_accidental[] = {"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b"};

Note::Note(const string note, const string accidental, const int octave, const int duration) {
  this->valid = true;
  this->note = note;

  this->accidental = accidental;
  this->duration = duration;

  if(note != "r"){
    this->octave = octave;
    this->midi_number = (octave + 1) * N_SCALE + notes_with_accidental_to_number[this->full_note()];
    this->note_number = (octave + 1) * N_NOTES + notes_to_number[this->note];
  }else{
    this->octave = 0;
    this->midi_number = 0;
    this->note_number = 0;
  }

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
  this->note = "c";
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

string Note::full_note() const{
  return this->note + this->accidental;
}

string Note::full_note_with_octave() const{
  return this->full_note() + to_string(this->octave);
}

string Note::description(){
  string s = "d:";
  s += to_string(duration) + ",n:" + full_note() + to_string(octave) + ",mn:" + to_string(midi_number)+ ",nn:" + to_string(note_number) + ",at:" + to_string(absolute_time);
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
    int note_position = notes_with_accidental_to_number[this->full_note()];
    if(p.first != this->full_note() &&
      (p.second % N_SCALE) == (note_position % N_SCALE)){
      Note n(*this);
      if(note_position > p.second)
        n.octave++;
      else if(note_position < p.second)
        n.octave--;

      n.set_full_note(p.first);
      v.push_back(n);
    }
  }

  return v;
}

bool Note::operator==(const Note & note) const{
  return full_note_with_octave() == note.full_note_with_octave();
}

bool Note::operator!=(const Note & note) const{
  return full_note_with_octave() != note.full_note_with_octave();
}
