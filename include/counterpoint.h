#ifndef COUNTERPOINT_H
#define COUNTERPOINT_H

#include "note.h"
#include "interval.h"
#include "scale.h"
#include "song.h"
#include <vector>
#include <cstring>
#include <algorithm>

using std::vector;
using std::random_shuffle;

class Counterpoint{
public:
  static bool dp[201][32][90][5][101];
  static Song * song;

  static vector<Note> generate_first_species_counterpoint(Song & song, bool ascendant);

  // static bool dp[201][32][90][5][101]; // [qtd_de_notas][posicao_da_nota_no_compasso][notas_do_piano][3as_6as_paralelas][movimentos_paralelos]

  static void analyse_and_add_interval(bool reverse_movement, bool melodic_ascendant, vector<Interval> & possible_intervals, Note previous_counterpoint_note, Note note, Interval interval, Song * counterpoint);

  static bool is_thesis(Note & note, int offset);
  // static vector<Note> dfs_generate_second_species_counterpoint(vector<Note> & song, bool ascendant, int paralels, int same_movements, Scale & scale);

  // static bool solve(unsigned position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale);
  // static bool solve_2(unsigned position, unsigned compass_position, int paralels, int same_movements, vector<Note> & song, vector<Note> & counterpoint, bool ascendant, Scale & scale);
  //
  // static bool is_thesis(unsigned compass_position);
};

#endif
