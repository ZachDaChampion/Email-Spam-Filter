#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "hash.hpp"

/**
 * @brief An entry to a hash table.
 * 
 * Implements a singly-linked list to handle hash collisions.
 * 
 * @tparam T The data type that is stored in the entry.
 */
template <typename T>
class HashEntry {
 private:
  std::string mIdentifier;
  T mData;

 public:
  std::unique_ptr<HashEntry<T>> mNext;  ///< The next entry in the linked list.

  /**
   * @brief Construct a new Hash Entry object.
   * 
   * @param identifier The identifier used to look up the stored data.
   * @param data The data that is stored in this entry.
   */
  HashEntry(std::string identifier, T data) : mIdentifier(identifier),
                                              mData(data),
                                              mNext(nullptr) {}

  /**
   * @brief Get the identifier of this entry.
   * 
   * @return The identifier of this entry.
   */
  std::string getIdentifier() { return mIdentifier; }

  /**
  * @brief Get the data stored in this entry.
  * 
  * @return The data stored in this entry.
  */
  T get() { return mData; }

  /**
   * @brief Search this and all subsequent entries for an identifier.
   * 
   * @param identifier The identifier to search for.
   * @return The data stored at the requested identifier, if it exists.
   */
  std::optional<T> search(std::string identifier) {
    if (this->mIdentifier == identifier) return this->get();
    if (this->mNext != nullptr) return this->mNext->search(identifier);
    return std::nullopt;
  }

  /**
   * @brief Set the value stored at an identifier in this or a subsequent entry.
   * 
   * Will search through this and all subsequent entries for the given identifier.
   * If it exists, the value will be updated.
   * If the idenifier is not found, a new entry will be created at the end of the linked list with the given identifier and data.
   * 
   * @param identifier The identifier of the data that is to be set.
   * @param data The data that is to be set.
   */
  void set(std::string identifier, T data) {
    if (this->mIdentifier == identifier) {
      this->mData = data;
    } else if (this->mNext != nullptr)
      this->mNext->set(identifier, data);
    else
      this->mNext = std::make_unique<HashEntry<T>>(identifier, data);
  }

  /**
   * @brief Add a new entry to the end of this linked list.
   * 
   * Creates a new entry at the end of the list with the given identifier and data.
   * 
   * @param identifier The identifier of the data that is to be added.
   * @param data The data that is to be added.
   * @return true if the entry is successfully created.
   * @return false if an entry with the given identifier already exists.
   */
  bool add(std::string identifier, T data) {
    if (this->mIdentifier == identifier) return false;
    if (this->mNext == nullptr) {
      this->mNext = std::make_unique<HashEntry<T>>(identifier, data);
      return true;
    }
    return this->mNext->add(identifier, data);
  }

  /**
   * @brief Removes the data stored at a given identifier in a subseqent entry.
   * 
   * Will completely delete the associated entry from the linked list.
   * Will NOT remove self, even if it has the correct identifier.
   * 
   * @param identifier The identifier of the data to be removed.
   * @return true if the data was successfully deleted.
   * @return false if the identifier could not be found.
   */
  bool remove(std::string identifier) {
    if (this->mNext == nullptr) return false;
    if (this->mNext->getIdentifier() == identifier) {
      std::unique_ptr tmp = std::move(this->mNext->mNext);
      this->mNext = std::move(tmp);
      return true;
    }
    return this->mNext->remove(identifier);
  }
};

/**
 * @brief An implementation of a hash table.
 * 
 * @tparam buckets How mant buckets are to be used in the table.
 * @tparam T The type of data to be stored in the table.
 */
template <uint64_t buckets, typename T>
class HashTable {
 private:
  std::function<uint64_t(std::string)> mHashFunc;
  std::unique_ptr<HashEntry<T>> mTable[buckets];

 public:
  /**
  * @brief Construct a new Hash Table<buckets,  T> object
  * 
  * @param hashFunc The hashing function to be used by this table.
  */
  HashTable<buckets, T>(std::function<uint64_t(std::string)> hashFunc = hash::fnv1a_64) : mHashFunc(hashFunc) {}

  /**
   * @brief Get the data stored at a given identifier.
   * 
   * @param identifier The identifier of the requested data.
   * @return The data stored at the given identifier, if it exists.
   */
  std::optional<T> get(std::string identifier) {
    uint64_t hash = this->mHashFunc(identifier) % buckets;
    return this->mTable[hash] != nullptr ? this->mTable[hash]->search(identifier) : std::nullopt;
  }

  /**
   * @brief Set the data stored at an identifier.
   * 
   * Will create a new table entry if one does not already exist.
   * If an entry with the given identifier already exists, its data will be replaced.
   * 
   * @param identifier The identifier of the data.
   * @param data The data to be stored.
   */
  void set(std::string identifier, T data) {
    uint64_t hash = this->mHashFunc(identifier) % buckets;
    if (this->mTable[hash] != nullptr)
      this->mTable[hash]->set(identifier, data);
    else
      this->mTable[hash] = std::make_unique<HashEntry<T>>(identifier, data);
  }

  /**
   * @brief Remove an entry from the table.
   * 
   * @param identifier The identifier of the data to be removed.
   * @return true if the entry was successfully removed.
   * @return false if the identifier does not exist in the table.
   */
  bool remove(std::string identifier) {
    uint64_t hash = this->mHashFunc(identifier) % buckets;
    if (this->mTable[hash] == nullptr) return false;
    if (this->mTable[hash]->getIdentifier() == identifier) {
      std::unique_ptr tmp = std::move(this->mTable[hash]->mNext);
      this->mTable[hash] = std::move(tmp);
      return true;
    }
    return this->mTable[hash]->remove(identifier);
  }
};