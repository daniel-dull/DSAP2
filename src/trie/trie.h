struct Node{
	char letter = '\0';
	vector<Node*> next;
	bool isWord = false;
	Node(){}
	Node(char letra): letter(letra) {}
};

class Trie{
	Node* root = new Node;
	
	void insertHelp(string word, Node* root);
	Node* searchHelp(string input);
public:
	bool insert(string word);
	Node* search(string input);
};
