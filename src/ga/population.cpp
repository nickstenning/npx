#include <cmath>

#include "population.h"

ga::Population::Population()
: std::vector<Genome>()
, _stats()
{}

ga::Population::Population(unsigned int n)
: std::vector<Genome>(n)
, _stats()
{}

void ga::Population::compute_stats ()
{
  vector<double> scores(this->size());
  double sum = 0;
  double sumsq = 0;

  for (auto it = this->cbegin(); it != this->cend(); ++it) {
    double f = it->fitness();

    scores[it - this->cbegin()] = f;
    sum += f;
  }

  this->_stats.min = *min_element(scores.begin(), scores.end());
  this->_stats.max = *max_element(scores.begin(), scores.end());
  this->_stats.mean = sum / scores.size();

  for (auto it = scores.cbegin(); it != scores.cend(); ++it) {
    sumsq += pow(*it - this->_stats.mean, 2);
  }

  this->_stats.sdev = sqrt(sumsq / scores.size());

  this->update_best_so_far(); // Yes, this makes it O(2N), but what's a factor of two between friends?
}

void ga::Population::update_best_so_far ()
{
  for (auto it = this->cbegin(); it != this->cend(); ++it) {
    double f = it->fitness();

    if (f > this->_stats.best_so_far) {
      this->_stats.best_so_far = f;
    }
  }
}
