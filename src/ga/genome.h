#ifndef GENOME_H
#define GENOME_H

#include <string>
#include <iostream>

#include <boost/dynamic_bitset.hpp>

#include "ga/evolvable.h"

namespace ga {
  class Genome;
}

std::ostream& operator<< (std::ostream& os, ga::Genome const& g);
std::istream& operator>> (std::istream& is, ga::Genome& g);

namespace ga {
  class Genome : public Evolvable
  {
  public:
    typedef boost::dynamic_bitset<> storage_type;
    typedef storage_type::size_type size_type;
    typedef storage_type::reference reference;

    Genome ();
    Genome (unsigned int size, unsigned long initializer = 0);
    Genome (storage_type const& copy);

    virtual ~Genome ();

    double fitness() const { return this->_fitness; }
    Genome& fitness(double f) { this->_fitness = f; return *this; }

    // Delegations to storage_type methods
    size_type size() const { return this->_bitset.size(); }

    reference operator[](size_type pos) { return this->_bitset[pos]; }
    bool operator[](size_type pos) const { return this->_bitset[pos]; }

    friend std::ostream& (::operator<<) (std::ostream& os, Genome const& g);
    friend std::istream& (::operator>>) (std::istream& is, Genome& g);

  private:
    storage_type _bitset;
    double _fitness;
  };

}

#endif // GENOME_H
