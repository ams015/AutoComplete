

 
/*
 * Name:  Aman Singh
 * PID: A11012283
 * Account:  ams015
 * Date: 08/21/2016
 * Description: DictionaryTrie class
 */

/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#define SIZE 27
#define ASC 96
#include <queue> 


class TSTNode{

	public:

		unsigned int freq;
		unsigned int most;
		char symb;
		bool isWord; //is it end of word?

		TSTNode* parent;
		TSTNode* left;
		TSTNode* mid;
		TSTNode* right;
		bool starterKey;//is character start of word?

		std::string phrase;
		TSTNode( unsigned int freq, unsigned int most, char symb, bool isWord,
				TSTNode* parent = 0,
				TSTNode* left = 0,
				TSTNode* mid = 0,
				TSTNode* right = 0):
			freq(freq), most(most), symb(symb), isWord(isWord), 
			parent(parent), left(left), mid(mid), right(right) {starterKey=false;}


		bool operator<(const TSTNode& other) const;
};

bool comp(TSTNode* one, TSTNode* other);
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie{
	public:

		/* Create a new Dictionary that uses a Trie back end */
		DictionaryTrie();

		/* Insert a word with its frequency into the dictionary.
		 * Return true if the word was inserted, and false if it
		 * was not (i.e. it was already in the dictionary or it was
		 * invalid (empty string) */
		bool insert(std::string word, unsigned int freq);

		/* Return true if word is in the dictionary, and false otherwise */
		bool find(std::string word) const;

		/* Return up to num_completions of the most frequent completions
		 * of the prefix, such that the completions are words in the dictionary.
		 * These completions should be listed from most frequent to least.
		 * If there are fewer than num_completions legal completions, this
		 * function returns a vector with as many completions as possible.
		 * If no completions exist, then the function returns a vector of size 0.
		 * The prefix itself might be included in the returned words if the prefix
		 * is a word (and is among the num_completions most frequent completions
		 * of the prefix)
		 */
		std::vector<std::string>
			predictCompletions(std::string prefix, unsigned int num_completions);

/*
 *
 *gets the # of words
 */
     int getNumWord();

      int num_words=0;
		//change to private later

		/* Destructor */
		~DictionaryTrie();

	private:
		// Add your own data members and methods here
		bool findHelper(TSTNode*, std::string,unsigned int ) const;

		TSTNode* findPrefixHelper ( TSTNode* curr, std::string prefix,unsigned int length) const;
		TSTNode* findPrefix(std::string prefix) const;
		void RestrictedBFS(TSTNode* curr , unsigned int num_completions,std::vector<std::string> &words);

		std::vector<std::string> predictCompletionsHelper(std::string prefix, unsigned int num_completions);
		TSTNode* root;
   
/*
 *delete all nodes 
 */
static void deleteAll(TSTNode* n) {
 

    if(n == nullptr) return;
    deleteAll(n->left);
    deleteAll(n->right);
    deleteAll(n->mid);
    delete n;
    n = 0;

  }

};


/**
 * comparison for priority queue PQueue that stored pairs of string and frequency
 */
class PairComp1 {
	public:
		bool operator()(std::pair<std::string,unsigned int> lhs, std::pair<std::string,unsigned int> rhs) const {
			if (lhs.second < rhs.second) 

				return true;
			else 
				return false;
		}
};
/**
  * comparison for minHeap that stores pairs of string and frequency
  */
class PairComp2 {
	public:
		bool operator()(std::pair<std::string,unsigned int> lhs, std::pair<std::string,unsigned int> rhs) const {
			if (lhs.second > rhs.second) 

				return true;
			else 
				return false;
		}
};


#endif // DICTIONARY_TRIE_HPP
