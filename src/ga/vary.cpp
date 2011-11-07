#include "vary.h"

#include "ga/genome.h"
#include "ga/population.h"
#include "random.h"

using namespace ga;

Genome ga::mutate_single(Genome const& g)
{
  Genome copy(g);
  // Flip a randomly chosen bit
  copy[util::random::rand_uint(copy.size() - 1)].flip();
  return copy;
}

Genome ga::mutate_uniform(Genome const& g)
{
  Genome copy(g);
  double threshold = 1.0 / g.size();
  for (Genome::size_type i = 0; i < g.size(); ++i) {
    if (util::random::random() < threshold) {
      copy[i].flip();
    }
  }
  return copy;
}

Genome ga::crossover_binary_1point(Genome const& a, Genome const& b)
{
  Genome copy(a);

  Genome::size_type pivot = util::random::rand_uint(copy.size() - 1);

  for (Genome::size_type i = 0; i < pivot; ++i) {
    copy[i] = b[i];
  }

  return copy;
}

// Population crossover_binary_npoint(unsigned int n, Genome const&, Genome const&);

Genome ga::crossover_binary_uniform(Genome const& a, Genome const& b)
{
  return ga::crossover_binary_uniform_weighted(0.5, a, b);
}

Genome ga::crossover_binary_uniform_weighted(double weight, Genome const& a, Genome const& b)
{
  Genome copy(a);

  for (Genome::size_type i = 0; i < copy.size(); ++i) {
    if (util::random::random() < weight) {
      copy[i] = b[i];
    }
  }

  return copy;
}


Genome ga::crossover_nary_uniform_weighted(unsigned int n_parents,
                                           double weight,
                                           Population const& pop,
                                           ga::_fp_genome_selector select)
{
  Population parents(n_parents);

  // Select parents
  for (unsigned int i = 0; i < n_parents; ++i) {
    parents[i] = select(pop);
  }

  // Create target genome from first parent
  Genome copy(parents[0]);

  for (Genome::size_type i = 0; i < copy.size(); ++i) {
    Genome* parent = NULL;

    for (unsigned int j = 0; j < n_parents; ++j) {
      if (util::random::random() < 1 - weight) {
        parent = &parents[j];
        break;
      }
    }

    // Fell off the end, so choose last parent
    // TODO: determine whether this is actually unfairly weighting the last parent
    if (parent == NULL) parent = &parents[n_parents - 1];

    // Copy ith bit from selected parent
    copy[i] = (*parent)[i];
  }

  return copy;
}
