#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "note.h"
#include "interval.h"
#include "note_reader.h"
#include "counterpoint.h"

using namespace std;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12

int main(int argc, char *argv[]){
  vector<Note> song;

  if(argc < 2){
    cerr << "Missing input file" << endl;
    return -1;
  }

  fstream file(argv[1]);
  string s;

  Note prev, note;



  while(file >> s){
    note = NoteReader::string_to_note(prev, s);
    if(!note.valid) continue;
    cout << "[" << s << "] ";
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
    song.push_back(note);
  }

  cout << "\nGenerating counterpoint...\n";

  vector<Note> counterpoint = Counterpoint::dfs_generate_first_order_counterpoint(song, (argc > 2), 4, song.size());

  if(counterpoint.size()){
    cout << "Successfully generated counterpoint! " << counterpoint.size() <<" notes\n\n";
  }else{
    cout << "Couldn't generate counterpoint\n";
    return -2;
  }

  int size = min(song.size(), counterpoint.size());
  for(int i = 0; i < size; ++i){
    Interval in(song[i], counterpoint[i]);
    cout << song[i].full_note_with_octave() << " " << counterpoint[i].full_note_with_octave() << " " << in.description() << endl;
  }

  cout << endl;
  for(auto & c : counterpoint){
    cout << NoteReader::note_to_string(c) << " ";
  }
  cout << endl;


	return 0;
}
