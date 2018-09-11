#include "catch.hpp"

#include "first_species_counterpoint.h"
#include "ly_parser.h"

TEST_CASE("First Species Counterpoint returns a counterpoint with only consonant intervals", "[single-file]"){
    Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
    Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
    Interval interval;

    REQUIRE(song.size() == counterpoint.size());
    int size = song.size();
    for(int i = 0; i < size; ++i){
      interval = Interval(song.notes[i], counterpoint.notes[i]);
      REQUIRE(interval.ascendant_or_unison() == true);
      REQUIRE(interval.is_consonant() == true);
    }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that starts and ends on perfect consonants", "[single-file]"){
  Song counterpoint;
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Interval interval;

  SECTION("not having fifth if is descendant"){
    counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, false, 4, song.size());

    REQUIRE(song.size() == counterpoint.size());
    interval = Interval(song.notes.back(), counterpoint.notes.back());
    REQUIRE(interval.qualitative == "P");
    bool is_unison_or_octave = interval.quantitative == 1 || interval.quantitative == 8;
    REQUIRE(is_unison_or_octave == true);

    interval = Interval(song.notes.back(), counterpoint.notes.back());
    REQUIRE(interval.qualitative == "P");
    is_unison_or_octave = interval.quantitative == 1 || interval.quantitative == 8;
    REQUIRE(is_unison_or_octave == true);
  }

  SECTION("having fifth if is ascendant"){
    counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());

    REQUIRE(song.size() == counterpoint.size());
    interval = Interval(song.notes.back(), counterpoint.notes.back());
    REQUIRE(interval.qualitative == "P");
    bool is_unison_or_octave_or_fifth = interval.quantitative == 1 || interval.quantitative == 8 || interval.quantitative == 5;
    REQUIRE(is_unison_or_octave_or_fifth == true);

    interval = Interval(song.notes.back(), counterpoint.notes.back());
    REQUIRE(interval.qualitative == "P");
    is_unison_or_octave_or_fifth = interval.quantitative == 1 || interval.quantitative == 8 || interval.quantitative == 5;
    REQUIRE(is_unison_or_octave_or_fifth == true);
  }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that only has unison at the beggining or the end", "[single-file]"){
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Interval interval;
  Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
  int size = counterpoint.size();
  for(int i = 1; i < size - 1; ++i){
    interval = Interval(song.notes[i], counterpoint.notes[i]);
    REQUIRE(interval.description() != "P1");
  }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that doesn't have paralels fifths or octaves", "[single-file]"){
    Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
    Interval interval, previous_interval;
    Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
    int size = counterpoint.size();
    previous_interval = Interval(song.notes[0], counterpoint.notes[0]);
    for(int i = 1; i < size; ++i){
      interval = Interval(song.notes[i], counterpoint.notes[i]);
      if(interval == "P5" or interval == "P8"){
        REQUIRE(previous_interval.description() != interval.description());
      }
      previous_interval = interval;
    }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that only have no more than 11th as intervals", "[single-file]"){
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
  Interval interval;

  REQUIRE(song.size() == counterpoint.size());
  int size = song.size();
  for(int i = 0; i < size; ++i){
    interval = Interval(song.notes[i], counterpoint.notes[i]);
    REQUIRE(interval.quantitative <= 11);
  }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that only have no more than four consecutive paralels 3th or 6th", "[single-file]"){
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Interval interval, previous_interval;
  Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
  int size = counterpoint.size(), paralels = 0;
  previous_interval = Interval(song.notes[0], counterpoint.notes[0]);
  for(int i = 1; i < size; ++i){
    interval = Interval(song.notes[i], counterpoint.notes[i]);

    bool is_paralel = (interval.quantitative == previous_interval.quantitative and (interval.quantitative == 3 || interval.quantitative == 6 || interval.quantitative == 10));
    paralels = is_paralel ? paralels + 1 : 0;
    REQUIRE(paralels <= 4);

    previous_interval = interval;
  }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that don't have leaps bigger than a 4th, unless it's an octave or reverse movement", "[single-file]"){
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Interval interval, cantus_firmus_interval;
  Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size());
  int size = counterpoint.size();
  for(int i = 1; i < size; ++i){
    cantus_firmus_interval = Interval(song.notes[i - 1], song.notes[i]);
    interval = Interval(counterpoint.notes[i - 1], counterpoint.notes[i]);
    if(interval != "P8" && interval.direction == cantus_firmus_interval.direction)
      REQUIRE(interval.quantitative <= 4);
  }
}

TEST_CASE("First Species Counterpoint returns a counterpoint that prioritizes reverse movement", "[single-file]"){
  Song song = LyParser::read_file("res/twinkle_twinkle_only_notes.ly", false);
  Interval interval, cantus_firmus_interval;
  Song counterpoint = FirstSpeciesCounterpoint::dfs_generate_counterpoint(song, true, 4, song.size() / 2);
  int size = counterpoint.size();
  int same_movements = 0;
  for(int i = 1; i < size; ++i){
    cantus_firmus_interval = Interval(song.notes[i - 1], song.notes[i]);
    interval = Interval(counterpoint.notes[i - 1], counterpoint.notes[i]);
    same_movements += (interval.direction == cantus_firmus_interval.direction);
  }
  REQUIRE(same_movements <= size / 2);
}
