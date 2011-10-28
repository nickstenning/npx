#include <iostream>
#include <cmath>
#include <cstdlib>

#include "nk.h"

#include "ga/genome.h"
#include "random.h"

nk::Landscape::Landscape (unsigned int n, unsigned int k)
: _n(n)
, _k(k)
{}

nk::Landscape::~Landscape ()
{}

double nk::Landscape::evaluate (ga::Genome const& g)
{
  double total = 0;
  for (unsigned int i = 0; i < g.size(); ++i) {
    total += this->evaluate_position(i, g);
  }
  return total / g.size();
}

double nk::Landscape::evaluate_position(unsigned int i, ga::Genome const& g)
{
  // Seed the RNG with the id of this particular genome
  util::random::seed(g.id());

  // Re-seed the RNG with the next random number multiplied by i:
  util::random::seed(util::random::rand_uint() * i);

  unsigned int table_index = 0;

  // The neighbours are all taken from the immediate "right" of the
  // bit position i, with the jth neighbour contributing the jth
  // significant bit of the table_index.
  for (unsigned int j = 0; j < (this->_k + 1); ++j) {
    table_index = g[(i + j) % (g.size() - 1)] << j;
  }

  // // Discard all the random fitnesses up to table_index - 1
  // for (unsigned int j = 0; j < table_index; ++j) {
  //   util::random::random();
  // }

  util::random::seed(util::random::rand_uint() * table_index);

  return util::random::random(); // table[table_index]
}
