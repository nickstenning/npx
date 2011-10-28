#include <iostream>
#include <string>
#include <cstdlib>

#include "nk/nk.h"
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

  // Read one genome from stdin
  unsigned long ul;
  std::string line;
  if (!std::getline(std::cin, line)) {
    return 1;
  }
  ul = std::strtoul(line.c_str(), NULL, 0);
  ga::Genome g(n, ul);

  // Generate a random NK landscape
  nk::Landscape landscape(n, k);

  // Print fitness of genome
  std::cout << landscape.evaluate(g) << std::endl;

  // Print fitness of each single-bit-flip neighbour of genome
  for (unsigned int i = 0; i < g.size(); ++i) {
    g[i].flip();
    std::cout << landscape.evaluate(g) << std::endl;
    g[i].flip(); // Flip back
  }

  return 0;
}
