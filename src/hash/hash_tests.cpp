#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include "hash.h"

using namespace std;

TEST_CASE("Empty table returns no matches") {
    HashTable table;

    REQUIRE_FALSE(table.search("avaricious"));
    REQUIRE(table.prefixSearch("avar").empty());
}

TEST_CASE("Inserted words can be found") {
    HashTable table;
    table.insert("apple");
    table.insert("banana");

    REQUIRE(table.search("apple"));
    REQUIRE(table.search("banana"));
    REQUIRE_FALSE(table.search("orange"));
    REQUIRE_FALSE(table.search("app"));
}

TEST_CASE("Duplicate words stored only one time") {
    HashTable table;
    table.insert("corner");
    table.insert("corner");

    vector<string> expected = {"corner"};
REQUIRE(table.prefixSearch("cor") == expected);}

TEST_CASE("Colliding words remain searchable") {
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

TEST_CASE("Prefix search returns exactly the matching words") {
    HashTable table;
    table.insert("cat");
    table.insert("catch");
    table.insert("caterpillar");
    table.insert("dog");

    vector<string> matches = table.prefixSearch("cat");
    sort(matches.begin(), matches.end());

    vector<string> expected = {"cat", "catch", "caterpillar"};

    REQUIRE(matches == expected);
    REQUIRE(table.prefixSearch("xyz").empty());
    REQUIRE(table.prefixSearch("caterpillars").empty());
}

TEST_CASE("Empty prefix returns all stored words") {
    HashTable table;
    table.insert("corner");
    table.insert("dog");

    vector<string> matches = table.prefixSearch("");
    sort(matches.begin(), matches.end());

    vector<string> expected = {"corner", "dog"};

    REQUIRE(matches == expected);
}

TEST_CASE("Search and prefix search are case-sensitive") {
    HashTable table;
    table.insert("Cat");

    REQUIRE(table.search("Cat"));
    REQUIRE_FALSE(table.search("cat"));
    REQUIRE_FALSE(table.search("CAT"));

    vector<string> expected = {"Cat"};

    REQUIRE(table.prefixSearch("Ca") == expected);
    REQUIRE(table.prefixSearch("ca").empty());
}
