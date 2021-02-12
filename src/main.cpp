#include <iomanip>
#include <iostream>

#include "hashtable.hpp"

int main(int, char **) {
  HashTable<10, int> table(hash::mod10);

  table.set("test", 20);
  table.set("b", 2);
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  table.set("b", 3);
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  std::cout << "Removed b?\t" << table.remove("b") << std::endl;
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  std::cout << "Removed test?\t" << table.remove("test") << std::endl;
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  std::cout << "Removed test?\t" << table.remove("test") << std::endl;
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  table.set("b", 4);
  std::cout << "test\t" << hash::mod10("test") << "\t" << (table.get("test").value_or(-1)) << std::endl;
  std::cout << "b\t" << hash::mod10("b") << "\t" << (table.get("b").value_or(-1)) << std::endl;
  std::cout << std::endl;

  std::cout << std::hex << (hash::fnv1a_64("hello, world")) << std::endl;
}
