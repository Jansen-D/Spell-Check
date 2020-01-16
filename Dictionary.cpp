//  Jansen Dike
//
//  COSC 320 - Project 2
//
//  Dictionary.cpp

#include "Dictionary.h"

node* newNode(std::string word){        //Function to create node
    node *n = new node;                 //Create node
    n->hash = 0;                        //Hash to 0 (default)
    n->word = word;                     //Set word to the word passed in
    n->next = NULL;                     //Next is null by default
    return n;                           //Return node
}

Dictionary::Dictionary(){           //dictionary constructor
    for(int i=0; i<4700; i++){
        table[i] = NULL;            //initializing each node to null to start
    }
}

Dictionary::~Dictionary(){          //destructor for dictionary
    for(int i =0; i < 4700; i++){
        delete table[i];            //delete each node in array
    }
}

void Dictionary::store(std::string word){      //function to store word in table
    node* st = newNode(word);                  //create new node with word
    st->hash = hashString(word);               // calculate hash for the word
    node* curr;                                //temp node curr to keep track
            if(table[st->hash] == NULL){               //if there is no node at that index
                table[st->hash] = st;                  //store the node at that index
                return;
            }
            curr = table[st->hash];
            while(curr->next != NULL){          //while there are still nodes in the chain
                curr=curr->next;                //traverse chain
            }
            curr->next = st;                    //once you've reached the end set the node as next
            return;
    
}

void Dictionary::readDictionary(){
    
    double start = double(clock()) / CLOCKS_PER_SEC;                                //Start clock
     std::ifstream file("english.txt");    //open txt file
     if (file.is_open()) {                                                        //check if file opened
         std::string line;                                                         //line hold each line
         while (getline(file, line)) {                                          //sets current line to line
             store(line.c_str());                                          //calls store to store the string
         }
         file.close();                                      //close file
     }
    double finish = double(clock()) / CLOCKS_PER_SEC;       //end clock
    double elapsed = finish - start;                        //calulate elapsed time
    std::cout << "Time taken: " << elapsed << std::endl;    //print time
}

int Dictionary::countWords(){
    int count = 0;                  // word count starts at 0
    node* curr;                     //node to traverse table
    
    for(int i=0; i<4700; i++){       //for loop to traverse table
        curr = table[i];
        while(curr!=NULL){          //while there is a node, haven't reached the end of chain
            count++;                //count increases after visiting each word
            curr=curr->next;        //traverse chain
        }
    }
    return count;                   //returns word count
}

int Dictionary::largestBucket(){       //function to find largest bucket
    int lsize=0;                        //keeps track of largest bucket size
    node *curr;                         //node to traverse table
    for(int i=0; i<4700; i++){          //for loop to go through table
        int csize=0;                    //current size set to 0
        curr = table[i];                //curr visits each index
        while(curr!=NULL){              //while chain is not at end
            csize++;                    //current size increase every node you move in chain
            curr=curr->next;            //traverse chain
        }
        if(csize > lsize){              //if current size is greater than the largest size
            lsize = csize;              //current becomes the new largest
        }
    }
    return lsize;                       //return largest bucket size
}

int Dictionary::smallestBucket(){       //function to find smallest bucket
    int ssize=0;                        //keeps track of smalles bucket size
    node *curr;                         //node to traverse table
    for(int i=0; i<4700; i++){          //for loop for each index
        int csize=0;                    //size of current chain
        curr = table[i];                //let curr be start of chain at that index
        while(curr!=NULL){              //while not at end of chain
            csize++;                    //current size increase for every node in chain
            curr=curr->next;            //traverse chain
        }
        if(i == 0){                     //base case
            ssize = csize;
        }
        if(csize < ssize && csize!=0){      //if the current size is greater than 0 but smaller than the smallest size
            ssize = csize;                  //set smallest size to current size
        }
    }
    return ssize;                           //return smallest size
}

