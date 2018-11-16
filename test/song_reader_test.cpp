#include "catch.hpp"

#include "song_reader.h"
#include "note.h"

TEST_CASE("Song Reader can receive a string in lilypond format and return a note", "[single-file]"){
  SECTION("when notes are without accidental"){
    Note note = SongReader::string_to_note(Note(), "c'4");
    REQUIRE(note.midi_number == 60);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "d'4");
    REQUIRE(note.midi_number == 62);
    REQUIRE(note.note_number == 36);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "e'4");
    REQUIRE(note.midi_number == 64);
    REQUIRE(note.note_number == 37);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "f'4");
    REQUIRE(note.midi_number == 65);
    REQUIRE(note.note_number == 38);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "g'4");
    REQUIRE(note.midi_number == 67);
    REQUIRE(note.note_number == 39);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "a'4");
    REQUIRE(note.midi_number == 69);
    REQUIRE(note.note_number == 40);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "b'4");
    REQUIRE(note.midi_number == 71);
    REQUIRE(note.note_number == 41);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "c''4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 42);
    REQUIRE(note.octave == 5);

    note = SongReader::string_to_note(Note(), "c4");
    REQUIRE(note.midi_number == 48);
    REQUIRE(note.note_number == 28);
    REQUIRE(note.octave == 3);

    note = SongReader::string_to_note(Note(), "c,4");
    REQUIRE(note.midi_number == 36);
    REQUIRE(note.note_number == 21);
    REQUIRE(note.octave == 2);

    note = SongReader::string_to_note(Note(), "c,,4");
    REQUIRE(note.midi_number == 24);
    REQUIRE(note.note_number == 14);
    REQUIRE(note.octave == 1);
  }

  SECTION("when notes are with accidental"){
    Note note = SongReader::string_to_note(Note(), "cis'4");
    REQUIRE(note.midi_number == 61);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "ces'4");
    REQUIRE(note.midi_number == 59);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "cisis'4");
    REQUIRE(note.midi_number == 62);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "ceses'4");
    REQUIRE(note.midi_number == 58);
    REQUIRE(note.note_number == 35);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "des'4");
    REQUIRE(note.midi_number == 61);
    REQUIRE(note.note_number == 36);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "eis'4");
    REQUIRE(note.midi_number == 65);
    REQUIRE(note.note_number == 37);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "fes'4");
    REQUIRE(note.midi_number == 64);
    REQUIRE(note.note_number == 38);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "gis'4");
    REQUIRE(note.midi_number == 68);
    REQUIRE(note.note_number == 39);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "ais'4");
    REQUIRE(note.midi_number == 70);
    REQUIRE(note.note_number == 40);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "bis'4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 41);
    REQUIRE(note.octave == 4);

    note = SongReader::string_to_note(Note(), "c''4");
    REQUIRE(note.midi_number == 72);
    REQUIRE(note.note_number == 42);
    REQUIRE(note.octave == 5);
  }


  SECTION("when notes have duration"){
    Note note = SongReader::string_to_note(Note(), "c'1");
    REQUIRE(note.duration == 32);

    note = SongReader::string_to_note(Note(), "c'2");
    REQUIRE(note.duration == 16);

    note = SongReader::string_to_note(Note(), "c'4");
    REQUIRE(note.duration == 8);

    note = SongReader::string_to_note(Note(), "c'8");
    REQUIRE(note.duration == 4);

    note = SongReader::string_to_note(Note(), "c'16");
    REQUIRE(note.duration == 2);

    note = SongReader::string_to_note(Note(), "c'32");
    REQUIRE(note.duration == 1);
  }

  SECTION("when notes are dotted"){
    Note note = SongReader::string_to_note(Note(), "c'2.");
    REQUIRE(note.duration == 24);

    note = SongReader::string_to_note(Note(), "c'2..");
    REQUIRE(note.duration == 28);

    note = SongReader::string_to_note(Note(), "c'4.");
    REQUIRE(note.duration == 12);

    note = SongReader::string_to_note(Note(), "c'4..");
    REQUIRE(note.duration == 14);
  }

  SECTION("when notes have duration from previous note"){
    Note note = SongReader::string_to_note(Note(), "c'2");
    Note note_2 = SongReader::string_to_note(note, "c");
    REQUIRE(note.duration == note_2.duration);

    note = SongReader::string_to_note(Note(), "c'4");
    note_2 = SongReader::string_to_note(note, "c");
    REQUIRE(note.duration == note_2.duration);
  }

  SECTION("when is a rest"){
    Note note = SongReader::string_to_note(Note(), "r4");
    REQUIRE(note.note == "r");
    REQUIRE(note.rest() == true);
    REQUIRE(note.midi_number == 0);
    REQUIRE(note.note_number == 0);
    REQUIRE(note.octave == 0);
  }
}

