#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    int blanks = 0;
    int first = -1;
    std::set<std::string> ret;
    for (int i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            blanks++;
            if (first == -1) first = i;
        }
    }
    if (blanks < floating.size()) {
        return ret;
    }
    if (blanks == 0) {
        if (dict.count(in) == 1) ret.insert(in);
        return ret;
    }
    
    for (int i = 0; i < floating.size(); i++) {
        string temp = in;
        string temp1 = floating;
        temp1.replace(i, 1, "");
        temp[first] = floating[i];
        std::set<std::string> t = wordle(temp, temp1, dict);
        for (auto j = t.begin(); j != t.end(); j++) {
            ret.insert(*j);
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        string temp = in;
        temp[first] = c;
        std::set<std::string> t = wordle(temp, floating, dict);
        for (auto j = t.begin(); j != t.end(); j++) {
            ret.insert(*j);
        }
    }
    return ret;
}

// Define any helper functions here

