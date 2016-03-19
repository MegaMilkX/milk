#ifndef _R3DDATA_H_
#define _R3DDATA_H_

#include <vector>

#include "filesystem\file.h"

#define R3D_POSITION 100
#define R3D_NORMAL 200
#define R3D_TANGENT 300
#define R3D_BITANGENT 400
#define R3D_UV 500
#define R3D_COLOR 600
#define R3D_BONE 700
#define R3D_WEIGHT 800
#define R3D_INDEX 900

#define R3D_UNSIGNED_BYTE 1
#define R3D_BYTE 2
#define R3D_UNSIGNED_SHORT 3
#define R3D_SHORT 4
#define R3D_UNSIGNED_INT 5
#define R3D_INT 6
#define R3D_FLOAT 7
#define R3D_DOUBLE 8

class R3DData
{
public:
    ~R3DData();
    struct Attrib
    {
        int type;
        int elemCount;
        unsigned char* data;
    };
    
    static R3DData Read(File file);
    int AttribCount();
    Attrib* GetAttrib(int i);
    
    template<typename T>
    void AddAttrib(const std::vector<T>& data, int type, int elemPerVertex);
    void Write(File file);
private:
    std::vector<Attrib> attribs;
};

template<typename T>
void R3DData::AddAttrib(const std::vector<T>& data, int type, int elemPerVertex)
{
    Attrib attrib;
    size_t buffer_len = data.size() * sizeof(T);
    attrib.data = new unsigned char[buffer_len];
    memcpy((void*)attrib.data, (void*)data.data(), buffer_len);
    attrib.type = type;
    attrib.elemCount = elemPerVertex;
    
    attribs.push_back(attrib);
}

class BufferReader
{
public:
    enum SEEKFROM
    {
        BEGIN = FILE_BEGIN,
        CURRENT = FILE_CURRENT,
        END = FILE_END
    };
    BufferReader(unsigned char* data, size_t sz);
    template<typename T>
    unsigned char* Read(size_t& bytesRead);
    void Seek(unsigned int dist, SEEKFROM seekFrom);
private:
    unsigned char* data;
    size_t size;
};

template<typename T>
unsigned char* BufferReader::Read(size_t& bytesRead)
{
    
}

#endif
