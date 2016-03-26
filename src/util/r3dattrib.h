#ifndef _R3DATTRIB_H_
#define _R3DATTRIB_H_

#include <vector>

#define R3D_POSITION 100
#define R3D_NORMAL 200
#define R3D_TANGENT 300
#define R3D_BITANGENT 400
#define R3D_UV 500
#define R3D_COLOR 600
#define R3D_BONE 700
#define R3D_WEIGHT 800
#define R3D_INDEX 900

class IR3DAttrib
{
public:
    virtual ~IR3DAttrib(){}
};

template<int TYPE_INDEX, typename ELEM_TYPE, int ELEM_COUNT>
class R3DAttrib : public IR3DAttrib, public std::vector<ELEM_TYPE>
{
public:
    R3DAttrib& operator<<(const ELEM_TYPE value)
    {
        push_back(value);
        return (*this);
    }
    static int type_index(){ return TYPE_INDEX; }
private:
};

class R3DPosition : public R3DAttrib<R3D_POSITION, float, 3>
{
};

#endif