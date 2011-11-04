#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "nk/nk.h"
#include "ga/population.h"
#include "ga/genome.h"
#include "random.h"

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
  ga::Population population;
  ga::Genome g(n);

  while(std::cin >> g) {
    population.push_back(g);
  }

  for (auto i = population.cbegin(); i < population.cend(); ++i) {
    std::cout << landscape.evaluate(*i) << std::endl;
  }

  return 0;
}
