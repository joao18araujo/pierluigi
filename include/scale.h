#ifndef SCALE_H
#define SCALE_H

#include <iostream>
#include <unordered_set>
#include <string>

#include "note.h"
#include "interval.h"

using std::unordered_set;
using std::string;
using std::to_string;

#define N_SCALE 12

class Scale{
	public:
    unordered_set<string> permitted_notes;

    Scale();
    Scale(Note first_note, string mode); //TODO mudar nome do atributo

    bool is_valid_note(Note note);
};

#endif
