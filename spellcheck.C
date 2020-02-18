//
//  spellcheck.C
//
//  Created by Jesus Lopez on 1/25/20.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include "dictionary.h"

using namespace std;

int main(int argc, const char * argv[]) {
    dictentry* root = createdictentry(); // create a new node to build our trie
    /*
     Separators used to split the words read in from our text file to tokenize each string.
     */
    const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
    ifstream myfile(argv[2]); // will read in aspell_list_en.txt, what we're using to build the trie
    if(myfile.is_open()) { // need to fail if the file does not exist
        string word; // we will store each string in word
        /*
        Extracts characters from myfile and stores them into word until the delimitation character
         delim is found (or the newline character, '\n').
        */
        while(getline(myfile,word)) {
            /*
            Returns a pointer to an array that contains a null-terminated sequence of characters (i.e.,
             a c-string) representing the current value of the string object.
            This array includes the same sequence of characters that make up the value of the string
             object plus an additional terminating null-character ('\0') at the end.
            */
            char *cstr = new char[word.length()+1];
            strcpy(cstr, word.c_str()); // cstr will contain a c-string copy of word
            /*
             Return the first string that will not contain any of the characters in separators and store it in token.
             */
            char *token = (char*)strtok(cstr, separators);
            while (token != NULL) {
                /*
                 Call insert method to insert the current token into our trie.
                 */
                insert(root, token, 0, (int)strlen(token));
                token = strtok(NULL, separators); // get the next token from the line_c buffer
            }
        }
        myfile.close(); // close the file
    }
    
//====================================================================================================
    
    ifstream myfiles(argv[1]); // will read in a text file to check if the word exists in the trie
    if(myfiles.is_open()) { // need to fail if the file does not exist
        string word; // we will store each string in word
        /*
        Extracts characters from myfile and stores them into word until the delimitation character
         delim is found (or the newline character, '\n').
        */
        while(getline(myfiles,word)) {
            /*
            Returns a pointer to an array that contains a null-terminated sequence of characters (i.e.,
             a c-string) representing the current value of the string object.
            This array includes the same sequence of characters that make up the value of the string
             object plus an additional terminating null-character ('\0') at the end.
            */
            char *cstr = new char[word.length()+1];
            strcpy(cstr, word.c_str()); //cstr now contains a c-string copy of word
            /*
             Return the first string that will not contain any of the characters in separators and
             store it in token.
            */
            char *token = (char*)strtok(cstr, separators); // returns first token
            while (token != NULL) {
                /*
                Call search method to insert the current token into our trie.
                */
                if(search(root, token, 0, (int)strlen(token)) == MISSPELLED) {
                    string word(token); // convert char array to a string
                    cout << word + "\n"; // output MISPELLED words to std::cout
                }
                token = strtok(NULL, separators); // get the next token from the line_c buffer
            }
        }
        myfiles.close(); //close the file
    }
    return 0;
}
