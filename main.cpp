#include <iomanip>
#include <iostream>

#include "lib/hash/hash.hpp"

int main(int, char **) {
  std::cout << std::hex << (hash::fnv1a_64("hello, world")) << std::endl;
}
