#ifndef TEXTMODEL_H
#define TEXTMODEL_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Pattern.h"

using namespace std;

class TextModel {
private:
    int L;
    unordered_map<string,int> counts;
    unordered_map<string, vector<Pattern> > lookup;

    string readAll(const string& path);
    void buildCounts(const string& text);
    void buildLookup();
    void computeCumulative();

public:
    TextModel(int length);
    void trainFromFile(const string& path);
    string generate(size_t outChars, const string& seedPrefix = "");
};

#endif
