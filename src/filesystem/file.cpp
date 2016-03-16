#include "file.h"

File File::Create(std::string path, File::MODE mode)
{
    OFSTRUCT ofstruct;
    File file;
    file.file = (HANDLE)OpenFile(path.c_str(), &ofstruct, OF_CREATE | mode);
    DWORD dwFileSizeHigh = 0;
    DWORD dwFileSizeLow = GetFileSize(file.file, &dwFileSizeHigh);
    file.sz = dwFileSizeLow | (__int64)dwFileSizeHigh << 32;
    return file;
}

File File::Open(std::string path, File::MODE mode)
{
    OFSTRUCT ofstruct;
    File file;
    file.file = (HANDLE)OpenFile(path.c_str(), &ofstruct, mode);
    DWORD dwFileSizeHigh = 0;
    DWORD dwFileSizeLow = GetFileSize(file.file, &dwFileSizeHigh);
    file.sz = dwFileSizeLow | (__int64)dwFileSizeHigh << 32;
    return file;
}

unsigned char* File::Read(size_t sz, unsigned int& bytes_read)
{
    if (readBuffer.sz != 0)
    {
        if (readBuffer.sz < sz)
        {
            readBuffer.Free();
            readBuffer.Alloc(sz);
        }
    }
    else
    {
        readBuffer.Alloc(sz);
    }

    memset(readBuffer.data, 0, sizeof(readBuffer.sz));

    DWORD dwBytesRead = 0;
    if (!ReadFile(file, readBuffer.data, sz, &dwBytesRead, NULL))
    {
        return 0;
    }
    bytes_read = dwBytesRead;
    return readBuffer.data;
}

void File::Write(void* data, size_t sz)
{
    DWORD dwBytesWritten;
    WriteFile(file, data, sz, &dwBytesWritten, NULL);
}

void File::Seek(unsigned int dist, SEEKFROM from)
{
    LARGE_INTEGER large_int;
    large_int.QuadPart = dist;
    SetFilePointerEx(file, large_int, NULL, from);
}

void File::Close()
{
    CloseHandle((HANDLE)file);
}