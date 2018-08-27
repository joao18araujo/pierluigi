#include "catch.hpp"

#include "note_reader.h"
#include "note.h"

TEST_CASE("Note Reader can receive a string in lilypond format and return a note", "[single-file]"){
  SECTION("when notes are without accidental"){
    Note note = NoteReader::string_to_note(Note(), "c'4");
    REQUIRE(note.midi_number == 60);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "d'4");
    REQUIRE(note.midi_number == 62);
    REQUIRE(note.note_number == 36);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "e'4");
    REQUIRE(note.midi_number == 64);
    REQUIRE(note.note_number == 37);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "f'4");
    REQUIRE(note.midi_number == 65);
    REQUIRE(note.note_number == 38);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "g'4");
    REQUIRE(note.midi_number == 67);
    REQUIRE(note.note_number == 39);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "a'4");
    REQUIRE(note.midi_number == 69);
    REQUIRE(note.note_number == 40);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "b'4");
    REQUIRE(note.midi_number == 71);
    REQUIRE(note.note_number == 41);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "c''4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 42);
    REQUIRE(note.octave == 5);

    note = NoteReader::string_to_note(Note(), "c4");
    REQUIRE(note.midi_number == 48);
    REQUIRE(note.note_number == 28);
    REQUIRE(note.octave == 3);

    note = NoteReader::string_to_note(Note(), "c,4");
    REQUIRE(note.midi_number == 36);
    REQUIRE(note.note_number == 21);
    REQUIRE(note.octave == 2);

    note = NoteReader::string_to_note(Note(), "c,,4");
    REQUIRE(note.midi_number == 24);
    REQUIRE(note.note_number == 14);
    REQUIRE(note.octave == 1);
  }

  SECTION("when notes are with accidental"){
    Note note = NoteReader::string_to_note(Note(), "cis'4");
    REQUIRE(note.midi_number == 61);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "ces'4");
    REQUIRE(note.midi_number == 59);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "cisis'4");
    REQUIRE(note.midi_number == 62);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "ceses'4");
    REQUIRE(note.midi_number == 58);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "des'4");
    REQUIRE(note.midi_number == 61);
    REQUIRE(note.note_number == 36);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "eis'4");
    REQUIRE(note.midi_number == 65);
    REQUIRE(note.note_number == 37);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "fes'4");
    REQUIRE(note.midi_number == 64);
    REQUIRE(note.note_number == 38);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "gis'4");
    REQUIRE(note.midi_number == 68);
    REQUIRE(note.note_number == 39);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "ais'4");
    REQUIRE(note.midi_number == 70);
    REQUIRE(note.note_number == 40);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "bis'4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 41);
    REQUIRE(note.octave == 4);

    note = NoteReader::string_to_note(Note(), "c''4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 42);
    REQUIRE(note.octave == 5);
  }


  SECTION("when notes have duration"){
    Note note = NoteReader::string_to_note(Note(), "c'1");
    REQUIRE(note.duration == 32);

    note = NoteReader::string_to_note(Note(), "c'2");
    REQUIRE(note.duration == 16);

    note = NoteReader::string_to_note(Note(), "c'4");
    REQUIRE(note.duration == 8);

    note = NoteReader::string_to_note(Note(), "c'8");
    REQUIRE(note.duration == 4);

    note = NoteReader::string_to_note(Note(), "c'16");
    REQUIRE(note.duration == 2);

    note = NoteReader::string_to_note(Note(), "c'32");
    REQUIRE(note.duration == 1);
  }

  SECTION("when notes are dotted"){
    Note note = NoteReader::string_to_note(Note(), "c'2.");
    REQUIRE(note.duration == 24);

    note = NoteReader::string_to_note(Note(), "c'2..");
    REQUIRE(note.duration == 28);

    note = NoteReader::string_to_note(Note(), "c'4.");
    REQUIRE(note.duration == 12);

    note = NoteReader::string_to_note(Note(), "c'4..");
    REQUIRE(note.duration == 14);
  }

  SECTION("when notes have duration from previous note"){
    Note note = NoteReader::string_to_note(Note(), "c'2");
    Note note_2 = NoteReader::string_to_note(note, "c");
    REQUIRE(note.duration == note_2.duration);

    note = NoteReader::string_to_note(Note(), "c'4");
    note_2 = NoteReader::string_to_note(note, "c");
    REQUIRE(note.duration == note_2.duration);
  }
}

TEST_CASE("Note Reader can receive a note and return a string", "[single-file]"){
  SECTION("when notes are without accidental"){
    Note note = Note("c", "", 3, 8);
    string s = NoteReader::note_to_string(note);
    REQUIRE(s == "c4");

    note = Note("c", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "c'4");

    note = Note("d", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "d'4");

    note = Note("e", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "e'4");

    note = Note("f", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "f'4");

    note = Note("g", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "g'4");

    note = Note("a", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "a'4");

    note = Note("b", "", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "b'4");

    note = Note("c", "", 5, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "c''4");
  }

  SECTION("when notes are with accidental"){
    Note note = Note("c", "#", 4, 8);
    string s = NoteReader::note_to_string(note);
    REQUIRE(s == "cis'4");

    note = Note("c", "\u266D", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "ces'4");

    note = Note("d", "##", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "disis'4");

    note = Note("e", "\u266D\u266D", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "eeses'4");

    note = Note("f", "#", 4, 2);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "fis'16");

    note = Note("g", "##", 4, 32);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "gisis'1");

    note = Note("a", "\u266D\u266D", 4, 8);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "aeses'4");

    note = Note("b", "#", 4, 16);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "bis'2");

    note = Note("c", "#", 5, 4);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "cis''8");
  }

  SECTION("when notes are dotted"){
    Note note = Note("c", "", 3, 24);
    string s = NoteReader::note_to_string(note);
    REQUIRE(s == "c2.");

    note = Note("c", "", 3, 28);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "c2..");

    note = Note("c", "", 3, 12);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "c4.");

    note = Note("c", "", 3, 14);
    s = NoteReader::note_to_string(note);
    REQUIRE(s == "c4..");
  }
}
