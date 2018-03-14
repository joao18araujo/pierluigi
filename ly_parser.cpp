#include <iostream>
#include <map>
#include <string>

using namespace std;



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
		map<string, int> notes_with_accidental = {
			{"c", 1}, {"bis", 1},
			{"cis", 2}, {"des", 2},
			{"d", 3},
			{"dis", 4}, {"ees", 4},
			{"e", 5}, {"fes", 5},
			{"eis", 6}, {"f", 6},
			{"fis", 7}, {"ges", 7},
			{"g", 8},
			{"gis", 9}, {"aes", 9},
			{"a", 10},
			{"ais", 11}, {"bes", 11},
			{"b", 12}, {"ces", 12}
		};

		map<string, int> notes = {{"c", 1}, {"d", 2}, {"e", 3}, {"f", 4}, {"g", 5}, {"a", 6}, {"b", 7}};


		int duration;
		string note;
		int octave;
		string modifier;
		int midi_number;

		Note(Note& prev, const string& m_note, const string& m_accidental, const string& m_modifier, const int& m_duration) {
			if(not m_duration)
				this->duration = prev.duration;

			note = m_note;
			octave = prev.closest_octave(note);
			for (auto& c : m_modifier){
				if (c == '\'')
					octave++;
				else if (c == ',')
					octave--;
			}


		}

		int closest_octave(string note){
			int this_note_number = notes[this->note];
			int note_number = notes[note];
			int prev_note_number = note_number - 7;
			int next_note_number = note_number + 7;

			int octave = this->octave;
			if((7 + note_number - this_note_number)%7 >= 4){
				if(this_note_number < note_number)
					octave--;
			}else if(this_note_number > note_number){}
				
			return octave;
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
