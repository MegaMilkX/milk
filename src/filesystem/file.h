#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <windows.h>
#include <string>

class File
{
public:
    enum MODE
    {
        READ = OF_READ,
        WRITE = OF_WRITE,
        READWRITE = OF_READWRITE,
        CREATE = OF_CREATE,
    };

    enum SEEKFROM
    {
        BEGIN = FILE_BEGIN,
        CURRENT = FILE_CURRENT,
        END = FILE_END
    };

    File(){}
    ~File(){ if (readBuffer.sz > 0) readBuffer.Free(); }

    static File Create(std::string path, File::MODE mode = READWRITE);
    static File Open(std::string path, MODE mode = READWRITE);
    unsigned char* Read(size_t sz, unsigned int& bytes_read);
    void Write(void* data, size_t sz);
    void Write(std::string data);
    void Seek(unsigned int dist, SEEKFROM from = BEGIN);
    void Close();
    size_t Size() { return sz; }
protected:
    struct Buffer
    {
        Buffer() : sz(0){}
        void Alloc(size_t sz)
        {
            data = (unsigned char*)malloc(sz);
            this->sz = sz;
        }
        void Free()
        {
            free(data);
            this->sz = 0;
        }
        unsigned char* data;
        size_t sz;
    };
    Buffer readBuffer;

    HANDLE file;
    size_t sz;
};

#endif