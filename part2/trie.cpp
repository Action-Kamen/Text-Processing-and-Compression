#include "trie.h"
#include <iostream>
using namespace std;

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* t= new TrieNode;
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
	if(search(root,key))return;
	cout<<"andar"<<endl;
	int i=0;
	TrieNode* temp=root;
	if(key[0]=='\0')return;
	while(key[i+1]!='\0')
	{
		if(temp->children[CHAR_TO_INDEX(key[i])]==NULL)
		{
			temp->children[CHAR_TO_INDEX(key[i])]=getNode();
		}
		temp=temp->children[CHAR_TO_INDEX(key[i])];
		i++;
	}
	cout<<"andar.1"<<endl;
	if(temp->children[CHAR_TO_INDEX(key[i])]==NULL)
		{
			temp->children[CHAR_TO_INDEX(key[i])]=getNode();
		}
	temp->children[CHAR_TO_INDEX(key[i])]->isWordEnd=1;
	cout<<"andarexit"<<endl;
	return;
}

//Trienode letter

bool Trie::search(struct TrieNode *root, std::string key)
{
	cout<<"search"<<endl;
	int i=0;
	TrieNode* temp;
	temp=root;
	if(key[i]=='\0')return true;
	while(key[i+1]!='\0' && temp->children[CHAR_TO_INDEX(key[i])]!=NULL)
	{
		temp=temp->children[CHAR_TO_INDEX(key[i])];
		i++;
	};
	cout<<"search.1"<<endl;
	if(key[i+1]=='\0')
	{
		if(temp->children[CHAR_TO_INDEX(key[i])]==NULL)
		{
			return false;
		}
		cout<<"search.2"<<endl;
		temp=temp->children[CHAR_TO_INDEX(key[i])];
		if(temp->isWordEnd==1)
		{
			return true;
		};
		return false;
	}
	cout<<"searchexit"<<endl;
	return false;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	TrieNode* temp;
	temp=root;
	int i=0;
	while(i<26)
	{
		if(temp->children[CHAR_TO_INDEX(key[i])]!=NULL)return false;
		i++;
	}
	return true;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	TrieNode* temp=root;
	int i =0;
	while(currPrefix[i]!='\0' && currPrefix[i+1]!='\0' && temp->children[CHAR_TO_INDEX(key[i])]!=NULL)
	{
		temp=temp->children[CHAR_TO_INDEX(currPrefix[i])];
		i++;
	};
	if(temp->children[CHAR_TO_INDEX(currPrefix[i])]==NULL) return;
	if(currPrefix[i+1]!='\0')return;
	temp=temp->children[CHAR_TO_INDEX(currPrefix[i])];
	i++;
	for(int j=0; j<26; j++)
	{
		if(temp->children[CHAR_TO_INDEX(j)]==NULL) continue;
		string newt[i+2];
		for (size_t l = 0; l < i; l++)
		{
			newt[l]=currPrefix[l];
		}
		newt[i]=char(j+int(a)-1);
		newt[i+1]='\0';
		if (temp->children[CHAR_TO_INDEX(j)]->isWordEnd==1)cout<<newt<<endl;
		suggestionsRec(root,newt);
	}
	return;
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	TrieNode* temp=root;
	int i =0;
	while(currPrefix[i+1]!='\0' && temp->children[CHAR_TO_INDEX(key[i])]!=NULL)
	{
		temp=temp->children[CHAR_TO_INDEX(currPrefix[i])];
		i++;
	};
	if(temp->children[CHAR_TO_INDEX(currPrefix[i])]==NULL) return;
	if(currPrefix[i+1]!='\0')return;
	temp=temp->children[CHAR_TO_INDEX(currPrefix[i])];
	i++;
	for(int j=0; j<26; j++)
	{
		if(temp->children[CHAR_TO_INDEX(j)]==NULL) continue;
		string newt[i+2];
		for (size_t l = 0; l < i; l++)
		{
			newt[l]=currPrefix[l];
		}
		newt[i]=char(j+int(a)-1);
		newt[i+1]='\0';
		if (temp->children[CHAR_TO_INDEX(j)]->isWordEnd==1)cout<<newt<<endl;
		suggestionsRec(root,newt);
	}
	return;
}
