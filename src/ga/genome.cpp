#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "genome.h"
#include "random.h"


ga::Genome::Genome ()
: _bitset()
, _fitness(0.0)
{}

ga::Genome::Genome (unsigned int size, unsigned long initializer)
: _bitset(size, initializer)
, _fitness(0.0)
{}

ga::Genome::Genome (ga::Genome::storage_type const& s)
: _bitset(s)
, _fitness(0.0)
{}

ga::Genome::~Genome ()
{}

// <iostream> print and load helpers
std::ostream& operator<< (std::ostream& os, ga::Genome const& g) { return os << g._bitset; }
std::istream& operator>> (std::istream& is, ga::Genome& g) { return is >> g._bitset; }
