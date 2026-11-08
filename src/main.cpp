#include <fstream>
#include <iostream>
#include <string>
#include "hash/hash.h"
#include "trie/trie.h"

using namespace std;


//Using the same input rules for both Trie and Hash structures
string normalizeWord(string word) {
    for (char& c : word) {
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c - 'A' + 'a');
        }

        if (!((c >= 'a' && c <= 'z') || c == '-' || c == '\'')) {
            return "";
        }
    }
    return word;
}

int main() {
    HashTable hash;
    Trie trie;

    trie.setMaxReturn(0);


    ifstream file("../assets/dictionary.txt");

    if (!file.is_open()) {
        cerr << "Could not open the dataset.\n";
        return 1;
    }


    string word;
    size_t accepted = 0;

    while (getline(file, word)) {
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }

        word = normalizeWord(word);

        if (word.empty()) {
            continue;
        }

        hash.insert(word);
        trie.insert(word);
        accepted++;
    }

    cout << "Loaded " << accepted << " accepted lines into both structures.\n";

    while (true) {
        cout << "\n1. Exact-word search\n"
             << "2. Prefix search\n"
             << "3. Exit\n"
             << "Choose: ";

        string choice;
        if (!getline(cin, choice) || choice == "3") {
            break;
        }

        if (choice != "1" && choice != "2") {
            cout << "Enter 1, 2, or 3.\n";
            continue;
        }

        cout << "Enter a word or prefix: ";

        string input;
        if (!getline(cin, input)) {
            break;
        }

        input = normalizeWord(input);

        if (input.empty()) {
            cout << "Enter letters, dashes, or apostrophes.\n";
            continue;
        }

        if (choice == "1") {
            bool hashFound = hash.search(input);

            Node* node = trie.search(input);
            bool trieFound = node != nullptr && node->isWord;

            cout << "Hash: "
                 << (hashFound ? "Found" : "Not found") << '\n';

            cout << "Trie: "
                 << (trieFound ? "Found" : "Not found") << '\n';
        } else {
            auto hashMatches = hash.prefixSearch(input);
            auto trieMatches = trie.FindNearest(input);

            cout << "\nHash: " << hashMatches.size() << " matches\n";

            for (size_t i = 0; i < hashMatches.size() && i < 5; i++) {
                cout << hashMatches[i] << '\n';
            }

            cout << "\nTrie: " << trieMatches.size() << " matches\n";

            for (size_t i = 0; i < trieMatches.size() && i < 5; i++) {
                cout << trieMatches[i] << '\n';
            }
        } // End the if/else
    } // End menu loop

    return 0;
} // Ends main
