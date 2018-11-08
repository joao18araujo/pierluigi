#include "ly_parser.h"

Song LyParser::read_file(string file_path, bool print){
  std::fstream file(file_path);
  string line, s_note;
  Note prev, note;
  int absolute_time = 0;

  if(!file.is_open()){
    std::cerr << "Error: File not found\n";
    exit(-1);
  }

  getline(file, line);
  Scale scale = SongReader::string_to_scale(line);
  if(print) printf("Key: %s %s\n", scale.base_note.note.c_str(), scale.mode.c_str());

  getline(file, line);
  CompassTime compass_time = SongReader::string_to_compass_time(line);
  if(print) printf("Time: %d/%d\n", compass_time.times, compass_time.base_note);

  Song song(scale, compass_time);

  while(file >> s_note){
    note = SongReader::string_to_note(prev, s_note);
    if(!note.valid) continue;

    note.absolute_time = absolute_time;
    absolute_time += note.duration;

    if(print) std::cout << "[" << s_note << "] ";
    if(print) std::cout << note.description();

    if(prev.valid){
      Interval interval(prev, note);
      Interval new_int(interval.description(), interval.direction);
      Note expected = Interval::interval_to_note(prev,interval);
      if(print){
        std::cout << " | " << interval.full_description() << "," << new_int.full_description() << " | ";
        if(expected.valid) std::cout << expected.description();
        else std::cout << "nullptr";
      }
    }
    if(print) std::cout << std::endl;
    prev = note;
    song.notes.push_back(note);
  }

  file.close();
  return song;
}

void LyParser::convert_file_to_simple_format(string file_path, string output_path) {
  std::fstream file(file_path);

  string line, s;

  if(!file.is_open()){
    std::cerr << "Error: File not found\n";
    exit(-2);
  }

  string s_scale = "", s_time = "", s_notes = "";
  Note note, prev;
  int note_count = 0;
  while(file >> s){
    if(s == "\\key" && s_scale == ""){
      string key, mode;
      file >> key >> mode;
      Scale scale = SongReader::string_to_scale(s + " " + key + " " + mode);
      s_scale = SongReader::scale_to_string(scale);
    }else if(s == "\\time" or s == "\\numericTimeSignature\\time"){
      string time_and_note;
      file >> time_and_note;
      CompassTime compass_time = SongReader::string_to_compass_time("\\time " + time_and_note);
      s_time = SongReader::compass_time_to_string(compass_time);
    }else if(s == "\\relative"){
      if(s_scale == ""){
        std::cerr << "Error: Lilypond with relative pitches\n";
        file.close();
        exit(-5);
      }
    }else{
      note = SongReader::string_to_note(prev, s);
      if(note.valid){
        prev = note;
        note_count++;
        if(note_count > 1 and note_count%10 == 1) s_notes += "\n";
        s_notes += SongReader::note_to_string(note) + " ";

      }
    }

    if(s == "}" and s_notes != "") break;
  }

  if(s_scale == ""){
    std::cerr << "Error: Lilypond without scale\n";
    file.close();
    exit(-3);
  }

  if(s_time == ""){
    std::cerr << "Error: Lilypond without time\n";
    file.close();
    exit(-4);
  }

  std::ofstream output(output_path);
  output << s_scale << std::endl;
  output << s_time << std::endl;
  output << s_notes << std::endl;
}
