#include "hash.h"

using namespace std;

HashTable::HashTable() : buckets(16), WordCount(0) {

}

size_t HashTable::hashFunction (const string& word) const {
    size_t hash_value = 0;
    for (unsigned char c : word) {
        hash_value = hash_value * 31 + c;
    }
    return hash_value % buckets.size();
}


bool HashTable::search (const string& word) const {
    size_t index = hashFunction(word);

    for (const string& storedWord : buckets[index]) {
        if (storedWord == word) {
            return true;
        }
    }
    return false;
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
