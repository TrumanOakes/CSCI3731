#ifndef FILESTREAMBUF_H
#define FILESTREAMBUF_H

#include <streambuf>
#include <stdio.h>

class FileStreamBuf : public std::streambuf {
private:
    FILE* file;
    char* buffer;
    int bufferSize;

public:
    FileStreamBuf(FILE* f, int bufSize);
    ~FileStreamBuf();

    FileStreamBuf(const FileStreamBuf&) = delete;
    FileStreamBuf& operator=(const FileStreamBuf&) = delete;
    FileStreamBuf(FileStreamBuf&&) = delete;
    FileStreamBuf& operator=(FileStreamBuf&&) = delete;

protected:
    // output
    virtual int overflow(int c);
    virtual int sync();

    // input
    virtual int underflow();
    virtual int uflow();
};

#endif
