#ifndef _RESOURCEOBJECT_H_
#define _RESOURCEOBJECT_H_

class ResourceObject
{
public:
    virtual ResourceObject(){}
    virtual int ReaderCount() = 0;
    virtual std::string GetReaderExtension(int id) = 0;
private:
};

#endif