#ifndef POPULATION_H
#define POPULATION_H

#include <cstdio>
#include <vector>

#include "genome.h"

namespace ga {
  class Population : public std::vector<Genome>
  {
  public:
    struct Stats {
      Stats()
      : mean(-1.0)
      , sdev(-1.0)
      , max(-1.0)
      , min(-1.0)
      , best_so_far(-1.0)
      {};
      double mean;
      double sdev;
      double max;
      double min;
      double best_so_far;
    };

    Population();
    Population(unsigned int n);

    Stats const& stats() const { return this->_stats; }
    void compute_stats();
    void update_best_so_far();

  private:
    Stats _stats;
  };
}

#endif // POPULATION_H
