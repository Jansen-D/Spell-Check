//  Jansen Dike
//
//  COSC 320 - Project 2
//
//  main.cpp

#include <iostream>
#include "Dictionary.cpp"

int main() {
    
    Dictionary test;                //Create dictionary object
    test.readDictionary();          //Load words into dictionary
    std::cout << "Total words: " << test.countWords() << std::endl;                 //Print total words
    std::cout << "Largest bucket size: " << test.largestBucket() << std::endl;      // Print largest bucket size
    std::cout << "Smallest bucket size: " << test.smallestBucket() << std::endl;    //Print smallest bucket size (non-zero)
    std::cout << "Total number of buckets: " << test.countBuckets() << std::endl;   //Print total buckets
    std::cout << "Number of buckets used: " << test.usedBuckets() << std::endl;     //Print number of buckets used
    std::cout << "Average number of nodes per bucket: " << test.avgItem() << std::endl << std::endl << std::endl;                                                          //Print average nodes per bucket
    
    test.spellCheck();          //Run spell check
    return 0;
}
