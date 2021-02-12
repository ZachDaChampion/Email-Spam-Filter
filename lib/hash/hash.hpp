#pragma once

#include <cstdint>
#include <string>

namespace hash {

/**
 * @brief An implementation of the 64-bit FNV-1a hash function.
 * 
 * The Fowler-Noll-Vo hash function is simple and efficient algorithm that distributes hashes evenly.
 * For more information, see https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
 * 
 * @param data The data, in string form, that is to be hashed.
 * 
 * @return A 64-bit unsigned integer that represents the hash of the data.
 */
uint64_t fnv1a_64(std::string data);
}  // namespace hash