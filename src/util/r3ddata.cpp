#include "r3ddata.h"

R3DData::~R3DData()
{
    for(int i = 0; i < attribs.size(); ++i)
    {
        delete attribs[0].data;
    }
    attribs.clear();
}

R3DData R3DData::Read(File file)
{
    R3DData r3d;
    file.Seek(0, File::BEGIN);
    size_t bytesRead = 3;
    /*
    std::string file_header = file.Read<std::string>(bytesRead);
    if(file_header != "R3D")
        return r3d;
    */    
    
        
    return r3d;
}

int R3DData::AttribCount()
{
    
}

R3DData::Attrib* R3DData::GetAttrib(int i)
{
    return 0;
}

void R3DData::Write(File file)
{
    file.Seek(0, File::BEGIN);
    
    file.Write("R3D");
    file.Write("100");
    short zeroShort = 0;
    file.Write(&zeroShort, sizeof(short));
    
    for(int i = 0; i < attribs.size(); ++i)
    {
        file.Write(&attribs[i].type, sizeof(attribs[i].type));
        file.Write(&attribs[i].elemCount, sizeof(attribs[i].elemCount));
        file.Write(&attribs[i].dataType, sizeof(attribs[i].dataType));
        file.Write(&attribs[i].count, sizeof(attribs[i].count));
        file.Write(attribs[i].data, attribs[i].size);
    }
}
