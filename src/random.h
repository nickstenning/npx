#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <functional>
#include <stdint.h>

namespace util
{

/**
 * Container for random number generator utilities.
**/
namespace random
{
  class rng
  {
  public:
    rng();
    rng(uintmax_t seed);
    virtual ~rng() {};

    uintmax_t seed (uintmax_t seed);

    double random ();
    double uniform (double a, double b);

    uintmax_t rand_uint (uintmax_t max = UINTMAX_MAX);

    friend std::mt19937_64& get_engine ();

  private:
    std::mt19937_64 _engine;
    std::function<double()> _real_generator;
    std::function<uintmax_t()> _uint_generator;
  };

  void init ();

  double random ();
  double uniform (double a, double b);
  uintmax_t rand_uint (uintmax_t max = UINTMAX_MAX);

  std::mt19937_64& get_engine();
}

}

#endif // RANDOM_H
