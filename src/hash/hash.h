#ifndef HASH_H
#define HASH_H

#include <cstddef>
#include <string>
#include <vector>


class HashTable {
private:
    std::vector<std::vector<std::string>> buckets;
    std::size_t WordCount;

    std::size_t hashFunction(const std::string& word)const;
    void rehash();

public:
    HashTable();
    void insert(const std::string& word);
    bool search(const std::string& word)const;
    std::vector<std::string> prefixSearch(const std::string& prefix)const;

};


