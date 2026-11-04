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
    if (search(word)) {
        return;
    }
    size_t index = hashFunction(word);
    buckets[index].push_back(word);
    WordCount++;

    float loadFactor = (float)WordCount / buckets.size();

    if (loadFactor > 0.75) {
        reHash();
    }
}


void HashTable::reHash() {
    vector<vector<string>> oldBuckets;
    oldBuckets.swap(buckets);

    buckets.resize(oldBuckets.size()*2);

    for (const auto& bucket : oldBuckets) {
        for (const string& word : bucket) {
            size_t index = hashFunction(word);
            buckets[index].push_back(word);
        }
    }
}

vector<string> HashTable::prefixSearch(const string& prefix) const {
    vector<string> matches;

    for (const auto& bucket : buckets) {
        for (const string& word : bucket) {
            if (word.compare(0, prefix.size(), prefix) == 0) {
                matches.push_back(word);
            }
        }
    }
    return matches;
}
