#include <iostream>
#include <stdio.h>
#include "FileStreamBuf.h"
using namespace std;

int main() {
    {
        FILE* f = fopen("test_io.txt", "w");
        if (!f) {
            perror("fopen for write");
            return 1;
        }

        FileStreamBuf fsb(f, 4);   // small buffer
        ostream out(&fsb);

        out << "Yoyoyo\n";
        // destructor will call sync() and fclose()
    }

    cout << "Wrote to test_io.txt.\n";

    // test input: read back through FileStreamBuf
    {
        FILE* f = fopen("test_io.txt", "r");
        if (!f) {
            perror("fopen for read");
            return 1;
        }

        FileStreamBuf fsb(f, 4);
        istream in(&fsb);

        cout << "Reading back from test_io.txt:\n";

        char c;
        while (in.get(c)) {
            cout << c;
        }

        cout << "Easy. Done. (it was not easy) \n";
    }

    return 0;
}
