#ifndef _R3DDATA_H_
#define _R3DDATA_H_

#include <vector>
#include <string>

#include <stdint.h>

#include "..\filesystem\file.h"

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
        int dataType;
        int count;
        int size;
        unsigned char* data;
    };
    
    static R3DData Read(File file);
    int AttribCount();
    Attrib* GetAttrib(int i);
    
    template<typename T>
    void AddAttrib(const std::vector<T>& data, int type, int elemPerVertex);
    void Write(File file);
private:
    unsigned int r3d_next_id()
    {
        static unsigned int type_id = 0;
        return ++type_id;
    }

    template<typename T>
    unsigned int r3d_get_type_id()
    {
        static unsigned int id = r3d_next_id();
        return id;
    }

    template<typename T>
    unsigned int r3d_get_type_def()
    {
        unsigned int id = r3d_get_type_id<T>();
        if (id == r3d_get_type_id<unsigned char>())
            return R3D_UNSIGNED_BYTE;
        else if (id == r3d_get_type_id<char>())
            return R3D_BYTE;
        else if (id == r3d_get_type_id<uint16_t>())
            return R3D_UNSIGNED_SHORT;
        else if (id == r3d_get_type_id<int16_t>())
            return R3D_SHORT;
        else if (id == r3d_get_type_id<uint32_t>())
            return R3D_UNSIGNED_INT;
        else if (id == r3d_get_type_id<int32_t>())
            return R3D_INT;
        else if (id == r3d_get_type_id<float_t>())
            return R3D_FLOAT;
        else if (id == r3d_get_type_id<double_t>())
            return R3D_DOUBLE;
        else
            return 0;
    }
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
    attrib.dataType = r3d_get_type_def<T>();
    attrib.count = data.size() / elemPerVertex;
    attrib.size = buffer_len;
    
    attribs.push_back(attrib);
}

#endif
