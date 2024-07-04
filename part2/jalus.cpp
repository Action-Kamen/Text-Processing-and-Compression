Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* t=new TrieNode;
	for(int i=0;i<ALPHABET_SIZE;i++)
	{
		t->children[i]=NULL;
	}
	t->isWordEnd=false;
	return t;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	//cout<<"a"<<endl;
	if(!search(root,key))
	{
		TrieNode* curr=root;
		for(char c:key)
		{
			int index=CHAR_TO_INDEX(c);
			if(!curr->children[index]){curr->children[index]=getNode();}
			curr=curr->children[index];
		}
		curr->isWordEnd=true;
	}
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	//cout<<"b"<<endl;
	TrieNode* curr=root;
	for(char c:key)
	{
		int index=CHAR_TO_INDEX(c);
		if(!curr->children[index])return false;
		curr=curr->children[index];
	}
	return(curr!=NULL&&curr->isWordEnd);
	
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	//cout<<"c"<<endl;
	for(int i=0;i<ALPHABET_SIZE;i++)
	{
		if(!root->children[i])
		{
			return 0;
		}
	}
	return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	TrieNode* curr=root;
	for(char c:currPrefix)
	{
		int index=CHAR_TO_INDEX(c);
		if(!curr->children[index]){return;}
		curr=curr->children[index];
	}
	cout<<currPrefix<<endl;
	for(int i=0;i<ALPHABET_SIZE;i++)
	{
		currPrefix.push_back(char(i));
            suggestionsRec(curr, currPrefix);
            currPrefix.pop_back();
	}

	// found a std::string in Trie with the given prefix
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	//if(!search(root,query)){return 0;}
	// if(search(root,query))
	// {
	TrieNode* curr=root;
	for(char c:query)
	{
		int index=CHAR_TO_INDEX(c);
		if(!curr->children[index]){return 0;}
		curr=curr->children[index];
	}
	if(isLastNode(curr)){return -1;}
	// }
	suggestionsRec(root,query);
	return 2;
}