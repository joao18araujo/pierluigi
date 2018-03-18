#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "note.h"
#include "interval.h"
#include "note_reader.h"


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

  Note prev;
  while(file >> s){
    cout << "[" << s << "]\n";
    Note note = NoteReader::string_to_note(&prev, s);
    Interval interval(&prev, &note);
    cout << note.description() << " | " << interval.description() << endl;
    prev = note;
  }

	return 0;
}
