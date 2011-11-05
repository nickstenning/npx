#ifndef NK_H
#define NK_H

#include <vector>

namespace ga
{
  class Genome;
}

namespace nk
{

  class Landscape
  {
  public:
    Landscape (unsigned int n, unsigned int k);
    virtual ~Landscape ();

    /** Evaluate fitness of genome `g`
     *
     * @return a float in [0,1]
    **/
    double evaluate(ga::Genome const& g) const;

    /** Evaluate fitness of gene at position `i` in genome `g`
    **/
    double evaluate_position(unsigned int i, ga::Genome const& g) const;

    unsigned long id() const { return this->_id; }

  private:
    unsigned int _n;
    unsigned int _k;

    unsigned long _id;
  };

} /* nk:: */

#endif // NK_H
