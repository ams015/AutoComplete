
 
/*
 * Name: , Aman Singh
 * PID:  A11012283
 * Account:  ams015
 * Date: 08/21/2016
 * Description: DictionaryTrie class
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <queue> 
#include <cstring>
//using namespace std;

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root =0;}

	/* Insert a word with its frequency into the dictionary.
	 * Return true if the word was inserted, and false if it
	 * was not (i.e. it was already in the dictionary or it was
	 * invalid (empty string) */


bool DictionaryTrie::insert(std::string word, unsigned int freq)
{




	//if the word is already inserted, don't insert
	if(find(word)) return false;
	unsigned int i =1;

	TSTNode* curr;

	//if trie is empty
	if( root ==0){


		root =new TSTNode(0, 0, word.at(0), false, 0,0,0,0);
		root->starterKey=true;
		curr=root;

		if(freq >curr->most){ curr->most=freq;}

	}
 //otherwise
	else{
		curr=root;

		for(;;)
		{

			if(((unsigned int)curr->symb ==(unsigned int)word.at(0))){

				if(freq >curr->most){ curr->most=freq;} break;}


			if ((unsigned int)curr->symb > (unsigned int)word.at(0)){

				if(curr->left ==0){

					curr->left=  new TSTNode(0, 0, word.at(0), false, curr,0,0,0);


				}
				curr = curr->left;
				curr->starterKey=true;

			}else if ((unsigned int)curr->symb < (unsigned int)word.at(0)){

				if(curr->right ==0){

					curr->right=  new TSTNode(0, 0, word.at(0), false, curr,0,0,0);


				}
				curr = curr->right;
				curr->starterKey=true;

			}else{

				curr=curr->mid;

			}


		}
	}



	//add rest of word to tree
	while(i<word.size()){

		if(curr->mid ==0){
			curr->mid =  new TSTNode(0, 0, word.at(i), false, curr,0,0,0);

		}

		curr = curr->mid;


		if(freq >curr->most){ curr->most=freq;}

		for(;;)
		{
			if((curr->symb ==word[i])){ break;}


			if ((unsigned int)curr->symb > (unsigned int)word.at(i)){
				if(curr->left ==0){
					curr->left=  new TSTNode(0, 0, word.at(i), false, curr,0,0,0);

				}
				curr = curr->left;

				if(freq >curr->most){ curr->most=freq;} //comment out later?

			}else if ((unsigned int)curr->symb < (unsigned int)word.at(i)){
				if(curr->right ==0){
					curr->right=  new TSTNode(0, 0, word.at(i), false, curr,0,0,0);
				}
				curr = curr->right;
				if(freq >curr->most){ curr->most=freq;} //comment out later?
			}else{
				curr=curr->mid;
				if(freq >curr->most){ curr->most=freq;}//comment out later?
			}

			//if(freq >curr->most){ curr->most=freq;}
		}


		i++;

	}
  
	curr->isWord=true;//tells u its last character of wrod
	curr->freq=freq;  //frequency
	curr->phrase=word; //stores word in nod
 
 
	if(freq >curr->most){ curr->most=freq;}


  num_words++;
	return true;
}


/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	if (root == 0) return false;
  if ( word =="") return false;
	return findHelper(root, word,word.size());



}
/* helper method for find*/
bool DictionaryTrie::findHelper ( TSTNode* curr, std::string word,unsigned int length) const{


	while( curr != 0){




		if ((unsigned int)curr->symb > (unsigned int)word.at(0)){
			if(curr->left !=0)
				curr = curr->left;
			else{ break;}
      

		}else if ((unsigned int)curr->symb < (unsigned int)word.at(0)){

			if(curr->right !=0)
				curr = curr->right;
        
        
        
			else{ break;}
      
      
		}else {


			if (length == 1){
				if(curr->isWord){return true;}
				return false;

			}

			return findHelper(curr->mid, word.substr(1, word.size()),length-1);	
		}		

	}

	return false;

}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
	std::vector<std::string> words;

  if(prefix==""){
  return words;
  
  }
  
  TSTNode* node = findPrefix(prefix);
  if(node!=0){
	RestrictedBFS(node,num_completions,words);
}

	return words;
}


/* Returns address of last character of prefix
 *
 */
TSTNode* DictionaryTrie::findPrefix(std::string prefix) const
{
	if (root == 0) return 0;
	return findPrefixHelper(root, prefix,prefix.size());



}

/* helper method for findPrefix
 *
 */
TSTNode* DictionaryTrie::findPrefixHelper ( TSTNode* curr, std::string prefix,unsigned int length) const{


	while( curr != 0){




		if ((unsigned int)curr->symb > (unsigned int)prefix.at(0)){
    
			if(curr->left !=0){
				curr = curr->left;
}
			else{ break;}

		}else if ((unsigned int)curr->symb < (unsigned int)prefix.at(0)){

			if(curr->right !=0){
				curr = curr->right;
        }
			else{ break;}
		}else  {

			if (length == 1){
				return curr;

			}

			return findPrefixHelper(curr->mid, prefix.substr(1, prefix.size()),length-1);	
		}		

	}
 
	return 0;


}




