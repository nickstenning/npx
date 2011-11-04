#include <cstdlib>
#include <random>
#include <cstdint>

#include "random.h"

static std::uniform_real_distribution<double> real_distribution;
static std::uniform_int_distribution<uintmax_t> uint_distribution(0, UINTMAX_MAX);

static util::random::rng global_rng;

util::random::rng::rng ()
: _engine()
, _real_generator(std::bind(real_distribution, std::ref(_engine)))
, _uint_generator(std::bind(uint_distribution, std::ref(_engine)))
{
  std::random_device dvc;
  uintmax_t seed = dvc();

  this->seed(seed);
}

util::random::rng::rng (uintmax_t seed)
: _engine()
, _real_generator(std::bind(real_distribution, std::ref(_engine)))
, _uint_generator(std::bind(uint_distribution, std::ref(_engine)))
{
  this->seed(seed);
}

uintmax_t util::random::rng::seed (uintmax_t seed)
{
  this->_engine.seed(seed);
  return seed;
}

double util::random::rng::random ()
{
  return this->_real_generator();
}

double util::random::rng::uniform (double a, double b)
{
  std::uniform_real_distribution<double> distribution(a, b);
  return distribution(this->_engine);
}

uintmax_t util::random::rng::rand_uint (uintmax_t max)
{
  if (max == UINTMAX_MAX) {
    return this->_uint_generator();
  } else {
    std::uniform_int_distribution<uintmax_t> distribution(0, max);
    return distribution(this->_engine);
  }
}

// Static global RNG

void util::random::init ()
{
  uintmax_t seed;
  char const* envSeed;

  envSeed = getenv("RNG_SEED");

  if (envSeed != NULL) {
    seed = strtoul(envSeed, NULL, 0);
    global_rng.seed(seed);
  }
}

double util::random::random ()
{
  return global_rng.random();
}

double util::random::uniform (double a, double b)
{
  return global_rng.uniform(a, b);
}

uintmax_t util::random::rand_uint (uintmax_t max)
{
  return global_rng.rand_uint(max);
}

std::mt19937_64& util::random::get_engine ()
{
  return global_rng._engine;
}
