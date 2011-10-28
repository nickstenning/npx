#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <functional>
#include <stdint.h>

#include "random.h"

static std::uniform_real_distribution<double> real_distribution;
static std::uniform_int_distribution<uintmax_t> uint_distribution(0, UINTMAX_MAX);

static std::mt19937_64 engine; // Mersenne twister MT19937
static auto real_generator = std::bind(real_distribution, std::ref(engine));
static auto uint_generator = std::bind(uint_distribution, std::ref(engine));

uintmax_t util::random::init ()
{
  uintmax_t seed;
  char const* envSeed;

  envSeed = getenv("RNG_SEED");

  if (envSeed != NULL) {
    seed = strtoul(envSeed, NULL, 0);
  } else {
    seed = std::time(0);
  }

  std::cerr << "RNG_SEED=" << seed << "\n";

  return util::random::seed(seed);
}

uintmax_t util::random::seed (uintmax_t seed)
{
  engine.seed(seed);
  return seed;
}

double util::random::random ()
{
  return real_generator();
}

double util::random::uniform (double a, double b)
{
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(engine);
}

bool util::random::choose (double prob)
{
  return (util::random::random() < prob);
}

uintmax_t util::random::rand_uint (uintmax_t max)
{
  if (max == UINTMAX_MAX) {
    return uint_generator();
  } else {
    std::uniform_int_distribution<uintmax_t> distribution(0, max);
    return distribution(engine);
  }
}