int Dictionary::usedBuckets(){
    int count = 0;                      //number of used buckets
    for(int i=0; i<4700; i++){          //for loop for table
        if(table[i]!=NULL){             //if bucket is used
            count++;                    //count increases
        }
    }
    return count;                       //return count
}

int Dictionary::countBuckets(){
    return 4700;                        //number of buckets is 4700
}

double Dictionary::avgItem(){       //function to find average words per bucket
    double words = countWords();     //number of words
    double buckets = countBuckets();    //number of buckets
    double avg = words/buckets;          //calculate average
    return avg;                         //return average
}

void Dictionary::spellCheck(){
    std::cout << "*************************************************************************" << std::endl;
    std::cout << "SPELL CHECKER" << std::endl;
    std::cout << "*************************************************************************" << std::endl;
    std::string userStr;            //string the user enters
    std::string tmp;                //each word will be tmp
    std::vector<std::string> userWords;         //load each words into vector
    std::vector<std::string> misspelled;         //all misspelled words in this vector
    std::cout << "Please enter a string: " << std::endl;  //prompts user to enter string
    
    std::string t;
    std::getline(std::cin, t);                                     //read in string
    std::istringstream iss(t);                              //use stringstream to pick out words
    while(iss >> tmp){                                           //while there are words still loaded into tmp
        userWords.push_back(tmp);                               //add to user word vector
    }
    
    
    
    for(int i=0; i<userWords.size(); i++){                      //for loop to go through user words
        if(findWord(userWords.at(i)) !=0)                       //if not in dictionary
            misspelled.push_back(userWords.at(i));              //add to misspelled vector
    }
    for(int i=0; i<misspelled.size(); i++){                 //for loop to go through misspelled
        suggest(misspelled.at(i));                          //run suggest for each misspelled word
    }
    
    std::cout << "Total number of misspelled words: " << misspelled.size() << std::endl;   //print number of misspelled words
}


void Dictionary::suggest(std::string word){                 //function for word suggestions
    std::cout << word << " is misspelled!" << std::endl;    //alerts user of misspelled word
    std::vector<std::string> suggestions;                   //create a vector of suggestions
    int edits = 0;                                          //keeps track of edit distance
    double start = double(clock()) / CLOCKS_PER_SEC;        //start clock
    replace(word, suggestions, edits);                      //call replace edit
    del(word, suggestions, edits);                          //call delete edit
    swap(word, suggestions, edits);                         //call swap edit
    add(word, suggestions, edits);                          //call add edit
    double finish = double(clock()) / CLOCKS_PER_SEC;       //end clock
    double elapsed = finish - start;                        //calculate time
    
    if(suggestions.size() == 0){                            //if there are no suggestions
        std::cout << "No suggestions found for " << word << std::endl;    //print message
        return;                                                           //done
    }
    
    std::cout << "Suggestions for " << word << ":";                     //print suggestions
    for(int i=0; i<suggestions.size(); i++){
        std::cout << " *" << suggestions.at(i) << "* ";
    }
    std::cout << std::endl;
    
    std::cout << "Number of suggestions: " << suggestions.size() << std::endl;      //print # of suggestions
    std::cout << "Time taken to find suggestions: " << elapsed << std::endl;        //print time taken
}


int Dictionary::findWord(std::string str){              //function checks if a word is in dictionary
    node* curr;                                        //node to traverse chains
    int pos = hashString(str);
    curr = table[pos];
        while(curr!=NULL){                              //while not at end of chain
            if(curr->word == str){                      //check if word matches current string
                return 0;                               //return 0 if found
            }
            curr=curr->next;
        }
    
    return 1;                       //return 1 if not found
}


int Dictionary::checkDup(std::string word, std::vector<std::string> suggestions){   //function to check for a duplicate suggestion
    for(int i=0; i<suggestions.size(); i++){
        if(suggestions.at(i)==word)
            return 1;                   //if suggestion is already in vector return 1
    }
    return 0;                   //otherwise return 0;
}


