#include "r3ddata.h"

R3DData::~R3DData()
{
    for(int i = 0; i < attribs.size(); ++i)
    {
        delete attribs[i].data;
    }
    attribs.clear();
}

R3DData R3DData::Read(File file)
{
    R3DData r3d;
    file.Seek(0, File::BEGIN);
    size_t bytesRead = 3;

    std::string header = file.Read<std::string>(bytesRead);
    
    if(header != "R3D")
        return r3d;
    
    file.Read<char>(bytesRead);
    file.Read<int>(bytesRead);
    
    while(bytesRead)
    {
        int type = file.Read<int>(bytesRead);
        int elemCount = file.Read<int>(bytesRead);
        int dataType = file.Read<int>(bytesRead);
        int count = file.Read<int>(bytesRead);
        
        size_t sz_to_read = count * elemCount * r3d_data_type_size(dataType);
        unsigned char* data = file.Read(sz_to_read, bytesRead);
        if(bytesRead > sz_to_read || bytesRead < sz_to_read)
        {
            break;
        }
        
        Attrib attrib;
        attrib.type = type;
        attrib.elemCount = elemCount;
        attrib.dataType = dataType;
        attrib.count = count;
        attrib.size = bytesRead;
        attrib.data = new unsigned char[bytesRead];
        memcpy(attrib.data, data, bytesRead);
        
        r3d.attribs.push_back(attrib);
    }
    
        
    return r3d;
}

int R3DData::AttribCount()
{
    return attribs.size();
}

R3DData::Attrib* R3DData::GetAttrib(int i)
{
    return &attribs[i];
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
