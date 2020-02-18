//
//  dictionary.C
//
//  Created by Jesus Lopez on 1/25/20.

#include <stdio.h>
#include <string.h>
#include "dictionary.h"

using namespace std;

/*
 Function to create a new node for our trie. Sets isEndOfWord to false as default value.
 */
dictentry* createdictentry() {
    dictentry *tdictentry = new dictentry();
    tdictentry->isEndOfWord = false;
    return tdictentry;
}

/*
 Function to convert a character to integer. Takes in a character pointer, word, and converts the
 character to an integer. It returns the index corresponding to the position of the letter in the array.
 */
int getIndex(const char *word) {
    if(*word >= 'A' && *word <= 'Z') // if the character is an uppercase character
        return (int)*word - 'A'; // subtract 'A' to return an index between 0 and 25
    else if(*word >= 'a' && *word <= 'z') // if the character is a lowercase character
        return (int)*word - 'a'; // subtract 'a' to return an index between 0 and 25
    else if(*word == 39) // if the character is an apostrophe. 39 refers to its ascii value
        return 26; // return 26, the last position in the array
    else
        return -1; // if index is invalid, not [A-Z, a-z, ']
}

/*
 This function adds words to our trie. Takes in an argument, root, where we will be adding our words.
 root represents the trie. Takes in an argumenet, word, which sets aside memory for a string and also a
 character pointer, and then initializes the pointer to point to the first character in the string. We
 will recursively increment it to point to the next character of the word we're adding to our trie.
 Takes in an additional two arguments, i and len. len is the length of the word we're adding in. i is a
 counter that tells us we have visited each character if it's equal to len, every time we recursively
 call our function we increment i.
 */
 ResultType insert(dictentry* root, const char *word, int i, int len) {
     if(i == len) { // if we have visited every character in the word
         if(root->isEndOfWord == true) // word already exists
             return EXISTS;
         else {
             root->isEndOfWord = true; // set isEndofWord to true
             return ADDED; // we successfully added the word to the trie
             
         }
     }
     else {
         int index = getIndex(word); // get the index of the word
         if(index < 0 || index > 26) return BADCHARS; // if index is out of bounds, it's a BADCHAR
         if(root->next[index] == NULL) // if we don't have a next node pointing to that index
             /*
              We will create a new node for our array at that index.
              */
             root->next[index] = createdictentry();
         /*
          We recursively call our function, insert, moving our root to the next node of the index of
          the word we just added. Increment our pointer word to point to the next character in the
          word. Then increment i since we're moving forward a character.
          */
         return insert(root->next[index],word+1,i+1,len);
    }
}

/*
This function searches if a word exists in our trie. Takes in an argument, root, which is the trie we
 will be searching. Takes in an argumenet, word, which sets aside memory for a string and also a
 character pointer, and then initializes the pointer to point to the first character in the string. We
 will recursively increment it to point to the next character of the word we're searching for in our
 trie. Takes in an additional two arguments, i and len. len is the length of the word we're searching
 for. i is a counter that tells us we have visited each character if it's equal to len, every time we
 recursively call our function we increment i.
*/
ResultType search(dictentry* root, const char *word, int i, int len) {
    if(i == len) { // if we have visited every character in the word
        if(root->isEndOfWord) // if isEndofWord is true, then it is a valid word in the dictionary
            return CORRECT; // return CORRECT
        return MISSPELLED; //else return MISPELLED, invald.
    }
    int index = getIndex(word); // get the index of the word
    if(root->next[index] == NULL) // if we don't have a next node pointing to that index
        return MISSPELLED; // word does not exist because there is no node to that character in the word
    /*
     We recursively call our function, search, moving our root to the next node of the index of the
     word we just added. Increment our pointer word to point to the next character in the word. Then
     increment i since we're moving forward a character.
     */
    return search(root->next[index], word + 1, i + 1, len);
}


