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

using namespace std;

int main(int argc, char *argv[]){

  if(argc < 2){
    cerr << "Missing input file" << endl;
    return -1;
  }

  Song song = LyParser::read_file(argv[1]);

  cout << "\nGenerating counterpoint...\n";

  vector<Note> counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, (argc > 2), 4, song.size());

  cout << "First species generated\n";

  vector<Note> second_counterpoint = SecondSpeciesCounterpoint::dfs_generate_counterpoint(song, (argc > 2), 4, song.size());

  cout << "Second species generated\n";

  if(counterpoint.size()){
    cout << "Successfully generated counterpoint! " << counterpoint.size() <<" notes\n\n";
  }else{
    cout << "Couldn't generate counterpoint\n";
    return -2;
  }

  int size = min(song.size(), counterpoint.size());
  for(int i = 0; i < size; ++i){
    Interval in(song.notes[i], counterpoint[i]);
    cout << song.notes[i].full_note_with_octave() << " " << counterpoint[i].full_note_with_octave() << " " << in.description() << endl;
  }

  cout << endl;

  cout << "First Species Counterpoint\n";
  for(auto & c : counterpoint){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;

  cout << endl;
  cout << "Second Species Counterpoint\n";
  for(auto & c : second_counterpoint){
    cout << SongReader::note_to_string(c) << " ";
  }
  cout << endl;


	return 0;
}
