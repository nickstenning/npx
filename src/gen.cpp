#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "random.h"

using namespace std;
namespace rng = util::random;

uintmax_t gen (uintmax_t);

int main (int argc, char const *argv[])
{
  int num, len;

  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " N L\n";
    return 1;
  }

  num = atoi(argv[1]);
  len = atoi(argv[2]);

  rng::init();

  for(int i = 0; i < num; ++i) {
    for(int j = 0; j < len; ++j) {
      cout << rng::rand_uint(1);
    }
    cout << endl;
  }

  return 0;
}

