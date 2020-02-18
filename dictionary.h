//
//  dictionary.h
//
//  Created by Jesus Lopez on 1/25/20.

#ifndef dictionary_h
#define dictionary_h
#define Nchars 27 /* a- z + ' */
#include <string>

using namespace std;

class dictentry {
public:
    //isEndOfWord is true if the node represents end of a word
    bool isEndOfWord;
    //subsequent characters in words. Null pointers if there are no further words with the next letter
    class dictentry *next[Nchars];
};

typedef enum {
    CORRECT, // word has correct spelling
    MISSPELLED,
    BADCHARS, // word has characters outside [A-Z,a-z,']
    ADDED,
    EXISTS,
} ResultType;

dictentry* createdictentry();
int getIndex(const char *word);
//insert operation signature
ResultType insert(dictentry* root, const char *word, int i, int len);
//search operation signature
ResultType search(dictentry* root, const char *word, int i, int len);
#endif /* dictionary_h */
