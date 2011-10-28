#ifndef GENOME_H
#define GENOME_H

#include <boost/dynamic_bitset.hpp>

namespace ga {
  class Genome : public boost::dynamic_bitset<>
  {
  public:
    Genome (unsigned int size, unsigned long initializer);
    virtual ~Genome ();

    unsigned long id() const { return this->_id; }

  private:
    unsigned long _id;
  };
}

#endif // GENOME_H
