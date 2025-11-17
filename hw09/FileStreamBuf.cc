#include "FileStreamBuf.h"

FileStreamBuf::FileStreamBuf(FILE* f, int bufSize)
    : file(f), buffer(nullptr), bufferSize(bufSize)
{
    if (bufferSize <= 0) {
        bufferSize = 1;
    }

    buffer = new char[bufferSize];

    // output buffer starts empty
    setp(buffer, buffer + bufferSize);

    // input buffer starts empty (next == end)
    setg(buffer, buffer, buffer);
}

FileStreamBuf::~FileStreamBuf() {
    // flush remaining output
    sync();

    if (file) {
        fclose(file);
        file = nullptr;
    }

    delete [] buffer;
}

int FileStreamBuf::overflow(int c) {
    // write whatever is currently in the buffer
    int count = (int)(pptr() - pbase());
    if (count > 0) {
        size_t written = fwrite(pbase(), 1, count, file);
        if (written != (size_t)count) {
            return EOF;
        }
    }

    // put c into the buffer as first character
    buffer[0] = (char)c;

    // 1byte in buffer
    setp(buffer, buffer + bufferSize);
    pbump(1);

    // return character written
    return c;
}

int FileStreamBuf::sync() {
    // num of bytes currently in the buffer
    int count = (int)(pptr() - pbase());

    if (count > 0) {
        size_t written = fwrite(pbase(), 1, count, file);
        if (written != (size_t)count) {
            return -1;  // error
        }
    }

    // buffer is now empty
    setp(buffer, buffer + bufferSize);
    return 0;
}

int FileStreamBuf::underflow() {
    // if there is still unread data, return next char
    if (gptr() < egptr()) {
        return (unsigned char)(*gptr());
    }

    // read from FILE* into buffer
    int count = (int)fread(buffer, 1, bufferSize, file);
    if (count <= 0) {
        return EOF;   // no more data
    }

    // buffer now has valid data
    setg(buffer, buffer, buffer + count);

    // return next available character (first in buffer)
    return (unsigned char)(*gptr());
}

int FileStreamBuf::uflow() {
    // get next character
    int c = underflow();
    if (c == EOF) {
        return EOF;
    }

    // advance the "next" pointer 
    gbump(1);

    return c;
}
