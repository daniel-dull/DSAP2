#include <string>
#include <vector>
# ifndef TRIE_H
# define TRIE_H


struct Node{
	char letter = ''; // i think you need a place holder here?
	std::vector<Node*> next;
	bool isWord = false;
	Node(char letra): letter(letra) {}
};

class Trie{
	//Node* root = nullptr; idk if this is what it should be?

	Node* root = new Node;
public:
	bool insert(std::string word);
	std::string search(std::string input);

};


#endif