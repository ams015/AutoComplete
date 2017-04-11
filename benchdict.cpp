
 
/*
 * Name: Yicun Liu, Aman Singh
 * PID: A92412701, A11012283
 * Account: cs100vbg, ams015
 * Date: 08/21/2016
 * Description: BST Iterator class represents binary search tree's iterator.
 */
#include <iostream>
#include <fstream>
#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "util.hpp"



using namespace std;
 
int main(int argc, char *argv[]) {
Timer timer;
int min_size=atoi(argv[1]);
int step_size=atoi(argv[2]);
int num_iterations =atoi(argv[3]);
ifstream dictfile;
long time,avg,time_after;
Utils ut1,ut2,ut3;
int i,j;
  cout<<"DictionaryHashtable"<<endl;
//hashtable
  i =0;
  while(i<num_iterations){
 
  DictionaryHashtable* dictHT= new DictionaryHashtable();
  
  ut1.load_dict(*dictHT, dictfile,min_size + i*step_size );
  
  
  time=0;
  j=0;
    while(j<20)
    {
    
      timer.begin_timer();  
      dictHT->find("asdfghdadsf");
      dictHT->find("cntusdfdsff");
      dictHT->find("afs ghs kkdsf");
      dictHT->find("asdfg");
      dictHT->find("asdfgfsd");
      dictHT->find("sdfasdfgsdfasdf");
      dictHT->find("bafoon");
      dictHT->find("pattan bharamula");
      dictHT->find("bafodfon");
      dictHT->find("kkpattanbvdfharamdfula");
      
      time_after= timer.end_timer();
      time=time+time_after;
      
     j++;
    }
    
    std::cout << min_size + i*step_size << "\t" ;
    
    avg=time/20;
    std::cout << avg<<std::endl;
    dictfile.clear();
    i++;
      }
//BST

  cout<<"DictionaryBST"<<endl;
  
  i =0;
  while(i<num_iterations){
  DictionaryBST* dictBST= new DictionaryBST();
  ut2.load_dict(*dictBST,dictfile,min_size + i*step_size);

    j=0;
    while(j<20)
    {
    
      timer.begin_timer();  
       dictBST->find("asdfghdadsf");
      dictBST->find("cntusdfdsff");
      dictBST->find("afs ghs kkdsf");
      dictBST->find("asdfg");
      dictBST->find("asdfgfsd");
      dictBST->find("sdfasdfgsdfasdf");
      dictBST->find("bafoon");
      dictBST->find("pattan bharamula");
      dictBST->find("bafodfon");
      dictBST->find("kkpattanbvdfharamdfula");
      time_after= timer.end_timer();
      time=time+time_after;
       j++;
      }
      
    std::cout << min_size + i*step_size << "\t" ;
        avg=time/20;
    std::cout << avg<<std::endl;
    dictfile.clear();
    i++;
        }
//TST

  cout<<"DictionaryTrie"<<endl;
  i =0;
  while(i<num_iterations){
  DictionaryTrie* trie= new DictionaryTrie();
  Utils::load_dict( *trie,dictfile,min_size + i*step_size);
  
    if(trie->getNumWord()<min_size + i*step_size){
    
    cout<<"Warning:Fewer than"<<min_size + i*step_size<<
    " size words in trie"<<endl;
    }
    j=0;
    while(j<20)
    {
    
  
      timer.begin_timer(); 
       trie->find("asdfghdadsf");
       trie->find("cntusdfdsff");
       trie->find("afs ghs kkdsf");
       trie->find("asdfg");
       trie->find("asdfgfsd");
       trie->find("sdfasdfgsdfasdf");
       trie->find("bafoon");
       trie->find("pattan bharamula");
       trie->find("bafodfon");
       trie->find("kkpattanbvdfharamdfula"); 
      time_after= timer.end_timer();
      time=time+time_after;
      j++;
      }
      
    std::cout << min_size + i*step_size << "\t" ;
        avg=time/20;
    std::cout << avg<<std::endl;
    dictfile.clear();
    i++;
      }
      delete trie;
      delete dictBST;
      delete dictHT;
}