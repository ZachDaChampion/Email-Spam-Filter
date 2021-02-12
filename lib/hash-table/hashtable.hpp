#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "hash.hpp"

template <typename T>
class HashEntry {
 private:
  std::string mIdentifier;
  T mData;

 public:
  std::unique_ptr<HashEntry<T>> mNext;
  HashEntry(std::string identifier, T data) : mIdentifier(identifier),
                                              mData(data),
                                              mNext(nullptr) {}

  std::string getIdentifier() { return mIdentifier; }

  T get() { return mData; }

  std::optional<T> search(std::string identifier) {
    if (this->mIdentifier == identifier) return this->get();
    if (this->mNext != nullptr) return this->mNext->search(identifier);
    return std::nullopt;
  }

  void set(std::string identifier, T data) {
    if (this->mIdentifier == identifier) {
      this->mData = data;
    } else if (this->mNext != nullptr)
      this->mNext->set(identifier, data);
    else
      this->mNext = std::make_unique<HashEntry<T>>(identifier, data);
  }

  bool add(std::string identifier, T data) {
    if (this->mIdentifier == identifier) return false;
    if (this->mNext == nullptr)
      this->mNext = std::make_unique<HashEntry<T>>(identifier, data);
    else
      this->mNext->add(identifier, data);
    return true;
  }

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

template <uint64_t buckets, typename T>
class HashTable {
 private:
  std::function<uint64_t(std::string)> mHashFunc;
  std::unique_ptr<HashEntry<T>> mTable[buckets];

 public:
  HashTable<buckets, T>(std::function<uint64_t(std::string)> hashFunc = hash::fnv1a_64) : mHashFunc(hashFunc) {}

  std::optional<T> get(std::string identifier) {
    uint64_t hash = this->mHashFunc(identifier) % buckets;
    return this->mTable[hash] != nullptr ? this->mTable[hash]->search(identifier) : std::nullopt;
  }

  void set(std::string identifier, T data) {
    uint64_t hash = this->mHashFunc(identifier) % buckets;
    if (this->mTable[hash] != nullptr)
      this->mTable[hash]->set(identifier, data);
    else
      this->mTable[hash] = std::make_unique<HashEntry<T>>(identifier, data);
  }

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