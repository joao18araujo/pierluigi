#include "song_reader.h"

Note SongReader::string_to_note(Note prev, string s){
  if(!regex_match(s, regex("[a-gr][ies]*[\',]*\\d*\\.*~?")))
    return Note();

  string accidental = "", modifier = "";
	string note = "";
	int duration = 0, dots = 0;
  int octave = BELOW_MIDDLE_C_OCTAVE;
  bool linked = false;

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
    else if(c == '~')
        linked = true;
    else
			modifier += c;
	}

  for (auto& c : modifier){
    if (c == '\'')
      octave++;
    else if (c == ',')
      octave--;
  }

  if(duration){
    //TODO setar valor mínimo (fusa atualmente)
    duration = (duration ? QUANT / duration : duration);
    int increment = duration / 2;
    while(dots--){
      duration += increment;
      increment /= 2;
    }
  }
  else
    duration = prev.duration;

  accidental = regex_replace(accidental, regex("is"), "#");
  accidental = regex_replace(accidental, regex("es"), "\u266D");

	Note n(note, accidental, octave, duration, linked);
  n.valid = (duration != 0);
  return n;
}

string SongReader::note_to_string(Note note){
  int octave_diff = note.octave - BELOW_MIDDLE_C_OCTAVE;
  string s = note.full_note();

  s = regex_replace(s, regex("#"), "is");
  s = regex_replace(s, regex("\u266D"), "es");

  if(not note.rest()){
    if(octave_diff > 0){
      while(octave_diff--)
        s += "\'";
    }else{
      while(octave_diff++)
        s += ",";
    }
  }

  string duration = to_string((note.duration ? QUANT / msb(note.duration) : 0));
  int total_dots = number_of_on_bits(note.duration) - 1;
  while(total_dots-- > 0){
    duration += ".";
  }

  s += duration;

  if(note.linked){
    s = "~ " + s;
  }

  return s;
}

Scale SongReader::string_to_scale(string line){
  if(!regex_match(line, regex("\\\\key [a-g] \\\\(major|minor)")))
    return Scale();

  stringstream scale_line(line);
  string identificator, key, mode;
  scale_line >> identificator >> key >> mode;
  mode.erase(mode.begin());
  return Scale(key, mode);
}

string SongReader::scale_to_string(Scale scale){
  return "\\key " + scale.base_note.note + " \\" + scale.mode;
}

CompassTime SongReader::string_to_compass_time(string line){
  if(!regex_match(line, regex("\\\\time \\d+\\/\\d+")))
    return CompassTime();

  int times, base_note;
  sscanf(line.c_str(), "\\time %d/%d\n", &times, &base_note);
  return CompassTime(times, base_note);
}

string SongReader::compass_time_to_string(CompassTime compass_time){
  return "\\time " + to_string(compass_time.times) + "/" + to_string(compass_time.base_note);
}

int SongReader::msb(int N) {
  return N ? 1 << (31 - __builtin_clz(N)) : 0;
}

int SongReader::number_of_on_bits(int N) {
  return __builtin_popcount(N);
}

string SongReader::song_clef_to_string(Song & song) {
  int total_midi = 0, total_notes = 0;
  for(auto note : song.notes) {
    if(not note.rest()) {
      total_midi += note.midi_number;
      total_notes++;
    }
  }

  Note treble("b", "", 4);
  Note bass("d", "", 3);

  double mid = total_notes ? (1.0 * total_midi) / total_notes : 0;
  string clef;
  if(treble.midi_number - mid <= mid - bass.midi_number)
    clef = "treble";
  else
    clef = "bass";

  return "\\clef " + clef;
}

string SongReader::song_to_voice_string(Song & song){
  string counterpoint_voice = "\n\nCounterpointVoice = {\n\t" +
          song_clef_to_string(song) + " " +
          scale_to_string(song.scale) + " " +
          compass_time_to_string(song.time) + "\n\t";

  Note prev;
  int note_count = 0;
  for(auto note : song.notes){
    prev = note;
    note_count++;
    if(note_count > 1){
      if(note_count % 10 == 1) counterpoint_voice += "\n\t";
      else counterpoint_voice += " ";
    }
    counterpoint_voice += SongReader::note_to_string(note);
  }

  counterpoint_voice += "\n}\n\n";

  return counterpoint_voice;
}

string SongReader::new_staff_string(){
  return "\n\n\t\t\\new Staff <<\n\t\t\t\\set Staff.instrumentName = \"Contraponto\"\n\t\t\t\\set Staff.shortInstrumentName = \"Ctp.\"\n\t\t\t\\context Staff <<\n\t\t\t\t\\context Voice = \"CounterpointVoice\" { \\CounterpointVoice }\n\t\t\t>>\n\t\t>>\n\n";
}

string SongReader::midi_indicator(){
  return "\n\t\\midi { \\tempo 4 = 120 }\n";
}
