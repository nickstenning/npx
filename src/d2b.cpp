#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

void printb (unsigned long ul, unsigned int num_bits);

int main (int argc, char const *argv[])
{
  unsigned int n;

  if (argc == 2) {
    n = std::atoi(argv[1]);
  } else {
    n = 8 * sizeof(unsigned long);
  }

  unsigned long ul;
  std::string line;
  while(std::getline(std::cin, line)) {
    ul = std::strtoul(line.c_str(), NULL, 0);
    printb(ul, n);
    std::cout << std::endl;
  };

  return 0;
}

void printb (unsigned long ul, unsigned int num_bits)
{
  for (int pos = num_bits - 1; pos >= 0; --pos) {
    unsigned long cmp = pow(2, pos); // Can't use lshift for > 32 bits.
    if (cmp & ul) {
      std::cout << '1';
    } else {
      std::cout << '0';
    }
  }
}
