#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

namespace util
{

/**
 * Container for random number generator utilities.
**/
namespace random
{

  uintmax_t init ();
  uintmax_t seed (uintmax_t seed);

  double random ();
  double uniform (double a, double b);

  uintmax_t rand_uint (uintmax_t max = UINTMAX_MAX);

  bool choose (double prob = 0.5);
}

}

#endif // RANDOM_H
