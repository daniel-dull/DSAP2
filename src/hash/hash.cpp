#include "hash.h"

using namespace std;

HashTable::HashTable() : buckets(16), WordCount(0) {

}

size_t HashTable::hashFunction (const string& word) const {
    hash<string> hasher;
    size_t hash_value = hasher (word);
    return hash_value;
}


bool HashTable::search (const string& word) const {
    //finish
    return 0;
}

void HashTable::insert(const string& word) {
    //finish
    return 0;
}


void HashTable::reHash() {
    return 0;
}

vector<string> HashTable::prefixSearch(const string& prefix) const {
    //finish
    return 0;
}
