#include <string>
#include <vector>
# ifndef TRIE_H
# define TRIE_H
using namespace std;


struct Node{
	char letter = '\0';
	vector<Node*> next;
	bool isWord = false;
	Node(){}
	Node(char letra): letter(letra) {}
};

class Trie{
	Node* root = new Node;
	int wordsToSuggest = 5;
	// private member functions
	void insertHelp(string word, Node* root);
	Node* searchHelp(string input);
	void DFSOrderHelp(Node* root, string &output,vector<string> &ret);
	vector<char> levelOrderHelp(Node* root);
	vector<string> FindNearestHelp(Node* root,string &input, int maxReturn);
public:
	// public member funcitons
	bool insert(string word);
	Node* search(string input);
	bool deleteWord(string input);
	vector<string> getDFSOrder();
	void getLevelOrder();
	vector<string> FindNearest(string input);
	void setMaxReturn(int input);
};


#endif
