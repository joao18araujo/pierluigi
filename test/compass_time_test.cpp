#include "catch.hpp"

#include "compass_time.h"
#include "note.h"

TEST_CASE("Compass time can return base note duration", "[single-file]"){
  CompassTime ct(4, 1);
  REQUIRE(ct.base_note_duration() == 32);

  ct = CompassTime(4, 2);
  REQUIRE(ct.base_note_duration() == 16);

  ct = CompassTime(4, 4);
  REQUIRE(ct.base_note_duration() == 8);

  ct = CompassTime(4, 8);
  REQUIRE(ct.base_note_duration() == 4);

  ct = CompassTime(4, 16);
  REQUIRE(ct.base_note_duration() == 2);

  ct = CompassTime(4, 32);
  REQUIRE(ct.base_note_duration() == 1);
}

TEST_CASE("Compass time can return compass duration", "[single-file]"){
  CompassTime ct;
  ct = CompassTime(4, 4);
  REQUIRE(ct.compass_duration() == 32);

  ct = CompassTime(3, 4);
  REQUIRE(ct.compass_duration() == 24);

  ct = CompassTime(2, 4);
  REQUIRE(ct.compass_duration() == 16);

  ct = CompassTime(2, 2);
  REQUIRE(ct.compass_duration() == 32);

  ct = CompassTime(5, 4);
  REQUIRE(ct.compass_duration() == 40);

  ct = CompassTime(9, 8);
  REQUIRE(ct.compass_duration() == 36);

}
