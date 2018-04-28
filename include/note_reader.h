#ifndef NOTE_READER_H
#define NOTE_READER_H

#define BELOW_MIDDLE_C_OCTAVE 3

#include <string>
#include <regex>

#include "note.h"

using std::string;
using std::to_string;
using std::regex;
using std::regex_replace;

class NoteReader{
public:
  static Note string_to_note(Note prev, string s);
  static string note_to_string(Note note);
  static int msb(int N);
  static int number_of_on_bits(int N);
};

#endif
