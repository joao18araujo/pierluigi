#ifndef NOTE_READER_H
#define NOTE_READER_H

#define BELOW_MIDDLE_C_OCTAVE 3

#include <string>

#include "note.h"

using std::string;

class NoteReader{
public:
  static Note string_to_note(Note prev, string s);
};

#endif
