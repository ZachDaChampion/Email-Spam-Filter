#include <optional>
#include <string>

#include "catch.hpp"
#include "hashtable.hpp"

TEST_CASE("Hash table") {
  HashTable<0xfff, std::string> table;

  SECTION("Empty entries") {
    REQUIRE(table.get("test0").value_or("EMPTY") == "EMPTY");
    REQUIRE(table.get("test1").value_or("EMPTY") == "EMPTY");
    REQUIRE(table.get("").value_or("EMPTY") == "EMPTY");
  }

  SECTION("Entries can be set") {
    table.set("test0", "hello, world");
    REQUIRE(table.get("test0").value_or("EMPTY") == "hello, world");
    REQUIRE(table.get("test1").value_or("EMPTY") == "EMPTY");

    table.set("test1", "goodbye, world");
    REQUIRE(table.get("test0").value_or("EMPTY") == "hello, world");
    REQUIRE(table.get("test1").value_or("EMPTY") == "goodbye, world");
  }

  SECTION("Entries can be overwritten") {
    table.set("test0", "hello, world");
    table.set("test1", "goodbye, world");

    table.set("test0", "hello, earth");
    REQUIRE(table.get("test0").value_or("EMPTY") == "hello, earth");
    REQUIRE(table.get("test1").value_or("EMPTY") == "goodbye, world");

    table.set("test1", "goodbye, earth");
    REQUIRE(table.get("test0").value_or("EMPTY") == "hello, earth");
    REQUIRE(table.get("test1").value_or("EMPTY") == "goodbye, earth");
  }

  SECTION("Entries can be deleted") {
    table.set("test0", "hello, earth");
    table.set("test1", "goodbye, earth");

    REQUIRE(table.remove("test1") == true);
    REQUIRE(table.get("test0").value_or("EMPTY") == "hello, earth");
    REQUIRE(table.get("test1").value_or("EMPTY") == "EMPTY");

    REQUIRE(table.remove("test0") == true);
    REQUIRE(table.get("test0").value_or("EMPTY") == "EMPTY");
    REQUIRE(table.get("test1").value_or("EMPTY") == "EMPTY");

    REQUIRE(table.remove("test0") == false);
    REQUIRE(table.remove("test1") == false);
  }

  SECTION("Binning") {
    HashTable<10, std::string> tableMod10(hash::mod10);

    SECTION("Empty entries") {
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "EMPTY");
    }

    SECTION("Retrieve binned entries") {
      tableMod10.set("a", "this is a");
      tableMod10.set("b", "this is b");
      tableMod10.set("k", "this is k");
      tableMod10.set("u", "this is u");
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "this is k");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");
    }

    SECTION("Overwrite binned entries") {
      tableMod10.set("a", "this is a");
      tableMod10.set("b", "this is b");
      tableMod10.set("k", "this is k");
      tableMod10.set("u", "this is u");

      tableMod10.set("a", "this is a but better");
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a but better");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "this is k");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");

      tableMod10.set("b", "this is b but better");
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a but better");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b but better");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "this is k");

      tableMod10.set("k", "this is k but better");
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a but better");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b but better");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "this is k but better");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");

      tableMod10.set("u", "this is u but better");
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a but better");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b but better");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "this is k but better");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u but better");
    }

    SECTION("Delete binned entries") {
      tableMod10.set("a", "this is a");
      tableMod10.set("b", "this is b");
      tableMod10.set("k", "this is k");
      tableMod10.set("u", "this is u");

      REQUIRE(tableMod10.remove("k") == true);
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "this is b");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");

      REQUIRE(tableMod10.remove("b") == true);
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "this is a");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");

      REQUIRE(tableMod10.remove("a") == true);
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "this is u");

      REQUIRE(tableMod10.remove("u") == true);
      REQUIRE(tableMod10.get("a").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("b").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("k").value_or("EMPTY") == "EMPTY");
      REQUIRE(tableMod10.get("u").value_or("EMPTY") == "EMPTY");
    }
  }

  SECTION("Collision between multiple hash tables") {
    HashTable<0xfff, std::string> coolerTable;

    SECTION("Empty entries") {
      REQUIRE(table.get("ta").value_or("EMPTY") == "EMPTY");
      REQUIRE(table.get("tb").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "EMPTY");
    }

    SECTION("Collision when adding") {
      table.set("ta", "original table");
      REQUIRE(table.get("ta").value_or("EMPTY") == "original table");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "EMPTY");

      coolerTable.set("ta", "cooler table");
      REQUIRE(table.get("ta").value_or("EMPTY") == "original table");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "cooler table");

      coolerTable.set("tb", "cooler table again");
      REQUIRE(table.get("tb").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "cooler table again");

      table.set("tb", "original table again");
      REQUIRE(table.get("tb").value_or("EMPTY") == "original table again");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "cooler table again");
    }

    SECTION("Collision when overwriting") {
      table.set("ta", "original table");
      coolerTable.set("ta", "cooler table");
      table.set("tb", "original table again");
      coolerTable.set("tb", "cooler table again");

      table.set("ta", "o table");
      REQUIRE(table.get("ta").value_or("EMPTY") == "o table");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "cooler table");

      coolerTable.set("ta", "c table");
      REQUIRE(table.get("ta").value_or("EMPTY") == "o table");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "c table");

      coolerTable.set("tb", "c table again");
      REQUIRE(table.get("tb").value_or("EMPTY") == "original table again");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "c table again");

      table.set("tb", "o table again");
      REQUIRE(table.get("tb").value_or("EMPTY") == "o table again");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "c table again");
    }

    SECTION("Collision when deleting") {
      table.set("ta", "o table");
      coolerTable.set("ta", "c table");
      table.set("tb", "o table again");
      coolerTable.set("tb", "c table again");

      REQUIRE(table.remove("ta") == true);
      REQUIRE(table.get("ta").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "c table");

      REQUIRE(coolerTable.remove("tb") == true);
      REQUIRE(table.get("tb").value_or("EMPTY") == "o table again");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "EMPTY");

      REQUIRE(coolerTable.remove("ta") == true);
      REQUIRE(table.get("ta").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("ta").value_or("EMPTY") == "EMPTY");

      REQUIRE(table.remove("tb") == true);
      REQUIRE(table.get("tb").value_or("EMPTY") == "EMPTY");
      REQUIRE(coolerTable.get("tb").value_or("EMPTY") == "EMPTY");
    }
  }
}