#ifndef SONG_H
#define SONG_H

#include "note.h"
#include "scale.h"
#include "compass_time.h"

class Song {
public:
  vector<Note> notes;
  Scale scale;
  CompassTime time;

  Song() {}
  Song(Scale s, CompassTime t) : scale(s), time(t) {}

  std::vector<Note>::size_type size() { return notes.size(); }
};

#endif
