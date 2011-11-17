#ifndef SELECT_H
#define SELECT_H

#include "ga/population.h"

namespace ga {
  Population::iterator       select_random(ga::Population& p);
  Population::const_iterator select_random(ga::Population const& p);
}

#endif // SELECT_H
