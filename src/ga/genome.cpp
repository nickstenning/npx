#include <boost/dynamic_bitset.hpp>

#include "genome.h"
#include "random.h"

ga::Genome::Genome (unsigned int size, unsigned long initializer)
: boost::dynamic_bitset<>(size, initializer)
, _id(util::random::rand_uint())
{}

ga::Genome::~Genome ()
{}
