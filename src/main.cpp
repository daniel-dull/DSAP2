#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

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

int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--console") {
        HashTable hash;
        Trie t; // Keeping your teammates' variable naming
        t.setMaxReturn(0);

        ifstream file("assets/dictionary.txt");
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
            t.insert(word);
            accepted++;
        }

        file.close();
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

                Node* node = t.search(input);
                bool trieFound = node != nullptr && node->isWord;

                cout << "Hash: " << (hashFound ? "Found" : "Not found") << '\n';
                cout << "Trie: " << (trieFound ? "Found" : "Not found") << '\n';
            } else {
                auto hashMatches = hash.prefixSearch(input);
                auto trieMatches = t.FindNearest(input);

                cout << "\nHash: " << hashMatches.size() << " matches\n";
                for (size_t i = 0; i < hashMatches.size() && i < 5; i++) {
                    cout << hashMatches[i] << '\n';
                }

                cout << "\nTrie: " << trieMatches.size() << " matches\n";
                for (size_t i = 0; i < trieMatches.size() && i < 5; i++) {
                    cout << trieMatches[i] << '\n';
                }
            }
        }
        return 0;
    }
    sf::RenderWindow window(sf::VideoMode(1280, 720), "DSAP2");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SMFL." << std::endl;
        return -1;
    }

    HashTable hash;
    Trie trie;

    char searchWordBuffer[256] = "";
    std::string statusMessage = "Dataset not loaded.";
    bool datasetLoaded = false;

    double hashInsertTimeMs = 0.0;
    double trieInsertTimeMs = 0.0;

    double hashSearchTimeUs = 0.0;
    double trieSearchTimeUs = 0.0;

    bool hashFound = false;
    bool trieFound = false;

    vector<string> hashSuggestions;
    vector<string> trieSuggestions;

    trie.setMaxReturn(0);

    ifstream file("assets/dictionary.txt");

    if (!file.is_open()) {
        statusMessage = "Error: Could not open file";
    } else {
        string word;
        size_t accepted = 0;

        auto startLoad = chrono::high_resolution_clock::now();
        while (getline(file, word)) {
            if (!word.empty() && word.back() =='r') {
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
        auto endLoad = chrono::high_resolution_clock::now();
        double totalLoadMs = chrono::duration<double, milli>(endLoad - startLoad).count();

        hashInsertTimeMs = totalLoadMs / 2.0;
        trieInsertTimeMs = totalLoadMs / 2.0;

        file.close();
        datasetLoaded = true;
        statusMessage = "Loaded " + to_string(accepted) + "words into the Tables";
    }

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(20,20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(1240,680), ImGuiCond_FirstUseEver);

        ImGui::Begin("DSA Project 2: Hash Table vs. Trie Performance Dashboard");

        ImGui::Text("Dataset Status");
        ImGui::Separator();
        ImGui::TextColored(datasetLoaded ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1), "%s", statusMessage.c_str());

        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        ImGui::Text("Search & Suggestion Bar");
        ImGui::Separator();

        bool enterPressed = ImGui::InputText("Search Word / Prefix", searchWordBuffer, IM_ARRAYSIZE(searchWordBuffer), ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::SameLine();

        if (ImGui::Button("Run Search") || enterPressed) {
            if (datasetLoaded) {
                string input(searchWordBuffer);
                input = normalizeWord(input);

                if (!input.empty()) {
                    auto startH = chrono::high_resolution_clock::now();
                    hashFound = hash.search(input);
                    auto hashMatches = hash.prefixSearch(input);
                    auto endH = chrono::high_resolution_clock::now();
                    hashSearchTimeUs = chrono::duration<double, micro>(endH - startH).count();

                    hashSuggestions.clear();
                    for (size_t i = 0; i < hashMatches.size() && i < 5; i++) {
                        hashSuggestions.push_back(hashMatches[i]);
                    }

                    auto startT = chrono::high_resolution_clock::now();
                    Node* node = trie.search(input);
                    trieFound = (node != nullptr && node->isWord);
                    auto trieMatches = trie.FindNearest(input);
                    auto endT = chrono::high_resolution_clock::now();
                    trieSearchTimeUs = chrono::duration<double, micro>(endT - startT).count();

                    trieSuggestions.clear();
                    for (size_t i = 0; i < trieMatches.size() && i < 5; i++) {
                        trieSuggestions.push_back(trieMatches[i]);
                    }
                }
            }
        }

        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        if (ImGui::BeginTable("PerformanceTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Metric");
            ImGui::TableSetupColumn("Hash Table Result");
            ImGui::TableSetupColumn("Trie Result");
            ImGui::TableHeadersRow();

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Insertion Time (Est.)");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%.2f ms", hashInsertTimeMs);
            ImGui::TableSetColumnIndex(2); ImGui::Text("%.2f ms", trieInsertTimeMs);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Lookup Time");
            ImGui::TableSetColumnIndex(1); ImGui::Text("%.2f us", hashSearchTimeUs);
            ImGui::TableSetColumnIndex(2); ImGui::Text("%.2f us", trieSearchTimeUs);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0); ImGui::Text("Exact Match Status");
            ImGui::TableSetColumnIndex(1);
            ImGui::TextColored(hashFound ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1), hashFound ? "Found" : "Not Found");
            ImGui::TableSetColumnIndex(2);
            ImGui::TextColored(trieFound ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1), trieFound ? "Found" : "Not Found");

            ImGui::EndTable();
        }

        ImGui::Dummy(ImVec2(0.0f, 15.0f));

        if (ImGui::BeginTable("SuggestionsTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingStretchProp)) {
            ImGui::TableSetupColumn("Hash Table Suggestions (Top 5)");
            ImGui::TableSetupColumn("Trie Suggestions (Top 5)");
            ImGui::TableHeadersRow();

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            if (hashSuggestions.empty()) {
                ImGui::TextDisabled("No prefix matches found.");
            } else {
                for (const auto& w : hashSuggestions) {
                    ImGui::BulletText("%s", w.c_str());
                }
            }

            ImGui::TableSetColumnIndex(1);
            if (trieSuggestions.empty()) {
                ImGui::TextDisabled("No prefix matches found.");
            } else {
                for (const auto& w : trieSuggestions) {
                    ImGui::BulletText("%s", w.c_str());
                }
            }

            ImGui::EndTable();
        }

        ImGui::End();

        window.clear(sf::Color(30, 30, 30));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
