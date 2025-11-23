#ifndef PATTERN_H
#define PATTERN_H

#include <string>
using namespace std;

class Pattern {
public:
    string full;
    int count;
    double cumu;

    Pattern();
    Pattern(const string& s, int c);
};

#endif
