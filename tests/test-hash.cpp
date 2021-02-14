#include "catch.hpp"
#include "hash.hpp"

TEST_CASE("Test FNV-1A against known hashes") {
  REQUIRE(hash::fnv1a_64("hello, world") == 0x17a1a4f267be633d);
  REQUIRE(hash::fnv1a_64("this is test") == 0x61901d0a123174a5);
  REQUIRE(hash::fnv1a_64("qwerty") == 0x3eb459c7c3501ff9);
  REQUIRE(hash::fnv1a_64("QWERTY") == 0x7b7546808ed0ff79);
  REQUIRE(hash::fnv1a_64("a") == 0xaf63dc4c8601ec8c);
}

TEST_CASE("Test mod10 against known hashes") {
  REQUIRE(hash::mod10("a") == 7);
  REQUIRE(hash::mod10("b") == 8);
  REQUIRE(hash::mod10("k") == 7);
  REQUIRE(hash::mod10("abacus") == 3);
  REQUIRE(hash::mod10("") == 0);
}
