#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <string>

using std::unordered_map;
using std::vector;
using std::string;
using std::to_string;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12
#define N_NOTES 7

class Note{
	public:
		static unordered_map<string, int> notes_with_accidental_to_number;
		static unordered_map<string, int> notes_to_number;
    static string number_to_notes[10];
    static string number_to_notes_with_accidental[15];

		int duration;
		string note;
    string accidental;
		int octave;
		int midi_number;
    int note_number;

    Note();
    Note(Note * note);
    Note(int midi_number, int duration = 0);
		Note(const string& note, const string& accidental, const int& octave, const int duration);
    string full_note();
    string full_note_with_octave();
    string description();
    void set_full_note(string s);
    vector<Note *> enarmonies();

};

#endif