TEST_CASE("Song Reader can receive a note and return a string", "[single-file]"){
  SECTION("when notes are without accidental"){
    Note note = Note("c", "", 3, 8);
    string s = SongReader::note_to_string(note);
    REQUIRE(s == "c4");

    note = Note("c", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "c'4");

    note = Note("d", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "d'4");

    note = Note("e", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "e'4");

    note = Note("f", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "f'4");

    note = Note("g", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "g'4");

    note = Note("a", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "a'4");

    note = Note("b", "", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "b'4");

    note = Note("c", "", 5, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "c''4");
  }

  SECTION("when notes are with accidental"){
    Note note = Note("c", "#", 4, 8);
    string s = SongReader::note_to_string(note);
    REQUIRE(s == "cis'4");

    note = Note("c", "\u266D", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "ces'4");

    note = Note("d", "##", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "disis'4");

    note = Note("e", "\u266D\u266D", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "eeses'4");

    note = Note("f", "#", 4, 2);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "fis'16");

    note = Note("g", "##", 4, 32);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "gisis'1");

    note = Note("a", "\u266D\u266D", 4, 8);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "aeses'4");

    note = Note("b", "#", 4, 16);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "bis'2");

    note = Note("c", "#", 5, 4);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "cis''8");
  }

  SECTION("when notes are dotted"){
    Note note = Note("c", "", 3, 24);
    string s = SongReader::note_to_string(note);
    REQUIRE(s == "c2.");

    note = Note("c", "", 3, 28);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "c2..");

    note = Note("c", "", 3, 12);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "c4.");

    note = Note("c", "", 3, 14);
    s = SongReader::note_to_string(note);
    REQUIRE(s == "c4..");
  }
}


