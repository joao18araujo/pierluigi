#ifndef LY_PARSER_H
#define LY_PARSER_H

#include <fstream>
#include <iostream>

#include "song.h"
#include "song_reader.h"

class LyParser{
public:
  static Song read_file(string file_path, bool print = true);
};

#endif
