// ###########################################################################
//                                  STATIC HELPERS
// ###########################################################################


// takes a string input, checks if its all letters, dashes, or apostraphes,
// then converts it all to lowercase.
string validate(string word){ 
	for(auto i : word){ // O(n) n= word.size(). can regexs improve this? prolly not, I think regexs can help with finding if it doesn't match a pattern but not for converting characters.
		if( !( (i > 64 && i < 91) || (i > 96 && i < 123) || (i == 45) || (i == 49) ) ) //if char is not upper case letter and not lowercase letter and not - and not ' then return false
			return "";
		else
			i = tolower(i); // else convert to lower 
	}
	return word;
}

// takes a node and a string, searches node's children for match to string's
// first char, returns child node if found else returns null. 
Node* searchChildren(string input,Node* root){
	for(auto i : root->next){
		if(i->letter == input.at(0))
			return i
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
		pulse = root->next.emplace_back(new Node(word.at(0));
		
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
	word = validate(word);
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
	// is null. whether pulse node is a word or not doesn't matter. 
	// ex: search cat. ca found, but t is not found; return nullptr 
	// else, recursive call with shortened word and next node as root.
	input.erase(0,1);
	if(input.empty() || !pulse)
		return pulse;
	else
		return searchHelper(input,pulse);
}

Node* Trie::search(string input){
	input = validate(input);
	if(input.empty())
		return nullptr;
	return searchHelper(input, this->root);
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





















