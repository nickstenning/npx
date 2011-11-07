#include <iostream>
#include <functional>
#include <cmath>

#include "random.h"

#include "nk/nk.h"
#include "ga/population.h"
#include "ga/genome.h"
#include "ga/vary.h"

using namespace std;

static ga::Population pop;
static ga::Genome const* best_so_far;

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
      print_stats(tick / pop.size(), pop);
    }

    // Select a random member of the population
    ga::Population::iterator cand_it = select(pop);
    // Select another random member of the population
    ga::Population::iterator other_it = select(pop);

    // Mutate (and copy)
    ga::Genome cand = ga::mutate_single(*cand_it);

    // Crossover
    // cand = ga::crossover_binary_1point(cand, *select(pop));
    // cand = ga::crossover_binary_uniform(cand, *select(pop));
    cand = ga::crossover_nary_uniform_weighted(5, 0.2, pop, select);

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

// Random selection
ga::Population::iterator select (ga::Population& p)
{
  ga::Population::iterator it = p.begin();
  unsigned int inc_num = util::random::rand_uint(pop.size() - 1);
  for (; inc_num > 0; --inc_num)
    ++it;
  return it;
}

ga::Genome const& select (ga::Population const& p)
{
  ga::Population::const_iterator it = p.cbegin();
  unsigned int inc_num = util::random::rand_uint(pop.size() - 1);
  for (; inc_num > 0; --inc_num)
    ++it;
  return *it;
}

void print_stats_header (void)
{
  printf("#%9s%10s%10s%10s%10s%10s", "gen", "min", "max", "mean", "stddev", "bsf");
  cout << endl;
}

void print_stats (int generation, ga::Population const& p)
{
  vector<double> scores(p.size());
  double sum = 0;
  double sumsq = 0;

  for (auto it = p.cbegin(); it != p.cend(); ++it) {
    double f = it->fitness();

    if (best_so_far == NULL || f > best_so_far->fitness()) {
      best_so_far = &(*it);
    }

    scores[it - p.cbegin()] = f;
    sum += f;
  }

  double min = *min_element(scores.begin(), scores.end());
  double max = *max_element(scores.begin(), scores.end());
  double mean = sum / scores.size();

  for (auto it = scores.cbegin(); it != scores.cend(); ++it) {
    sumsq += pow(*it - mean, 2);
  }

  double stddev = sqrt(sumsq / scores.size());

  printf("%10d%10.4g%10.4g%10.4g%10.4g%10.4g", generation, min, max, mean, stddev, best_so_far->fitness());
  cout << endl;
}
