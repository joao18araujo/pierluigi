#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "note.h"
#include "song.h"
#include "scale.h"
#include "interval.h"
#include "song_reader.h"
#include "compass_time.h"
#include "first_species_counterpoint.h"
#include "second_species_counterpoint.h"

using namespace std;

int main(int argc, char *argv[]){
  int absolute_time = 0;

  if(argc < 2){
    cerr << "Missing input file" << endl;
    return -1;
  }

  fstream file(argv[1]);
  string line, s_note;
  Note prev, note;

  getline(file, line);
  Scale scale = SongReader::string_to_scale(line);

  getline(file, line);
  CompassTime compass_time = SongReader::string_to_compass_time(line);

  Song song(scale, compass_time);

  while(file >> s_note){
    note = SongReader::string_to_note(prev, s_note);
    if(!note.valid) continue;

    note.absolute_time = absolute_time;
    absolute_time += note.duration;

    cout << "[" << s_note << "] ";
    cout << note.description();

    if(prev.valid){
      Interval interval(prev, note);
      Interval new_int(interval.description(), interval.ascendant);
      Note expected = Interval::interval_to_note(prev,interval);
      cout << " | " << interval.full_description() << "," << new_int.full_description() << " | ";
      if(expected.valid) cout << expected.description();
      else cout << "nullptr";
    }
    cout << endl;
    prev = note;
    song.notes.push_back(note);
  }

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
