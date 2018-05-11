#ifndef SONG_H
#define SONG_H

#include "note.h"
#include "scale.h"

class Song {
public:
  vector<Note> notes;
  Scale scale;
  int times, base_note;

  std::vector<Note>::size_type size() { return notes.size(); }
};

#endif
