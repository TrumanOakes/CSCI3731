#include <iostream>
#include <string>
#include "TextModel.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0]
             << " <training.txt> <pattern_length L>=2 <output_chars> [seed_prefix]\n";
        return 1;
    }

    string path = argv[1];
    int L = stoi(argv[2]);
    size_t outChars = (size_t)stoll(argv[3]);
    string seed = (argc >= 5) ? argv[4] : "";

    if (L < 2) {
        cerr << "pattern_length must be >= 2\n";
        return 1;
    }

    TextModel model(L);
    model.trainFromFile(path);
    string result = model.generate(outChars, seed);

    cout << result << "\n";
    return 0;
}
