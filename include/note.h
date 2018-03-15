#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>

using std::unordered_map;
using std::string;
using std::to_string;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12

class Note{
	public:
		static unordered_map<string, int> notes_with_accidental;
		static unordered_map<string, int> notes;

		int duration;
		string note;
    string accidental;
		int octave;
		int midi_number;

    Note();
		Note(const string& note, const string& accidental, const int& octave, const int& duration);
    string full_note();
    string description();
};

#endif
