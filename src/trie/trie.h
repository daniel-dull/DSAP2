struct Node{
	char letter = '';
	vector<Node*> next;
	bool isWord = false;
	Node(char letra): letter(letra) {}
};

class Trie{
	Node* root = new Node;
public:
	bool insert(string word);
	string search(string input);
	
	
	

};
