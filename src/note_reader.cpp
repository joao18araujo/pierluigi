#include "note_reader.h"

Note NoteReader::string_to_note(Note * prev, string s){
  string accidental = "", modifier = "";
	string note = "";
	int duration = 0;
  int octave = BELOW_MIDDLE_C_OCTAVE;

	note += s[0];
	s.erase(s.begin());
	for (auto& c : s){
		if (isdigit(c)){
			duration *= 10;
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

  if(not duration && prev)
    duration = prev->duration;

	Note n(note, accidental, octave, duration);

	return n;
}