/* function to test out a restricted version of BFS on TST subtrees , it only traverses nodes,  will delete later*/
void DictionaryTrie::RestrictedBFS(TSTNode* curr, unsigned int num_completions,std::vector<std::string> &words){

  
  //queue used for BFS
	std::queue<TSTNode*> BFSQueue;
 
  //stores strings and their frequency in max order
	std::priority_queue < std::pair<std::string,unsigned int>,
		std::vector<std::pair<std::string,unsigned int>>,
		PairComp1> PQueue;



  //stores strings and their frequency in min order
	std::priority_queue < std::pair<std::string,unsigned int>,
		std::vector<std::pair<std::string,unsigned int>>,
		PairComp2> minHeap;


  //stores strings and their frequency in min order
	if(curr->isWord){

		std::string  phrase = curr->phrase;
		unsigned  int free = curr->freq;
		minHeap.push(std::pair<std::string,unsigned int>(phrase,free));

	}
 
 
  //stores strings and their frequency in min order
	if(curr->mid){

		BFSQueue.push(curr->mid);
	}


  //loop until quue is empty
	while(BFSQueue.size()!=0){



    //resize the minHeap once it reaches num_completions
		if(minHeap.size()>num_completions){
			minHeap.pop();

		}
   //add current node to queue
		curr= BFSQueue.front();


		if((minHeap.size()>=num_completions) && (curr->most <(minHeap.top().second))){
			BFSQueue.pop();

			continue;
		}
		BFSQueue.pop();


    //look at left child
		if(curr->left) {

          //restriction on minHeap  to minimize  size of all queues
			if((minHeap.size()>=num_completions) && (curr->left->most <(minHeap.top().second))){

			}
      
      //if restriction is met
			else{
      
        //add left child to BFS queue
				BFSQueue.push(curr->left);

        // if word is found from terminating key
				if(curr->left->isWord){


          // another restriction on Priority Queues to minimize their size
					if((minHeap.size()>=num_completions) && (curr->left->freq<(minHeap.top().second))){

					}

          //if restrictions are met, add to priority queues
					else{
						std::string  phrase = curr->left->phrase;
						unsigned  int free = curr->left->freq;
						minHeap.push(std::pair<std::string,unsigned int>(phrase,free));

					}
				}
			}
		}

    //looks at middle child
		if(curr->mid){

      //restriction on Priority Queue and BFS Queue to minimize their size
			if((minHeap.size()>=num_completions) && (curr->mid->most <(minHeap.top().second))){

			}
      
      //if restriction is met
			else{

        //add middle child to BFS queue
				BFSQueue.push(curr->mid);

        // if word is found from terminating key
				if(curr->mid->isWord){
        
          // another restriction on Priority Queues to minimize their size
					if((minHeap.size()>=num_completions) && (curr->mid->freq <(minHeap.top().second))){

					}
           
           //if restrictions are satisfied, add to the priority queue
					else{
						std::string const phrase = curr->mid->phrase;
						unsigned  int free = curr->mid->freq;

						minHeap.push(std::pair<std::string,unsigned int>(phrase,free));
					}
				}
			}
		}
   
    //looks at  right child
		if(curr->right){


			if((minHeap.size()>=num_completions) && (curr->right->most <(minHeap.top().second))){

			} 


      //if restriction is met
			else{
				BFSQueue.push(curr->right);

        // if word is found from terminating key
				if(curr->right->isWord){ 

					std::string  phrase = curr->right->phrase;
					unsigned  int free = curr->right->freq;

          // another restriction on minHeap to minimize sizes of queues and priority queues
					if((minHeap.size()>=num_completions) && (curr->right->freq <(minHeap.top().second))){

					}
           
           //if restrictions are satisfied, add to the priority queue
					else{

						minHeap.push(std::pair<std::string,unsigned int>(phrase,free));
					}
				}
			}
		}


	}

	unsigned int i,j =0;
	unsigned int minHeapSize=minHeap.size();
 
 //put elements from min heap into max heap
	for(j=0;j<minHeapSize;j++){

		std::pair<std::string,unsigned int> a_string = minHeap.top();
		minHeap.pop();
		PQueue.push(a_string);


	}


  //put elements from priority queue into words vector
	while((!PQueue.empty()) || (i<num_completions)){
		if(words.size()==num_completions) break;

		std::pair<std::string,unsigned int> a_string = PQueue.top();


		PQueue.pop();
		words.push_back(a_string.first);

		i++;
	}

     

}

int DictionaryTrie::getNumWord(){
     
     
      return this->num_words;
     }
/* Destructor */
DictionaryTrie::~DictionaryTrie(){

	deleteAll(root);
}

//do deletAll


