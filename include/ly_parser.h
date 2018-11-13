#ifndef LY_PARSER_H
#define LY_PARSER_H

#include <fstream>
#include <iostream>

#include "song.h"
#include "song_reader.h"

class LyParser{
public:
  static Song read_file(string file_path, bool print = true);
  static void convert_file_to_simple_format(string file_path, string output_path = "res/out.ly");
  static void add_counterpoint_to_lilypond(Song & song, string file_path, string output_path = "res/counterpoint.ly");
};

#endif
