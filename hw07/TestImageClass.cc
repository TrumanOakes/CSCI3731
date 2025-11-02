#include <iostream>
#include "ImageClass.cc"

int main(int argc, char** argv) {
    const std::string inPath  = (argc >= 2) ? argv[1] : "test.ppm";
    const std::string outPath = (argc >= 3) ? argv[2] : "out.ppm";
    const int bias            = (argc >= 4) ? std::stoi(argv[3]) : 25;

    Image img;
    if (!img.readPPM(inPath)) {
        std::cerr << "Failed to read PPM: " << inPath << "\n";
        return 1;
    }

    img += bias;

    if (!img.writePPM(outPath)) {
        std::cerr << "Failed to write PPM: " << outPath << "\n";
        return 1;
    }

    std::cout << "Wrote " << outPath << " (+" << bias << " per channel)\n";
    return 0;
}