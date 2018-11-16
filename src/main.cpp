#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include <regex>
#include "note.h"
#include "song.h"
#include "interval.h"
#include "ly_parser.h"
#include "first_species_counterpoint.h"
#include "second_species_counterpoint.h"
#include "third_species_counterpoint.h"
#include "fourth_species_counterpoint.h"

using namespace std;

int main(int argc, char *argv[]){

  if(argc < 4){
    cerr << "Missing parameters: prog input species ascendant" << endl;
    return -1;
  }

  string input_path(argv[1]);
  string simple_input_path = "res/simple_input.ly";
  int species = atoi(argv[2]);
  bool ascendant = (string(argv[3]) == "true");
  printf("[%s] [%d] [%d]\n", input_path.c_str(), species, ascendant);

  LyParser::convert_file_to_simple_format(input_path, simple_input_path);
  Song song = LyParser::read_file(simple_input_path);

  Song counterpoint, second_counterpoint, third_counterpoint, fourth_counterpoint;
  switch (species) {
    case 1:
      cout << "\nGenerating first species counterpoint...\n";
      counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size());
    break;

    case 2:
      cout << "\nGenerating second species counterpoint...\n";
      counterpoint = SecondSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 2);
    break;

    case 3:
      cout << "\nGenerating third species counterpoint...\n";
      counterpoint = ThirdSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 4);
    break;

    case 4:
      cout << "\nGenerating fourth species counterpoint...\n";
      counterpoint = FourthSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 2);
    break;

    default:
      cout << "\nGenerating counterpoints...\n";
      counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size());
      second_counterpoint = SecondSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 2);
      third_counterpoint = ThirdSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 4);
      fourth_counterpoint = FourthSpeciesCounterpoint::dfs_generate_counterpoint(song, ascendant, 4, song.size() * 2);
    break;
  }

  if(counterpoint.size())
    LyParser::add_counterpoint_to_lilypond(counterpoint, input_path, "res/counterpoint_1.ly");

  if(second_counterpoint.size())
    LyParser::add_counterpoint_to_lilypond(second_counterpoint, input_path, "res/counterpoint_2.ly");

  if(third_counterpoint.size())
    LyParser::add_counterpoint_to_lilypond(third_counterpoint, input_path, "res/counterpoint_3.ly");

  if(fourth_counterpoint.size())
    LyParser::add_counterpoint_to_lilypond(fourth_counterpoint, input_path, "res/counterpoint_4.ly");


  if(counterpoint.size() == 0){
    cout << "Couldn't generate counterpoint\n";
    return -2;
  }

  int size = min(song.size(), counterpoint.size());
  for(int i = 0; i < size; ++i){
    Interval in(song.notes[i], counterpoint.notes[i]);
    cout << song.notes[i].full_note_with_octave() << " " << counterpoint.notes[i].full_note_with_octave() << " " << in.description() << endl;
  }

  cout << endl;

  cout << "First Species Counterpoint\n";
  for(auto & c : counterpoint.notes){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;
  printf("Size: %d\n", (int) counterpoint.size());

  cout << endl;
  cout << "Second Species Counterpoint\n";
  for(auto & c : second_counterpoint.notes){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;
  printf("Size: %d\n", (int) second_counterpoint.size());

  cout << endl;
  cout << "Third Species Counterpoint\n";
  for(auto & c : third_counterpoint.notes){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;
  printf("Size: %d\n", (int) third_counterpoint.size());

  cout << endl;
  cout << "Fourth Species Counterpoint\n";
  for(auto & c : fourth_counterpoint.notes){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;
  printf("Size: %d\n", (int) fourth_counterpoint.size());

	return 0;
}
