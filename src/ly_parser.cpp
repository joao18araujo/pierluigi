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

  return song;
}
