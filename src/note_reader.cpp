#include "note_reader.h"

Note NoteReader::string_to_note(Note prev, string s){
  if(!regex_match(s, regex("[a-gr][ies]*[\',]*\\d*\\.*")))
    return Note();

  string accidental = "", modifier = "";
	string note = "";
	int duration = 0, dots = 0;
  int octave = BELOW_MIDDLE_C_OCTAVE;

	note += s[0];
	s.erase(s.begin());
	for (auto & c : s){
		if (isdigit(c)){
			duration *= 10;
			duration += (c - '0');
		} else if (isalpha(c))
			accidental += c;
		else if(c == '.')
      dots++;
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

  duration = (duration ? 16 / duration : duration);
  //TODO setar valor mínimo (semicolcheia atualmente)

  int increment = duration / 2;
  while(dots--){
    duration += increment;
    increment /= 2;
  }

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
  s += to_string((note.duration ? 16 / note.duration : note.duration)); // printar com pontos

  return s;
}
