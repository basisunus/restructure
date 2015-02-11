#ifndef FL_OBJECTFACTORY
#define FL_OBJECTFACTORY

#include "Referenced.h"
#include "ref_ptr.h"
#include "tinyxml2/tinyxml2.h"

class ObjectFactory : public Referenced
{
public:
	ObjectFactory();

	virtual const char* className() const {return "ObjectFactory"; }

	virtual Object* build();

protected:
	virtual ~ObjectFactory();
};

#endif