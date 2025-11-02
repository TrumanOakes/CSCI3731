#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Image {
public:
    int width = 0;
    int height = 0;
    std::vector<unsigned char> pixels;

    ~Image() = default;

    bool readPPM(const std::string& path) {
        std::ifstream in(path, std::ios::binary);
        if (!in) return false;

        std::string magic;
        int maxval = 0;

        // header
        if (!(in >> magic >> width >> height >> maxval)) return false;
        if (magic != "P6" || width <= 0 || height <= 0 || maxval != 255) return false;

        // consume 
        in.get();

        const size_t size = static_cast<size_t>(width) * static_cast<size_t>(height) * 3u;
        pixels.resize(size);

        // read RGB block
        in.read(reinterpret_cast<char*>(pixels.data()),
                static_cast<std::streamsize>(size));
        return static_cast<size_t>(in.gcount()) == size;
    }

    bool writePPM(const std::string& path) const {
        if (width <= 0 || height <= 0 ||
            pixels.size() != static_cast<size_t>(width) * static_cast<size_t>(height) * 3u) {
            return false;
        }
        std::ofstream out(path, std::ios::binary);
        if (!out) return false;

        out << "P6\n" << width << ' ' << height << "\n255\n";

        // RGB block
        out.write(reinterpret_cast<const char*>(pixels.data()),
                  static_cast<std::streamsize>(pixels.size()));
        return static_cast<bool>(out);
    }

    // add int to color channels
    Image& operator+=(int bias) {
        for (auto& c : pixels) {
            int v = static_cast<int>(c) + bias;
            if (v < 0) v = 0;
            if (v > 255) v = 255;
            c = static_cast<unsigned char>(v);
        }
        return *this;
    }
};