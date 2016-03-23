#ifndef _R3D_H_
#define _R3D_H_

#include <vector>

class R3DAttrib
{
public:
	virtual ~R3DAttrib(){}
};

class R3DPosition : public R3DAttrib
{
};

class R3DData
{
public:
	bool Read(File file);
	bool Write(File file);
	
	template<typename T>
	void PushAttribute(R3DAttr* data);
	template<typename T>
	T GetAttribute(int id = 0);
private:
	std::vector<R3DAttrib*> attributes;
};

#endif