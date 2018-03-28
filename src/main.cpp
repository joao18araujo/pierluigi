#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "note.h"
#include "interval.h"
#include "note_reader.h"
#include "counterpoint.h"

using namespace std;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12

int main(int argc, char *argv[]){
  vector<Note *> song;

  if(argc < 2){
    cerr << "Missing input file" << endl;
    return -1;
  }

  fstream file(argv[1]);
  string s;

  Note * prev = nullptr;
  while(file >> s){
    cout << "[" << s << "] ";
    Note * note = NoteReader::string_to_note(prev, s);
    cout << note->description() << " | ";

    if(prev){
      Interval * interval = new Interval(prev, note);
      Interval * new_int = new Interval(interval->description(), interval->ascendant);
      Note * expected = Interval::interval_to_note(prev, *interval);
      cout << interval->full_description() << "," << new_int->full_description() << " | ";
      if(expected) cout << expected->description();
      else cout << "nullptr";
    }
    cout << endl;
    prev = note;
    song.push_back(note);
  }

  cout << "\nGenerating counterpoint...\n";
  vector <Note *> counterpoint = Counterpoint::generate_first_order_counterpoint(song);
  if(counterpoint.empty()){
    cout << "Couldn't generate counterpoint.\n";\
    return -2;
  }else{
    cout << "Successfully generated! " << counterpoint.size() <<" notes\n\n";
  }

  int size = min(song.size(), counterpoint.size());
  for(int i = 0; i < size; ++i){
    Interval in(song[i], counterpoint[i]);
    cout << song[i]->full_note_with_octave() << " " << counterpoint[i]->full_note_with_octave() << " " << in.description() << endl;
  }


	return 0;
}
