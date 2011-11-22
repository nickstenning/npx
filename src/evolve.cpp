#include <iostream>
#include <functional>
#include <cmath>

#include "random.h"

#include "nk/landscape.h"
#include "ga/population.h"
#include "ga/genome.h"
#include "ga/select.h"
#include "ga/vary.h"

using namespace std;

static ga::Population pop;

ga::Genome const& select (ga::Population const& p);
ga::Population::iterator select (ga::Population& p);

void print_stats_header (void);
void print_stats (int generation, ga::Population const& p);

int main (int argc, char const *argv[])
{
  unsigned int n, k;

  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " N K\n";
    return 1;
  }

  n = atoi(argv[1]);
  k = atoi(argv[2]);

  if (!(k < n)) {
    cerr << "K must be in the range [0, N)!\n";
    return 1;
  }

  nk::Landscape landscape(n, k);

  auto evaluate = bind(&nk::Landscape::evaluate, cref(landscape), placeholders::_1);

  {
    ga::Genome g(n);

    while(cin >> g) {
      g.fitness(evaluate(g));
      pop.push_back(g);
    };
  }

  // Now, we have initialized the population. Enter the GA.
  print_stats_header();
  int tick = 0;

  while (true) {
    // Print population statistics every "generation"
    if (tick % pop.size() == 0) {
      pop.compute_stats();
      print_stats(tick / pop.size(), pop);
    } else {
      pop.update_best_so_far(); // Mustn't miss any brilliance between "generations".
    }

    // Select a random member of the population
    ga::Population::iterator cand_it = ga::select_random(pop);
    // Select another random member of the population
    ga::Population::iterator other_it = ga::select_random(pop);

    // Mutate (and copy)
    ga::Genome cand = ga::mutate_single(*cand_it);

    // Crossover
    // cand = ga::crossover_binary_1point(cand, *select(pop));
    // cand = ga::crossover_binary_uniform(cand, *select(pop));
    cand = ga::crossover_nary_uniform_weighted(10, 0.5, pop, ga::select_random);

    // Update the individual with its new fitness
    cand.fitness(evaluate(cand));

    // Tournament with other
    if (cand.fitness() > other_it->fitness()) {
      *other_it = cand;
    }

    ++tick;
  }

  return 0;
}

void print_stats_header ()
{
  fprintf(stdout, "#%9s%10s%10s%10s%10s%10s\n", "gen", "min", "max", "mean", "stddev", "bsf");
  fflush(stdout);
}

void print_stats (int generation, ga::Population const& pop)
{
  ga::Population::Stats s = pop.stats();
  fprintf(stdout, "%10d%10.4g%10.4g%10.4g%10.4g%10.4g\n", generation, s.min, s.max, s.mean, s.sdev, s.best_so_far);
  fflush(stdout);
}

