#include <iostream>

#include "random.h"

#include "nk/landscape.h"
#include "ga/population.h"
#include "ga/genome.h"
#include "ga/select.h"
#include "ga/vary.h"

using namespace std;
namespace rng = util::random;

// Create empty populations vector
static vector<ga::Population> populations;

// Typedef for fitness function
// typedef double (*_fp_evaluator)(ga::Genome const&);
typedef std::function<double (ga::Genome const&)> _fp_evaluator;

void setup_populations(unsigned int num);
void load_genomes(unsigned int pop_size, unsigned int n);

void ga_init(_fp_evaluator);
void ga_tick(_fp_evaluator, unsigned int);

void print_stats (int generation);

int main (int argc, char const *argv[])
{
  unsigned int num_pops, num_gens, pop_size, n, k;

  if (argc != 6) {
    cerr << "Usage: " << argv[0] << " num_pops num_gens pop_size N K\n";
    return 1;
  }

  num_pops = atoi(argv[1]);
  num_gens = atoi(argv[2]);
  pop_size = atoi(argv[3]);
  n        = atoi(argv[4]);
  k        = atoi(argv[5]);

  // Make the landscape
  nk::Landscape landscape(n, k);
  // Fitness function
  auto evaluate = bind(&nk::Landscape::evaluate, cref(landscape), placeholders::_1);

  setup_populations(num_pops);
  load_genomes(pop_size, n);

  cerr << "Loaded " << pop_size * num_pops << " " << n << "-bit genomes..." << endl;

  ga_init(evaluate);

  // print_stats_header();
  unsigned int tick = 0;

  while (tick < pop_size * num_gens) {
    ga_tick(evaluate, tick);

    // Each generation, print stats
    if (tick % pop_size == 0) {
      print_stats(tick / pop_size);
    }

    ++tick;
  }
}

void setup_populations (unsigned int num)
{
  for (unsigned int i = 0; i < num; ++i) {
    ga::Population p;
    populations.push_back(p);
  }
}

void load_genomes (unsigned int pop_size, unsigned int n)
{
  ga::Genome g(n);
  for (auto it = populations.begin(); it != populations.end(); ++it) {
    for (unsigned int i = 0; i < pop_size; ++i) {
      cin >> g;
      it->push_back(g);
    }
  }
}

void ga_init (_fp_evaluator evaluate)
{
  for (auto pit = populations.begin(); pit != populations.end(); ++pit) {
    for (auto git = pit->begin(); git != pit->end(); ++git) {
      git->fitness(evaluate(*git));
    }
  }
}

void ga_tick (_fp_evaluator evaluate, unsigned int tick)
{
  for (auto pit = populations.begin(); pit != populations.end(); ++pit) {
    if (tick % pit->size() == 0) {
      pit->compute_stats();
    } else {
      pit->update_best_so_far(); // Mustn't miss any brilliance between "generations".
    }

    // Select a random member of the population
    ga::Population::iterator cand_it = ga::select_random(*pit);
    // Select another random member of the population
    ga::Population::iterator other_it = ga::select_random(*pit);

    // Mutate (and copy)
    ga::Genome cand = ga::mutate_single(*cand_it);

    // Crossover
    // cand = ga::crossover_binary_1point(cand, *ga::select_random(*pit));
    cand = ga::crossover_binary_uniform_weighted(0.2, cand, *ga::select_random(*pit));
    // cand = ga::crossover_nary_uniform_weighted(10, 0.5, *pit, ga::select_random);

    // Update the individual with its new fitness
    cand.fitness(evaluate(cand));

    // Tournament with other
    if (cand.fitness() > other_it->fitness()) {
      *other_it = cand;
    }
  }
}

void print_stats (int)
{
  // fprintf(stdout, "%10d", generation);
  for (auto it = populations.begin(); it != populations.end(); ++it) {
    fprintf(stdout, "%10.4g", it->stats().best_so_far);
  }
  fprintf(stdout, "\n");
  fflush(stdout);
}
