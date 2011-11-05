#include <iostream>
#include <string>
#include <cstdlib>
#include <numeric>

#include "nk/nk.h"
#include "ga/genome.h"
#include "random.h"

class stream_statistics
{
public:
  stream_statistics() : _n(0) {}

  void clear() { _n = 0; }

  void push(double x)
  {
    ++_n;

    // See Knuth TAOCP vol 2, 3rd edition, page 232
    if (_n == 1) {
        _old_mean = _new_mean = x;
        _old_sdev = 0.0;
    } else{
      _new_mean = _old_mean + (x - _old_mean)/_n;
      _new_sdev = _old_sdev + (x - _old_mean)*(x - _new_mean);

      _old_mean = _new_mean; 
      _old_sdev = _new_sdev;
    }
  }

  int n() const { return _n; }

  double mean() const
  {
    return (_n > 0) ? _new_mean : 0.0;
  }

  double var() const
  {
    return (_n > 1) ? _new_sdev/(_n - 1) : 0.0;
  }

  double sdev() const
  {
    return sqrt(this->var());
  }

private:
  int _n;
  double _old_mean, _new_mean;
  double _old_sdev, _new_sdev;
};


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

  // Generate a random NK landscape
  nk::Landscape landscape(n, k);

  stream_statistics ss;

  ga::Genome g(n);
  
  while (std::cin >> g) {
    // Print fitness of genome
    double orig_fitness = landscape.evaluate(g);

    // Print fitness of each single-bit-flip neighbour of genome
    for (unsigned int i = 0; i < g.size(); ++i) {
      g[i].flip();
      double flip_fitness = landscape.evaluate(g);
      g[i].flip(); // Flip back

      if (flip_fitness > orig_fitness) {
        ss.push(flip_fitness - orig_fitness);
      } else {
        ss.push(orig_fitness - flip_fitness);
      }

    }
  }



  double e_maxk = 1.0 / n;
  double e_mink = 0.33 / n;
  std::cout << "# E(K = N - 1) = " << e_maxk << std::endl;
  std::cout << "# E(K = 0) = " << e_mink << std::endl;

  double interp_point = (ss.mean() - e_mink) / (e_maxk - e_mink);

  // Upper and lower bounds. Could also do this properly with a bayesian model...
  interp_point = std::min(interp_point, 1.0);
  interp_point = std::max(interp_point, 0.0);
  std::cout << "# Mean delta-fitness: " << ss.mean() << std::endl;
  std::cout << "# Estimated K: " << (n - 1) * interp_point << std::endl;



  return 0;
}
        
