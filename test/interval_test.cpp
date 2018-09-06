#include "catch.hpp"

#include "interval.h"
#include "note.h"

TEST_CASE("Interval can be created from two notes", "[single-file]"){
  Note first, second;
  Interval interval;
  SECTION("when is ascendant"){
    first = Note("c", "", 4);
    second = Note("g", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P5");
    REQUIRE(interval.ascendant == true);
  }

  SECTION("when is descendant"){
    first = Note("g", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P5");
    REQUIRE(interval.ascendant == false);
  }

  SECTION("when is unison"){
    first = Note("c", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P1");
    REQUIRE(interval.half_tones == 0);
  }

  SECTION("when is major or minor second"){
    first = Note("c", "", 4);
    second = Note("d", "\u266D", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "m2");
    REQUIRE(interval.half_tones == 1);
    REQUIRE(interval.ascendant == true);

    first = Note("d", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "M2");
    REQUIRE(interval.half_tones == 2);
    REQUIRE(interval.ascendant == false);
  }

  SECTION("when is major or minor third"){
    first = Note("c", "#", 4);
    second = Note("e", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "m3");
    REQUIRE(interval.half_tones == 3);
    REQUIRE(interval.ascendant == true);

    first = Note("e", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "M3");
    REQUIRE(interval.half_tones == 4);
    REQUIRE(interval.ascendant == false);
  }

  SECTION("when is perfect fourth"){
    first = Note("c", "", 4);
    second = Note("f", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P4");
    REQUIRE(interval.half_tones == 5);
  }

  SECTION("when is perfect fifth"){
    first = Note("c", "#", 4);
    second = Note("g", "#", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P5");
    REQUIRE(interval.half_tones == 7);
  }

  SECTION("when is major or minor sixth"){
    first = Note("c", "#", 4);
    second = Note("a", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "m6");
    REQUIRE(interval.half_tones == 8);
    REQUIRE(interval.ascendant == true);

    first = Note("a", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "M6");
    REQUIRE(interval.half_tones == 9);
    REQUIRE(interval.ascendant == false);
  }


  SECTION("when is major or minor seventh"){
    first = Note("c", "#", 4);
    second = Note("b", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "m7");
    REQUIRE(interval.half_tones == 10);
    REQUIRE(interval.ascendant == true);

    first = Note("b", "", 4);
    second = Note("c", "", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "M7");
    REQUIRE(interval.half_tones == 11);
    REQUIRE(interval.ascendant == false);
  }

  SECTION("when is octave"){
    first = Note("g", "", 4);
    second = Note("g", "", 5);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P8");
    REQUIRE(interval.half_tones == 12);
  }


  SECTION("when is compound"){
    first = Note("c", "", 4);
    second = Note("b", "", 5);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "M14");
    REQUIRE(interval.half_tones == 23);
    REQUIRE(interval.ascendant == true);

    first = Note("c", "", 4);
    second = Note("c", "", 6);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "P15");
    REQUIRE(interval.half_tones == 24);
    REQUIRE(interval.ascendant == true);
  }


  SECTION("when is augmented"){
    first = Note("c", "", 4);
    second = Note("f", "#", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "A4");
    REQUIRE(interval.half_tones == 6);
    REQUIRE(interval.ascendant == true);


    first = Note("c", "", 4);
    second = Note("c", "#", 5);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "A8");
    REQUIRE(interval.half_tones == 13);
    REQUIRE(interval.ascendant == true);
  }

  SECTION("when is diminished"){
    first = Note("c", "", 4);
    second = Note("f", "\u266D", 4);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "d4");
    REQUIRE(interval.half_tones == 4);
    REQUIRE(interval.ascendant == true);


    first = Note("c", "", 4);
    second = Note("c", "\u266D", 5);
    interval = Interval(first, second);
    REQUIRE(interval.description() == "d8");
    REQUIRE(interval.half_tones == 11);
    REQUIRE(interval.ascendant == true);
  }
}

TEST_CASE("Interval can be created from string and boolean", "[single-file]"){
  Interval interval;
  SECTION("when is ascendant"){
    interval = Interval("P4", true);
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 4);
    REQUIRE(interval.half_tones == 5);
    REQUIRE(interval.ascendant == true);
  }

  SECTION("when is descendant"){
    interval = Interval("3xA8", false);
    REQUIRE(interval.qualitative == "3xA");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 15);
    REQUIRE(interval.ascendant == false);
  }

  SECTION("when is unison"){
    interval = Interval("P1");
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 1);
    REQUIRE(interval.half_tones == 0);
    REQUIRE(interval.ascendant == true);
    REQUIRE(interval.is_consonant() == true);
  }

  SECTION("when is major or minor second"){
    interval = Interval("m2");
    REQUIRE(interval.qualitative == "m");
    REQUIRE(interval.quantitative == 2);
    REQUIRE(interval.half_tones == 1);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("M2");
    REQUIRE(interval.qualitative == "M");
    REQUIRE(interval.quantitative == 2);
    REQUIRE(interval.half_tones == 2);
    REQUIRE(interval.is_consonant() == false);
  }

  SECTION("when is major or minor third"){
    interval = Interval("m3");
    REQUIRE(interval.qualitative == "m");
    REQUIRE(interval.quantitative == 3);
    REQUIRE(interval.half_tones == 3);
    REQUIRE(interval.is_consonant() == true);

    interval = Interval("M3");
    REQUIRE(interval.qualitative == "M");
    REQUIRE(interval.quantitative == 3);
    REQUIRE(interval.half_tones == 4);
    REQUIRE(interval.is_consonant() == true);
  }

  SECTION("when is perfect fourth"){
    interval = Interval("P4");
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 4);
    REQUIRE(interval.half_tones == 5);
    REQUIRE(interval.ascendant == true);
    REQUIRE(interval.is_consonant() == false);
  }

  SECTION("when is perfect fifth"){
    interval = Interval("P5");
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 5);
    REQUIRE(interval.half_tones == 7);
    REQUIRE(interval.ascendant == true);
    REQUIRE(interval.is_consonant() == true);
  }

  SECTION("when is major or minor sixth"){
    interval = Interval("m6");
    REQUIRE(interval.qualitative == "m");
    REQUIRE(interval.quantitative == 6);
    REQUIRE(interval.half_tones == 8);
    REQUIRE(interval.is_consonant() == true);

    interval = Interval("M6");
    REQUIRE(interval.qualitative == "M");
    REQUIRE(interval.quantitative == 6);
    REQUIRE(interval.half_tones == 9);
    REQUIRE(interval.is_consonant() == true);
  }


  SECTION("when is major or minor seventh"){
    interval = Interval("m7");
    REQUIRE(interval.qualitative == "m");
    REQUIRE(interval.quantitative == 7);
    REQUIRE(interval.half_tones == 10);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("M7");
    REQUIRE(interval.qualitative == "M");
    REQUIRE(interval.quantitative == 7);
    REQUIRE(interval.half_tones == 11);
    REQUIRE(interval.is_consonant() == false);
  }

  SECTION("when is octave"){
    interval = Interval("P8");
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 12);
    REQUIRE(interval.is_consonant() == true);
  }


  SECTION("when is compound"){
    interval = Interval("P12");
    REQUIRE(interval.qualitative == "P");
    REQUIRE(interval.quantitative == 12);
    REQUIRE(interval.half_tones == 19);
    REQUIRE(interval.is_consonant() == true);

    interval = Interval("M14");
    REQUIRE(interval.qualitative == "M");
    REQUIRE(interval.quantitative == 14);
    REQUIRE(interval.half_tones == 23);
    REQUIRE(interval.is_consonant() == false);
  }


  SECTION("when is augmented"){
    interval = Interval("A4", false);
    REQUIRE(interval.qualitative == "A");
    REQUIRE(interval.quantitative == 4);
    REQUIRE(interval.half_tones == 6);
    REQUIRE(interval.ascendant == false);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("A5", false);
    REQUIRE(interval.qualitative == "A");
    REQUIRE(interval.quantitative == 5);
    REQUIRE(interval.half_tones == 8);
    REQUIRE(interval.ascendant == false);
    REQUIRE(interval.is_consonant() == true);

    interval = Interval("A8");
    REQUIRE(interval.qualitative == "A");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 13);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("3xA8");
    REQUIRE(interval.qualitative == "3xA");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 15);
    REQUIRE(interval.is_consonant() == true);
  }

  SECTION("when is diminished"){
    interval = Interval("d4", false);
    REQUIRE(interval.qualitative == "d");
    REQUIRE(interval.quantitative == 4);
    REQUIRE(interval.half_tones == 4);
    REQUIRE(interval.ascendant == false);
    REQUIRE(interval.is_consonant() == true);

    interval = Interval("d5", false);
    REQUIRE(interval.qualitative == "d");
    REQUIRE(interval.quantitative == 5);
    REQUIRE(interval.half_tones == 6);
    REQUIRE(interval.ascendant == false);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("d8");
    REQUIRE(interval.qualitative == "d");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 11);
    REQUIRE(interval.is_consonant() == false);

    interval = Interval("3xd8");
    REQUIRE(interval.qualitative == "3xd");
    REQUIRE(interval.quantitative == 8);
    REQUIRE(interval.half_tones == 9);
    REQUIRE(interval.is_consonant() == true);
  }
}

TEST_CASE("Interval class can return a note, given an interval and a note", "[single-file]"){
}
