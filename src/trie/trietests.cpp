#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include "trie.h"
using namespace std;

// main.cpp handles input validation. trie.cpp does not, so these tests will fail
// if input validation is tested for. 

//void sortV(vector<string> &veccy){
//	sort(veccy.begin(),veccy.end());
//}

TEST_CASE("Empty trie is empty"){
	Trie trie;
	REQUIRE_FALSE(trie.search("a"));
	vector<string> thing = trie.getDFSOrder();
	REQUIRE(thing.empty());
}

TEST_CASE("FUNCTION TESTS"){
	// these just ensure the functions actually work as expected. 
	// edge cases not tested.
	Trie trie;
	
	REQUIRE(trie.insert("apple"));
	REQUIRE(trie.insert("banana"));

	SECTION("Search tests"){
		REQUIRE(trie.search("apple"));
		REQUIRE(trie.search("banana"));
		REQUIRE(trie.search("app"));
		REQUIRE_FALSE(trie.search("orange"));
	}
	
	SECTION("Delete word test"){
		bool confirm = trie.deleteWord("apple");
		REQUIRE(confirm);
		REQUIRE_FALSE(trie.search("apple")->isWord);
	}
	
	SECTION("DFS order test"){
		vector<string> wholeTree = trie.getDFSOrder();
		sort(wholeTree.begin(),wholeTree.end());
		REQUIRE(wholeTree.at(0) == "apple");
		REQUIRE(wholeTree.at(1) == "banana");
	}
	
	SECTION("Level Order Test"){
		vector<vector<char>> actual = trie.getLevelOrder();
		vector<vector<char>> expected = {{0},{'a','b'},{'p','a'},{'p','n'},{'l','a'},{'e','n'},{'a'}};
		REQUIRE(expected == actual);
	}
	
	SECTION("Find Nearest test"){
		vector<string> expected = {"apple"};
		vector<string> actual = trie.FindNearest("app");
		
		REQUIRE(expected == actual);
	}
}

TEST_CASE("Duplicate words stored only one time") {
    Trie trie;
    trie.insert("corner");
    trie.insert("corner");

    vector<string> expected = {"corner"};
    vector<string> actual = trie.FindNearest("cor");
    vector<vector<char>> allCharsExp = {{0},{'c'},{'o'},{'r'},{'n'},{'e'},{'r'}};
    vector<vector<char>> allCharsAct = trie.getLevelOrder();
	REQUIRE(actual == expected);
	REQUIRE(allCharsExp == allCharsAct);
}

TEST_CASE("RANDOM TESTS"){
	// tests insertion of 100 random words made from capital letters, 
	// tests if the trie is built as expected.
	Trie trie;
	trie.setMaxReturn(0);
	
	random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> chars(65,90); // distribution in range [65, 90]
	uniform_int_distribution<std::mt19937::result_type> length(1,100);
	
	vector<string> expectedWords;
	
	for(int i = 0;i<100;i++){
		int wordLength = length(rng);
		string randomWord;
		for(int j = 0; j<wordLength;j++){
			randomWord += chars(rng);
		}
		expectedWords.push_back(randomWord);
		trie.insert(randomWord);
	}
	
	vector<string> actualBFS = trie.FindNearest("-1");
	vector<string> actualDFS = trie.getDFSOrder();
	
	sort(actualBFS.begin(),actualBFS.end());
	sort(actualDFS.begin(),actualDFS.end());
	sort(expectedWords.begin(),expectedWords.end());
	
	REQUIRE(actualBFS == actualDFS);
	REQUIRE(actualBFS == expectedWords);
	REQUIRE(actualDFS == expectedWords);
}
