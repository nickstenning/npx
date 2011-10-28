#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdint.h>

#include "random.h"

uintmax_t gen (uintmax_t);

int main (int argc, char const *argv[])
{
  int num, len, max;
  uintmax_t upper;

  max = 8 * sizeof(uintmax_t);

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " N L\n";
    return 1;
  }

  num = atoi(argv[1]);
  len = atoi(argv[2]);

  if (len > max) {
    std::cerr << "L > 8 * sizeof(uintmax_t): death, destruction, etc. Aborting.\n";
    return 1;
  }
  util::random::init();

  if (len == max) {
    upper = 0;
  } else {
    upper = 1;
    upper <<= len;
  }
  --upper;

  for(int i = 0; i < num; ++i) {
    std::cout << util::random::rand_uint(upper) << std::endl;
  }

  return 0;
}

