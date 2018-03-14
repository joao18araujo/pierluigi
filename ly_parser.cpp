#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>


using namespace std;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12

/*
   { "c", "bis" },  // pos = 0
   { "cis", "des" },
   { "d" },
   { "dis", "ees" },
   { "e", "fes" },
   { "eis", "f" },
   { "fis", "ges" },
   { "g" },
   { "gis", "aes" },
   { "a" },
   { "ais", "bes"},
   { "b", "ces" } // pos = 11
 */

class Note{
	public:
		unordered_map<string, int> notes_with_accidental = {
			{"c", 0}, {"bis", 0},
			{"cis", 1}, {"des", 1},
			{"d", 2},
			{"dis", 3}, {"ees", 3},
			{"e", 4}, {"fes", 4},
			{"eis", 5}, {"f", 5},
			{"fis", 6}, {"ges", 6},
			{"g", 7},
			{"gis", 8}, {"aes", 8},
			{"a", 9},
			{"ais", 10}, {"bes", 10},
			{"b", 11}, {"ces", 11}
		};

		unordered_map<string, int> notes = {{"c", 0}, {"d", 1}, {"e", 2}, {"f", 3}, {"g", 4}, {"a", 5}, {"b", 6}};

		int duration;
		string note;
    string accidental;
		int octave;
		int midi_number;

		Note(Note& prev, const string& note, const string& accidental, const string& modifier, const int& duration) {
			if(not duration)
				this->duration = prev.duration;
      else
        this->duration = duration;

			this->note = note;
      this->accidental = accidental;
			this->octave = BELOW_MIDDLE_C_OCTAVE;
			for (auto& c : modifier){
				if (c == '\'')
					this->octave++;
				else if (c == ',')
					this->octave--;
			}

      this->midi_number = octave * N_SCALE + notes_with_accidental[this->full_note()];
		}

    string full_note(){
      return this->note + this->accidental;
    }
};

Note parse_note(Note prev, string s){
	string accidental = "", modifier = "";
	string note = "";
	int duration = 0;

	note += s[0];
	s.erase(s.begin());
	for (auto& c : s){
		if (isdigit(c)){
			duration *= 10;
			duration += (c - '0');
		} else if (isalpha(c))
			accidental += c;
		else
			modifier += c;
	}

	Note n(prev, note, accidental, modifier, duration);

	return n;
}

int main(){
	return 0;
}
