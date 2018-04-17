#include "note_reader.h"

Note NoteReader::string_to_note(Note prev, string s){
  string accidental = "", modifier = "";
	string note = "";
	int duration = 0;
  int octave = BELOW_MIDDLE_C_OCTAVE;

	note += s[0];
  //TODO lidar com ponto de aumento
	s.erase(s.begin());
	for (auto& c : s){
		if (isdigit(c)){
			duration = 0;
			duration += (c - '0');
		} else if (isalpha(c))
			accidental += c;
		else
			modifier += c;
	}

  for (auto& c : modifier){
    if (c == '\'')
      octave++;
    else if (c == ',')
      octave--;
  }

  if(not duration)
    duration = prev.duration;

  accidental = regex_replace(accidental, regex("is"), "#");
  accidental = regex_replace(accidental, regex("es"), "\u266D");

	return Note(note, accidental, octave, duration);
}

string NoteReader::note_to_string(Note note){
  int octave_diff = note.octave - BELOW_MIDDLE_C_OCTAVE;
  string s = note.full_note();

  s = regex_replace(s, regex("#"), "is");
  s = regex_replace(s, regex("\u266D"), "es");

  if(octave_diff > 0){
    while(octave_diff--)
      s += "\'";
  }else{
    while(octave_diff++)
      s += ",";
  }
  s += to_string(note.duration);

  return s;
}
