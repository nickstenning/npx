#ifndef VARY_H
#define VARY_H

#include "ga/genome.h"
#include "ga/population.h"

namespace ga {

  typedef Genome const& (*_fp_genome_selector)(Population const&);

  Genome mutate_single(Genome const&);
  Genome mutate_uniform(Genome const&);

  Genome crossover_binary_1point(Genome const&, Genome const&);
  // Genome crossover_binary_npoint(unsigned int n, Genome const&, Genome const&);
  Genome crossover_binary_uniform(Genome const&, Genome const&);
  Genome crossover_binary_uniform_weighted(double weight, Genome const&, Genome const&);

  Genome crossover_nary_uniform_weighted(unsigned int n_parents,
                                         double weight,
                                         Population const&,
                                         _fp_genome_selector);

}

#endif // VARY_H
