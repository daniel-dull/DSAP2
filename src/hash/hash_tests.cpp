#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include "hash.h"

using namespace std;

Test_Case ("Empty table returns no matches") {
    HashTable table;

    REQUIRE_FALSE(table.search("avaricious"));
    REQUIRE(table.prefixSearch("avar").empty());
}

Test_Case("Inserted words can be found") {
    HashTable table;
    table.insert("apple");
    table.insert("banana");

    REQUIRE(table.search("apple"));
    REQUIRE(table.search("banana"));
    REQUIRE_FALSE(table.search("orange"));
    REQUIRE_FALSE(table.search("app"));
}

Test_Case("Duplicate words stored only one time") {
    HashTable table;
    table.insert("corner");
    table.insert("corner");

    vector<string> expected = {"corner"};
    REQUIRE(table.search prefixSearch("cor") == expected);
}

Test_Case("Colliding words remain searchable") {
    HashTable table;

    table.insert("a");
    table.insert("q");
    REQUIRE(table.search("a"));
    REQUIRE(table.search("q"));

    REQUIRE_FALSE(table.search("A"));
}

TEST_CASE("Words remain searchable after resizing") {
    HashTable table;

    for (int i = 0; i < 100; i++) {
        table.insert("word" + to_string(i));
    }
    for (int i = 0; i < 100; i++) {
        REQUIRE(table.search("word" + to_string(i)));
    }

    REQUIRE_FALSE(table.search("word100"));
    REQUIRE(table.prefixSearch("word").size() == 100);
}

