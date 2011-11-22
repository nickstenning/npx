#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <exception>
#include <vector>

#include "random.h"

namespace ga
{
  class Genome;
}

namespace nk
{

  class Landscape
  {
  public:
    class InvalidGenomeSize : public std::exception {
      virtual const char* what() const throw() { return "InvalidGenomeSize"; }
    };
    class InvalidPosition : public std::exception {
      virtual const char* what() const throw() { return "InvalidPosition"; }
    };

    Landscape (unsigned long id = util::random::rand_uint());
    Landscape (unsigned int n, unsigned int k, unsigned long id = util::random::rand_uint());
    virtual ~Landscape ();

    /** Evaluate fitness of genome `g`
     *
     * @return a float in [0,1]
    **/
    double evaluate(ga::Genome const& g) const throw(InvalidGenomeSize);

    /** Evaluate fitness of gene at position `i` in genome `g`
    **/
    double evaluate_position(unsigned int i, ga::Genome const& g) const throw(InvalidGenomeSize, InvalidPosition);

    unsigned long id() const { return this->_id; }

    Landscape& n(unsigned int n) { this->_n = n; return *this; }
    unsigned int n() const { return this->_n; }
    Landscape& k(unsigned int k) { this->_k = k; return *this; }
    unsigned int k() const { return this->_k; }

  private:
    unsigned int _n;
    unsigned int _k;

    unsigned long _id;
  };

} /* nk:: */

#endif // LANDSCAPE_H