void Dictionary::replace(std::string word, std::vector<std::string> &suggestions, int edits){
    if(edits >=2)       //if already have done two edits no more can be done
        return;
    char arr[26] = { 'a', 'b' , 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z'}; //alphabet array
    std::string tmp;                      //tmp string to hold each suggestion
    for(int i=0; i<word.size(); i++){
        for(int j=0; j<26; j++){
            tmp = word;                 //let tmp equal misspelled word
            tmp.at(i) = arr[j];         //replace each letter with each possible letter in alphabet
        
            if(findWord(tmp)==0 && checkDup(tmp, suggestions)==0){      //if is not duplicate and is in the dictionary it is a valid suggestion
            suggestions.push_back(tmp);     //push suggestion into vector
            }
            edits++;
            //calls each possible edit
            replace(tmp, suggestions, edits);
            swap(tmp, suggestions, edits);
            del(tmp, suggestions, edits);
            add(tmp, suggestions, edits);
        }
    }
}

void Dictionary::del(std::string word, std::vector<std::string> &suggestions, int edits){
        if(edits >=2)           //edit distance is already two
            return;
	if(word.size() <= 1){
		return;
	}
        std::string tmp;
        for(int i=0; i<word.size(); i++){
            tmp = word;
            tmp.erase(tmp.begin()+i);           //delete character at that position
            if(findWord(tmp)==0 && checkDup(tmp, suggestions)==0){
                suggestions.push_back(tmp);     //add to suggestions if valid
            }
            edits++;
            //calls each possible edit funciton
            replace(tmp, suggestions, edits);
            swap(tmp, suggestions, edits);
            del(tmp, suggestions, edits);
            add(tmp, suggestions, edits);
        }
    }


void Dictionary::swap(std::string word, std::vector<std::string> &suggestions, int edits){
    if(edits >=2)       //edit distance is already two so do nothing
        return;
    std::string tmp;
    char tmpchar;
        for(int i=0; i<word.size()-1; i++){
            tmp = word;
            tmpchar = tmp.at(i);     //holds char of current position
            tmp.at(i) = tmp.at(i+1);        //current pos is now the char in front of it
            tmp.at(i+1) = tmpchar;          //char at pos i+1 is now tmp which was char at pos i
            if(findWord(tmp)==0 && checkDup(tmp, suggestions)==0){
                suggestions.push_back(tmp); //add to suggestions if valid
            }
            edits++;
            //calls each possible edit function
            replace(tmp, suggestions, edits);
            swap(tmp, suggestions, edits);
            del(tmp, suggestions, edits);
            add(tmp, suggestions, edits);
        }
    }

void Dictionary::add(std::string word, std::vector<std::string> &suggestions, int edits){
    if(edits >=2)               //edit distance already 2 so return
        return;
    char arr[26] = { 'a', 'b' , 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z'};
    std::string tmp;
    for(int i=0; i<word.size(); i++){
        for(int j=0; j<26; j++){
            tmp = word;
            tmp.insert(tmp.begin()+i, arr[j]);      //insert each alphabet character into each position
        
            if(findWord(tmp)==0 && checkDup(tmp, suggestions)==0){  //if not a duplicate and is a word
            suggestions.push_back(tmp);     //add to suggestions
            }
            edits++;
            //calls each of the possible edit functions
            replace(tmp, suggestions, edits);
            swap(tmp, suggestions, edits);
            del(tmp, suggestions, edits);
            add(tmp, suggestions, edits);
        }
    }
}



int hashString(std::string word){ //function to hash a string
    int hash = 0;                  //hash is 0 by default
    int a=57;                   //prime number <64
    int W=pow(2, 64);           //2^64
    int Z=pow(2, 5);            //2^5
    for(int i =0; i < word.size()-1; i++){ //hashing each letter and adding to hash
        hash+=(((word.at(i)*a)%W)/Z);       //calculates hash of each letter and adds to hash
       }
    
    while(hash>=4700){  //while hash is too large divide it by 2
        hash=hash/2;
    }
    
    return hash;            //return its hash
}

