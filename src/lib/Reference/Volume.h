#ifndef FL_VOLUME
#define FL_VOLUME 1

#include "Node.h"

class BaseVolume : public Node
{
public:

	BaseVolume();

	BaseVolume(const BaseVolume&);

	virtual Object* clone() const { return new BaseVolume(*this); }

	virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const BaseVolume*>(obj)!=NULL; }

	virtual const char* className() const { return "BaseVolume"; }

	virtual void traverse(); {}

protected:

	virtual ~BaseVolume();
};

#endif