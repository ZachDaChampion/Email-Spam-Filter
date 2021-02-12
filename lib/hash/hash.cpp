#include "hash.hpp"

const uint64_t FNV_OFFSET_BASIS_64 = 14695981039346656037U;
const uint64_t FNV_PRIME_64 = 1099511628211U;

namespace hash {
uint64_t fnv1a_64(std::string data) {
  uint64_t hash = FNV_OFFSET_BASIS_64;

  for (uint32_t i = 0; i < data.length(); ++i) {
    hash = hash ^ (data[i]);
    hash *= FNV_PRIME_64;
  }

  return hash;
}
}  // namespace hash