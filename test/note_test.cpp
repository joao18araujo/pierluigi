#include "catch.hpp"

#include "note.h"

TEST_CASE("Note can be constructed with midi number", "[single-file]"){
  Note note;
  note = Note(59, 4);
  REQUIRE(note.note == "b");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 3);
  REQUIRE(note.duration == 4);
  REQUIRE(note.midi_number == 59);
  REQUIRE(note.note_number == 34);

  note = Note(60);
  REQUIRE(note.note == "c");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 60);
  REQUIRE(note.note_number == 35);

  note = Note(61);
  REQUIRE(note.note == "c");
  REQUIRE(note.accidental == "#");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 61);
  REQUIRE(note.note_number == 35);

  note = Note(62);
  REQUIRE(note.note == "d");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 62);
  REQUIRE(note.note_number == 36);


  note = Note(63);
  REQUIRE(note.note == "d");
  REQUIRE(note.accidental == "#");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 63);
  REQUIRE(note.note_number == 36);

  note = Note(64);
  REQUIRE(note.note == "e");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 64);
  REQUIRE(note.note_number == 37);

  note = Note(65);
  REQUIRE(note.note == "f");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 65);
  REQUIRE(note.note_number == 38);

  note = Note(66);
  REQUIRE(note.note == "f");
  REQUIRE(note.accidental == "#");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 66);
  REQUIRE(note.note_number == 38);

  note = Note(67);
  REQUIRE(note.note == "g");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 67);
  REQUIRE(note.note_number == 39);

  note = Note(68);
  REQUIRE(note.note == "g");
  REQUIRE(note.accidental == "#");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 68);
  REQUIRE(note.note_number == 39);

  note = Note(69);
  REQUIRE(note.note == "a");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 69);
  REQUIRE(note.note_number == 40);

  note = Note(70);
  REQUIRE(note.note == "a");
  REQUIRE(note.accidental == "#");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 70);
  REQUIRE(note.note_number == 40);


  note = Note(71);
  REQUIRE(note.note == "b");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 4);
  REQUIRE(note.midi_number == 71);
  REQUIRE(note.note_number == 41);


  note = Note(72);
  REQUIRE(note.note == "c");
  REQUIRE(note.accidental == "");
  REQUIRE(note.octave == 5);
  REQUIRE(note.midi_number == 72);
  REQUIRE(note.note_number == 42);
}

TEST_CASE("Note can be constructed with a string", "[single-file]"){
  Note note;
  note = Note("b", "", 3, 4);
  REQUIRE(note.duration == 4);
  REQUIRE(note.midi_number == 59);
  REQUIRE(note.note_number == 34);

  note = Note("b", "#", 3);
  REQUIRE(note.midi_number == 60);
  REQUIRE(note.note_number == 34);

  note = Note("c", "", 4);
  REQUIRE(note.midi_number == 60);
  REQUIRE(note.note_number == 35);

  note = Note("d", "\u266D\u266D", 4);
  REQUIRE(note.midi_number == 60);
  REQUIRE(note.note_number == 36);

  note = Note("c", "#", 4);
  REQUIRE(note.midi_number == 61);
  REQUIRE(note.note_number == 35);

  note = Note("d", "\u266D", 4);
  REQUIRE(note.midi_number == 61);
  REQUIRE(note.note_number == 36);

  note = Note("c", "##", 4);
  REQUIRE(note.midi_number == 62);
  REQUIRE(note.note_number == 35);

  note = Note("d", "", 4);
  REQUIRE(note.midi_number == 62);
  REQUIRE(note.note_number == 36);

  note = Note("d", "#", 4);
  REQUIRE(note.midi_number == 63);
  REQUIRE(note.note_number == 36);

  note = Note("e", "\u266D", 4);
  REQUIRE(note.midi_number == 63);
  REQUIRE(note.note_number == 37);

  note = Note("e", "", 4);
  REQUIRE(note.midi_number == 64);
  REQUIRE(note.note_number == 37);

  note = Note("f", "", 4);
  REQUIRE(note.midi_number == 65);
  REQUIRE(note.note_number == 38);

  note = Note("f", "#", 4);
  REQUIRE(note.midi_number == 66);
  REQUIRE(note.note_number == 38);
}

TEST_CASE("Each note has one or more enarmonies", "[single-file]"){
  Note note;
  note = Note("c", "", 4);
  auto enarmonies = note.enarmonies();
  REQUIRE(enarmonies[0].full_note() == "b#");
  REQUIRE(enarmonies[0].midi_number == note.midi_number);
  REQUIRE(enarmonies[1].full_note() == "d\u266D\u266D");
  REQUIRE(enarmonies[1].midi_number == note.midi_number);

  note = Note("g", "#", 4);
  enarmonies = note.enarmonies();
  REQUIRE(enarmonies[0].full_note() == "a\u266D");
  REQUIRE(enarmonies[0].midi_number == note.midi_number);

  note = Note("e", "", 4);
  enarmonies = note.enarmonies();
  REQUIRE(enarmonies[0].full_note() == "d##");
  REQUIRE(enarmonies[0].midi_number == note.midi_number);
  REQUIRE(enarmonies[1].full_note() == "f\u266D");
  REQUIRE(enarmonies[1].midi_number == note.midi_number);
}
