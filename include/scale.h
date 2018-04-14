#ifndef SCALE_H
#define SCALE_H

#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

#include "note.h"
#include "interval.h"

using std::unordered_set;
using std::string;
using std::vector;
using std::to_string;

#define N_SCALE 12

class Scale{
	public:
    unordered_set<string> permitted_notes;

    static Note interval_to_note_on_scale(Note note, Interval interval, Scale scale);

    Scale();
    Scale(Note first_note, string mode); //TODO mudar nome do atributo
    Scale(Note first_note, vector<Interval> intervals);

    bool is_valid_note(Note note);
    void fill_note_set(Note note, vector<Interval> intervals);

};

#endif