TEST_CASE("Song Reader can receive a string and return a scale", "[single-file]"){
  Scale scale;
  scale = SongReader::string_to_scale("\\key c \\major");
  REQUIRE(scale.is_valid_note(Note("c")) == true);
  REQUIRE(scale.is_valid_note(Note("c#")) == false);
  REQUIRE(scale.is_valid_note(Note("d")) == true);
  REQUIRE(scale.is_valid_note(Note("d#")) == false);
  REQUIRE(scale.is_valid_note(Note("e")) == true);
  REQUIRE(scale.is_valid_note(Note("f")) == true);
  REQUIRE(scale.is_valid_note(Note("f#")) == false);
  REQUIRE(scale.is_valid_note(Note("g")) == true);
  REQUIRE(scale.is_valid_note(Note("g#")) == false);
  REQUIRE(scale.is_valid_note(Note("a")) == true);
  REQUIRE(scale.is_valid_note(Note("a#")) == false);
  REQUIRE(scale.is_valid_note(Note("b")) == true);

  scale = SongReader::string_to_scale("\\key a \\minor");
  REQUIRE(scale.is_valid_note(Note("c")) == true);
  REQUIRE(scale.is_valid_note(Note("c#")) == false);
  REQUIRE(scale.is_valid_note(Note("d")) == true);
  REQUIRE(scale.is_valid_note(Note("d#")) == false);
  REQUIRE(scale.is_valid_note(Note("e")) == true);
  REQUIRE(scale.is_valid_note(Note("f")) == true);
  REQUIRE(scale.is_valid_note(Note("f#")) == false);
  REQUIRE(scale.is_valid_note(Note("g")) == true);
  REQUIRE(scale.is_valid_note(Note("g#")) == false);
  REQUIRE(scale.is_valid_note(Note("a")) == true);
  REQUIRE(scale.is_valid_note(Note("a#")) == false);
  REQUIRE(scale.is_valid_note(Note("b")) == true);

  scale = SongReader::string_to_scale("\\key f \\major");
  REQUIRE(scale.is_valid_note(Note("f")) == true);
  REQUIRE(scale.is_valid_note(Note("g")) == true);
  REQUIRE(scale.is_valid_note(Note("g#")) == false);
  REQUIRE(scale.is_valid_note(Note("a")) == true);
  REQUIRE(scale.is_valid_note(Note("a#")) == false);
  REQUIRE(scale.is_valid_note(Note("b\u266D")) == true);
  REQUIRE(scale.is_valid_note(Note("b")) == false);
  REQUIRE(scale.is_valid_note(Note("c")) == true);
  REQUIRE(scale.is_valid_note(Note("c#")) == false);
  REQUIRE(scale.is_valid_note(Note("d")) == true);
  REQUIRE(scale.is_valid_note(Note("d#")) == false);
  REQUIRE(scale.is_valid_note(Note("e")) == true);
  REQUIRE(scale.is_valid_note(Note("e#")) == false);

  scale = SongReader::string_to_scale("\\key g \\major");
  REQUIRE(scale.is_valid_note(Note("g")) == true);
  REQUIRE(scale.is_valid_note(Note("a")) == true);
  REQUIRE(scale.is_valid_note(Note("a#")) == false);
  REQUIRE(scale.is_valid_note(Note("b")) == true);
  REQUIRE(scale.is_valid_note(Note("b#")) == false);
  REQUIRE(scale.is_valid_note(Note("c")) == true);
  REQUIRE(scale.is_valid_note(Note("c#")) == false);
  REQUIRE(scale.is_valid_note(Note("d")) == true);
  REQUIRE(scale.is_valid_note(Note("d#")) == false);
  REQUIRE(scale.is_valid_note(Note("e")) == true);
  REQUIRE(scale.is_valid_note(Note("f")) == false);
  REQUIRE(scale.is_valid_note(Note("f#")) == true);
}

TEST_CASE("Song Reader can receive a string and return a compass time", "[single-file]"){
  CompassTime compass_time;
  compass_time = SongReader::string_to_compass_time("\\time 4/4");
  REQUIRE(compass_time.times == 4);
  REQUIRE(compass_time.base_note == 4);
  REQUIRE(compass_time.base_note_duration() == 8);
  REQUIRE(compass_time.compass_duration() == 32);

  compass_time = SongReader::string_to_compass_time("\\time 3/4");
  REQUIRE(compass_time.times == 3);
  REQUIRE(compass_time.base_note == 4);
  REQUIRE(compass_time.base_note_duration() == 8);
  REQUIRE(compass_time.compass_duration() == 24);

  compass_time = SongReader::string_to_compass_time("\\time 2/4");
  REQUIRE(compass_time.times == 2);
  REQUIRE(compass_time.base_note == 4);
  REQUIRE(compass_time.base_note_duration() == 8);
  REQUIRE(compass_time.compass_duration() == 16);

  compass_time = SongReader::string_to_compass_time("\\time 2/2");
  REQUIRE(compass_time.times == 2);
  REQUIRE(compass_time.base_note == 2);
  REQUIRE(compass_time.base_note_duration() == 16);
  REQUIRE(compass_time.compass_duration() == 32);


  compass_time = SongReader::string_to_compass_time("\\time 5/4");
  REQUIRE(compass_time.times == 5);
  REQUIRE(compass_time.base_note == 4);
  REQUIRE(compass_time.base_note_duration() == 8);
  REQUIRE(compass_time.compass_duration() == 40);

  compass_time = SongReader::string_to_compass_time("\\time 9/8");
  REQUIRE(compass_time.times == 9);
  REQUIRE(compass_time.base_note == 8);
  REQUIRE(compass_time.base_note_duration() == 4);
  REQUIRE(compass_time.compass_duration() == 36);
}
