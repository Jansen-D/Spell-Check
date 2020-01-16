//  Jansen Dike
//
//  COSC 320 - Project 2
//
//  Dictionary.h


#ifndef Dictionary_h
#define Dictionary_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

struct node{            //node structure
    int hash;           //hash member
    std::string word;   //word member
    node *next;         //next node in chain
};

node* newNode(std::string word);     //function to create new node

class Dictionary{
    
private:
    
public:
    
    node* table[4700];          //create table of nodes (hash table)

    Dictionary();               //constructor
    ~Dictionary();              //destructor
    
    void store(std::string word);       //function to store word into hash table
    void readDictionary();              //reads file and loads word into hash table
    int countWords();                   //number of words in hash table
    int largestBucket();                //function to find size of largest bucket
    int smallestBucket();               //function to find size of smallest buckets
    int countBuckets();                 //count number of buckets
    int usedBuckets();                  //function to find number of used buckets
    double avgItem();                   //function to find average number of items per bucket
    
    void spellCheck();                  //spell check functon
    void suggest(std::string word);     //function to find suggestions for a misspelled word
    int findWord(std::string str);      //function to check if a word is in the hash table
    
    int checkDup(std::string word, std::vector<std::string> suggestions);       //check if suggestion is already in vector
    void replace(std::string word, std::vector<std::string> &suggestions, int edits);  //replace edit
    void del(std::string word, std::vector<std::string> &suggestions, int edits);      //delete edit
    void add(std::string word, std::vector<std::string> &suggestions, int edits);      //add edit
    void swap(std::string word, std::vector<std::string> &suggestions, int edits);    //swap edit

};


int hashString(std::string word);           //function to hash a word to an integer


#endif /* Dictionary_h */
