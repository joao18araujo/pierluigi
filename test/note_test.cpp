#include "catch.hpp"

#include "../include/note.h"

TEST_CASE( "Note is valid", "[single-file]" ) {

	Note note;
    REQUIRE( note.valid != true );
}
