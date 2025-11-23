#include "TextModel.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

TextModel::TextModel(int length) : L(length) { }

string TextModel::readAll(const string& path) {
    ifstream in(path.c_str());
    if (!in) {
        cerr << "Could not open: " << path << "\n";
        exit(1);
    }
    string big, w;
    bool first = true;
    while (in >> w) {
        if (!first) big.push_back(' ');
        big += w;
        first = false;
    }
    return big;
}

void TextModel::buildCounts(const string& text) {
    counts.clear();
    if ((int)text.size() < L) return;
    counts.reserve(text.size());
    for (size_t i = 0; i + (size_t)L <= text.size(); ++i) {
        counts[text.substr(i, (size_t)L)]++;
    }
}

void TextModel::buildLookup() {
    lookup.clear();
    lookup.reserve(counts.size());
    for (auto it = counts.begin(); it != counts.end(); ++it) {
        const string& pat = it->first;
        int cnt = it->second;
        string prefix = pat.substr(0, (size_t)(L - 1));
        lookup[prefix].push_back(Pattern(pat, cnt));
    }
}

void TextModel::computeCumulative() {
    for (auto it = lookup.begin(); it != lookup.end(); ++it) {
        vector<Pattern>& v = it->second;
        long long sum = 0;
        for (size_t i = 0; i < v.size(); ++i) sum += v[i].count;
        long long run = 0;
        for (size_t i = 0; i < v.size(); ++i) {
            run += v[i].count;
            v[i].cumu = (double)run / (double)sum;  // ends at 1.0
        }
    }
}

void TextModel::trainFromFile(const string& path) {
    string text = readAll(path);
    if ((int)text.size() < L) {
        cerr << "Training text too short for L=" << L << "\n";
        exit(1);
    }
    buildCounts(text);
    buildLookup();
    computeCumulative();
    srand((unsigned)time(NULL));
}

string TextModel::generate(size_t outChars, const string& seedPrefix) {
    if (lookup.empty()) return "";

    string prefix = seedPrefix;
    if ((int)prefix.size() != L - 1 || lookup.find(prefix) == lookup.end()) {
        // pick the first available prefix
        prefix = lookup.begin()->first;
    }

    string out = prefix;
    out.reserve(outChars + prefix.size());

    while (out.size() < outChars) {
        auto it = lookup.find(prefix);
        if (it == lookup.end() || it->second.empty()) break;

        double r = (double)rand() / (double)RAND_MAX;
        const vector<Pattern>& v = it->second;
        const Pattern* chosen = &v.back();
        for (size_t i = 0; i < v.size(); ++i) {
            if (r <= v[i].cumu) { chosen = &v[i]; break; }
        }

        char nextCh = chosen->full[(size_t)(L - 1)];
        out.push_back(nextCh);

        if ((int)out.size() >= L - 1) {
            prefix = out.substr(out.size() - (size_t)(L - 1), (size_t)(L - 1));
        } else {
            prefix = out;
        }
    }

    return out;
}
