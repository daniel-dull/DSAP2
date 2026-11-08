#include <string>
#include <vector>
#include <queue>
#include "trie.h"
using namespace std;


// ###########################################################################
//                                  STATIC HELPERS
// ###########################################################################


// takes a string input, checks if its all letters, dashes, or apostraphes,
// then converts it all to lowercase.
//string validate(string word){ 
//	for(auto i : word){ // O(n) n= word.size(). can regexs improve this? prolly not, I think regexs can help with finding if it doesn't match a pattern but not for converting characters.
//		if( !( (i > 64 && i < 91) || (i > 96 && i < 123) || (i == 45) || (i == 49) ) ) //if char is not upper case letter and not lowercase letter and not - and not ' then return false
//			return "";
//		else
//			i = tolower(i); // else convert to lower 
//	}
//	return word;
//}

// takes a node and a string, searches node's children for match to string's
// first char, returns child node if found else returns null. 
Node* searchChildren(string input,Node* root){
	for(auto i : root->next){
		if(i->letter == input.at(0))
			return i;
	}
	return nullptr;
}

// ###########################################################################
//                                   INSERT 
// ###########################################################################
void Trie::insertHelp(string word, Node* root){
	// finds node whose stored character matches first letter in input.
	Node* pulse = searchChildren(word,root);
	
	// if no node matches first letter of stored character, create one 
	// in node's children vector and store the reference to it (c++ 17+ only).
	if(!pulse)
		pulse = root->next.emplace_back(new Node(word.at(0)));
		
	// delete a character. if the string is now empty, that means pulse is 
	// the end of the word, so mark it as such. 
	// if string is not empty, recursive call with the shorter string 
	// and pulse as root. pulse should always exist here. 
	word.erase(0,1);
	if(word.empty())
		pulse->isWord = true;
	else
		insertHelp(word,pulse);
}

bool Trie::insert(string word){
//	word = validate(word);
	if(word.empty())
		return false;
	insertHelp(word, this->root);
	return true;
}

// ###########################################################################
//                                    SEARCH
// ###########################################################################

Node* Trie::searchHelp(string input, Node* root){
	
	// finds child node whose stored character matches first letter in input.
	Node* pulse = searchChildren(input, root);
	
	// erase first character in input. if the input is now empty or if pulse 
	// is null, return pulse. whether pulse node is a 
	// word or not doesn't matter. 
	// ex: search cat. ca found, but t is not found; return nullptr 
	// else, recursive call with shortened word and next node as root.
	input.erase(0,1);
	if(input.empty() || !pulse)
		return pulse;
	else
		return searchHelp(input,pulse);
}

Node* Trie::search(string input){
//	input = validate(input);
	if(input.empty())
		return nullptr;
	return searchHelp(input, this->root);
}

// ###########################################################################
//                                 DELETE WORD
// ###########################################################################

// just unmarks a word as a valid word. 
bool Trie::deleteWord(string input){
	Node* word = search(input);
	if (!word)
		return false;
	if (word->isWord){
		word->isWord = false;
		return true;
	}
	return false;
}

// ###########################################################################
//                            GET ALL WORDS DFS ORDER
// ###########################################################################

// gathers all words in trie into a vector. 
// idea here is that each node appends a letter to a string, printing the
// string if the current node is marked as a word, before going to each of 
// the node's children and doing the same, then removing the letter it added. 
// this is essentially a recursion DFS, printing words along the way.
void Trie::DFSOrderHelp(Node* root, string &output, vector<string> &ret){
	// if the node's letter is not a null terminator
	// (should only apply to the root), then append it to the output string.
	if(root->letter != '\0')
		output += root->letter;
	// if the node is a word, push everything in output to vector 
	if(root->isWord)
		ret.push_back(output);
	// if there are children, recursively call this function on all children. 
	if(!root->next.empty()){
		for(auto i : root->next)
			DFSOrderHelp(i,output,ret);
	}
	// remove the last letter. 
	output.pop_back();
	return;
}

// front end. just called the helper pretty much but loads the 
// string to be printed. returns vector of words to be printed instead of 
// printing them automatically for testing sake.
vector<string> Trie::getDFSOrder(){
	string output = "";
	vector<string> ret;
	DFSOrderHelp(this->root,output,ret);
	return ret;
}

// ###########################################################################
//                               GET LEVEL ORDER
// ###########################################################################

// does level order stuff, returns a vector of vectors, should be
// the tree's keys in level order. level order not guaranteed to be sorted.
// i will not elaborate on how this works.
vector<vector<char>> Trie::levelOrderHelp(Node* root){
	if(!root)
		return {};
	vector<vector<char>> result;
	queue<Node*> q;
	q.push(root);
	int level = 0;
	
	while(!q.empty()){
		int count = q.size();
		result.push_back({});
		
		for(int i = 0;i<count;i++){
			result[level].push_back(q.front()->letter);
			for(auto i : q.front()->next)
				q.push(i);
			q.pop();
		}
		level++;
	}
	return result;
}

vector<vector<char>> Trie::getLevelOrder(){
	return levelOrderHelp(this->root);
//	int level = 0;
//	for(auto i : result){
//		cout << "LEVEL: " << level << "\n\t";
//		for(auto j : i){
//			if(j != '\0')
//				cout << j;
//		}
//	}

}
	
// ###########################################################################
//                               FIND NEAREST WORDS
// ###########################################################################

// does a breadth first search to find the nearest n words.
// n default == 5, can be adjusted. q pairs nodes to running string along that
// branch. will return all words BFS order if maxReturn <= 0.
vector<string> Trie::FindNearestHelp(Node* root,string input, int maxReturn){
	if(!root)
		return {};
	queue<pair<Node*,string>> q;
	q.push({root,input});
	vector<string> ret;
	while(!q.empty()){ 
		if(q.front().first->isWord)
			ret.push_back(q.front().second);
		if(maxReturn > 0)
			if(ret.size() == maxReturn)
				return ret;
		for(auto i : q.front().first->next){
			string temp = q.front().second;
			temp += i->letter;
			q.push({i,temp});
		}
		q.pop();
	}
	return ret;
}

vector<string> Trie::FindNearest(string input){
//	input = validate(input);
	if(input.empty())
		return {};
	return FindNearestHelp(search(input),input,this->wordsToSuggest);
}

// ###########################################################################
//                              ADJUST MAX RETURN
// ###########################################################################

void Trie::setMaxReturn(int input){
	this->wordsToSuggest = input;
}










