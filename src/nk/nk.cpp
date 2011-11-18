#include <iostream>
#include <cmath>
#include <cstdlib>

#include <boost/functional/hash/hash.hpp>

#include "nk.h"

#include "ga/genome.h"
#include "random.h"

nk::Landscape::Landscape (unsigned int n, unsigned int k, unsigned long id)
: _n(n)
, _k(k)
, _id(id)
{}

nk::Landscape::Landscape (unsigned long id)
: _n(0)
, _k(0)
, _id(id)
{}

nk::Landscape::~Landscape ()
{}

double nk::Landscape::evaluate (ga::Genome const& g) const throw(InvalidGenomeSize)
{
  // Throw if genome size != N
  if (g.size() != this->_n) throw nk::Landscape::InvalidGenomeSize();

  // Short-circuit if N == 0
  if (g.size() == 0) return 0.0;

  double total = 0;
  for (unsigned int i = 0; i < g.size(); ++i) {
    total += this->evaluate_position(i, g);
  }
  return total / g.size();
}

double nk::Landscape::evaluate_position (unsigned int i, ga::Genome const& g) const throw(InvalidGenomeSize, InvalidPosition)
{
  // Throw if genome size != N
  if (g.size() != this->_n) throw nk::Landscape::InvalidGenomeSize();

  // Throw if invalid position
  if (i >= g.size()) throw nk::Landscape::InvalidPosition();

  std::size_t seed = this->_id ^ i;

  // The neighbours are all taken from the immediate "right" of the
  // bit position i. So, with K = 2, the hash is updated with the values
  // at i, i + 1, i + 2.
  //
  // If we overrun the end of the genome, we wrap to the beginning.
  for (unsigned int j = 0; j < (this->_k + 1); ++j) {
    if (g[(i + j) % g.size()]) {
      boost::hash_combine(seed, 0x17A3C0E09F8EA2BDUL);
    } else {
      boost::hash_combine(seed, 0xF26C7F23511450FAUL);
    }
  }

  util::random::rng rng(seed);
  double x = rng.random();
  return x;
}
