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
    size_t bytesRead = 3
    std::string file_header = file.Read<std::string>(bytesRead);
    if(file_header != "R3D")
        return r3d;
        
    
        
    return r3d;
}

int R3DData::AttribCount()
{
    
}

Attrib* R3DData::GetAttrib(int i)
{
    
}

void R3DData::Write(File file)
{
    file.Seek(0, File::BEGIN);
    
    for(int i = 0; i < attribs.size(); ++i)
    {
        
    }
}