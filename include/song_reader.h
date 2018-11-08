#ifndef NOTE_READER_H
#define NOTE_READER_H

#include <string>
#include <regex>
#include <sstream>

#include "constants.h"
#include "note.h"
#include "scale.h"
#include "compass_time.h"

using std::string;
using std::to_string;
using std::regex;
using std::regex_replace;
using std::stringstream;

class SongReader{
public:
  static Note string_to_note(Note prev, string s);
  static string note_to_string(Note note);

  static Scale string_to_scale(string line);
  static string scale_to_string(Scale scale);
  static CompassTime string_to_compass_time(string line);
  static string compass_time_to_string(CompassTime compass_time);

  static int msb(int N);
  static int number_of_on_bits(int N);
};

#endif
