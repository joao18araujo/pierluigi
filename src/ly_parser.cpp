#include <iostream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <note.h>


using namespace std;

#define BELOW_MIDDLE_C_OCTAVE 3
#define N_SCALE 12

Note parse_note(Note, string);

int main(){
	return 0;
}

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
