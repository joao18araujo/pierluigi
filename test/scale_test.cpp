#include "catch.hpp"

#include "scale.h"
#include "note.h"

TEST_CASE("Scale can be created from base note and mode", "[single-file]"){
  SECTION("when is major"){
    Note base_note = Note("c");
    Scale scale = Scale(base_note, "major");
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

    base_note = Note("f");
    scale = Scale(base_note, "major");
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

    base_note = Note("g");
    scale = Scale(base_note, "major");
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
}

TEST_CASE("Scale can be created from base note and intervals", "[single-file]"){
  Note base_note = Note("g");
  Interval M3 = Interval("M3");
  Interval M2 = Interval("M2");
  Interval m2 = Interval("m2");
  vector<Interval> intervals {M3, M2, m2, M3};
  Scale scale = Scale(base_note, intervals);
  REQUIRE(scale.is_valid_note(Note("g")) == true);
  REQUIRE(scale.is_valid_note(Note("b")) == true);
  REQUIRE(scale.is_valid_note(Note("c#")) == true);
  REQUIRE(scale.is_valid_note(Note("d")) == true);
  REQUIRE(scale.is_valid_note(Note("f#")) == true);
}

TEST_CASE("Scale class can return a note, given an interval, a note and a scale", "[single-file]"){
  Note base_note = Note("c");
  Note note = Note("e");
  Scale c_major = Scale(Note("c"), "major");
  Scale f_major = Scale(Note("f"), "major");
  Scale g_major = Scale(Note("g"), "major");
  Interval interval = Interval("P5");
  Interval augmented_interval = Interval("A5");
  Interval diminished_interval = Interval("d5");
  Note new_note = Scale::interval_to_note_on_scale(note, interval, c_major);
  REQUIRE(new_note.valid == true);
  REQUIRE(new_note.full_note() == "b");

  new_note = Scale::interval_to_note_on_scale(note, interval, f_major);
  REQUIRE(new_note.valid == false);

  new_note = Scale::interval_to_note_on_scale(note, diminished_interval, f_major);
  REQUIRE(new_note.valid == true);
  REQUIRE(new_note.full_note() == "b\u266D");

  new_note = Scale::interval_to_note_on_scale(note, interval, g_major);
  REQUIRE(new_note.valid == true);
  REQUIRE(new_note.full_note() == "b");

  new_note = Scale::interval_to_note_on_scale(note, augmented_interval, g_major);
  REQUIRE(new_note.valid == false);
}
