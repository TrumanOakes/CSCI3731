#include "Pattern.h"

Pattern::Pattern() {
    full = "";
    count = 0;
    cumu = 0.0;
}

Pattern::Pattern(const string& s, int c) {
    full = s;
    count = c;
    cumu = 0.0;
}
