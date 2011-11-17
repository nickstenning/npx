#include "ga/population.h"
#include "random.h"

#include "select.h"

// Random selection
ga::Population::iterator ga::select_random (ga::Population& p)
{
  ga::Population::iterator it = p.begin();
  it += util::random::rand_uint(p.size() - 1);
  return it;
}

ga::Population::const_iterator ga::select_random (ga::Population const& p)
{
  ga::Population::const_iterator it = p.cbegin();
  it += util::random::rand_uint(p.size() - 1);
  return it;
}
