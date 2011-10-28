#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "nk/nk.h"
#include "ga/population.h"
#include "ga/genome.h"
#include "random.h"

ga::Population population_from_stream(std::istream& is, unsigned int n);

int main (int argc, char const *argv[])
{
  unsigned int n, k;

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " N K\n";
    return 1;
  }

  n = std::atoi(argv[1]);
  k = std::atoi(argv[2]);

  if (!(k < n)) {
    std::cerr << "K must be in the range [0, N)!\n";
    return 1;
  }

  util::random::init();

  nk::Landscape landscape(n, k);
  ga::Population population = population_from_stream(std::cin, n);


  for (unsigned int i = 0; i < population.size(); ++i) {
    std::cout << landscape.evaluate(population[i]) << std::endl;
  }

  return 0;
}

ga::Population population_from_stream(std::istream& is, unsigned int n)
{
  ga::Population pop;

  unsigned long ul;
  std::string line;
  while(std::getline(is, line)) {
    ul = std::strtoul(line.c_str(), NULL, 0);
    ga::Genome g(n, ul);
    pop.push_back(g);
  };

  return pop;
}

