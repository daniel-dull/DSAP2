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
	void printAllWordsHelp(Node* root, string &output);
	vector<char> levelOrderHelp(Node* root);
public:
	// public member funcitons
	bool insert(string word);
	Node* search(string input);
	bool deleteWord(string input);
	void printAllWords();
	void printLevelOrder();
};
