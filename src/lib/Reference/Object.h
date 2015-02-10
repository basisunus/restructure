#ifndef FL_OBJECT
#define FL_OBJECT 1

#include "Referenced.h"
#include "ref_ptr.h"
#include "Observer.h"
#include "Value.h"
#include <string>
#include <stack>
//#include "tinyxml2/tinyxml2.h"

class Vec2f;
class Vec3f;
class Vec4f;
class Vec2d;
class Vec3d;
class Vec4d;
class Quat;
class Planef;
class Planed;
class Matrixf;
class Matrixd;
class Color3f;
class Color3d;
class HsvColor3f;
class HsvColor3d;

typedef std::stack<ref_ptr<ValueSet> > ValueSetStack;

class Object : public Referenced, public Observer
{
public:

	Object();

	Object(const Object& obj, bool ref_copy=false);

	virtual Object* clone() const {return new Object(*this);};

	virtual bool isSameKindAs(const Object*) const {return true;}

	virtual const char* className() const { return "Object"; };

	inline void setId( const unsigned int id ) { _id = id; }

	inline const unsigned int getId() const { return _id; }

	virtual void objectDeleted(void*);
	virtual void objectChanged(void*, const std::string &exp);

	//add a value
	virtual bool addValue(const std::string &name, Referenced* value);
	virtual bool addValue(const std::string &name, bool value);
	virtual bool addValue(const std::string &name, char value);
	virtual bool addValue(const std::string &name, unsigned char value);
	virtual bool addValue(const std::string &name, short value);
	virtual bool addValue(const std::string &name, unsigned short value);
	virtual bool addValue(const std::string &name, long value);
	virtual bool addValue(const std::string &name, unsigned long value);
	virtual bool addValue(const std::string &name, long long value);
	virtual bool addValue(const std::string &name, unsigned long long value);
	virtual bool addValue(const std::string &name, float);
	virtual bool addValue(const std::string &name, double);
	virtual bool addValue(const std::string &name, const std::string &value);
	virtual bool addValue(const std::string &name, const Vec2f &value);
	virtual bool addValue(const std::string &name, const Vec3f &value);
	virtual bool addValue(const std::string &name, const Vec4f &value);
	virtual bool addValue(const std::string &name, const Vec2d &value);
	virtual bool addValue(const std::string &name, const Vec3d &value);
	virtual bool addValue(const std::string &name, const Vec4d &value);
	virtual bool addValue(const std::string &name, const Quat &value);
	virtual bool addValue(const std::string &name, const Planef &value);
	virtual bool addValue(const std::string &name, const Planed &value);
	virtual bool addValue(const std::string &name, const Matrixf &value);
	virtual bool addValue(const std::string &name, const Matrixd &value);
	virtual bool addValue(const std::string &name, const Color3f &value);
	virtual bool addValue(const std::string &name, const Color3d &value);
	virtual bool addValue(const std::string &name, const HsvColor3f &value);
	virtual bool addValue(const std::string &name, const HsvColor3d &value);
	virtual bool addValue(const std::string &name, const ValueSet &value);

	/** All the set value functions */
	virtual bool setValue(const std::string &name, Referenced* value);
	virtual bool setValue(const std::string &name, bool value);
	virtual bool setValue(const std::string &name, char value);
	virtual bool setValue(const std::string &name, unsigned char value);
	virtual bool setValue(const std::string &name, short value);
	virtual bool setValue(const std::string &name, unsigned short value);
	virtual bool setValue(const std::string &name, long value);
	virtual bool setValue(const std::string &name, unsigned long value);
	virtual bool setValue(const std::string &name, long long value);
	virtual bool setValue(const std::string &name, unsigned long long value);
	virtual bool setValue(const std::string &name, float value);
	virtual bool setValue(const std::string &name, double value);
	virtual bool setValue(const std::string &name, const std::string &value);
	virtual bool setValue(const std::string &name, const Vec2f &value);
	virtual bool setValue(const std::string &name, const Vec3f &value);
	virtual bool setValue(const std::string &name, const Vec4f &value);
	virtual bool setValue(const std::string &name, const Vec2d &value);
	virtual bool setValue(const std::string &name, const Vec3d &value);
	virtual bool setValue(const std::string &name, const Vec4d &value);
	virtual bool setValue(const std::string &name, const Quat &value);
	virtual bool setValue(const std::string &name, const Planef &value);
	virtual bool setValue(const std::string &name, const Planed &value);
	virtual bool setValue(const std::string &name, const Matrixf &value);
	virtual bool setValue(const std::string &name, const Matrixd &value);
	virtual bool setValue(const std::string &name, const Color3f &value);
	virtual bool setValue(const std::string &name, const Color3d &value);
	virtual bool setValue(const std::string &name, const HsvColor3f &value);
	virtual bool setValue(const std::string &name, const HsvColor3d &value);
	virtual bool setValue(const std::string &name, const ValueSet &value);

	/** All the get value functions */
	virtual bool getValue(const std::string &name, Referenced* value);
	virtual bool getValue(const std::string &name, bool &value);
	virtual bool getValue(const std::string &name, char &value);
	virtual bool getValue(const std::string &name, unsigned char &value);
	virtual bool getValue(const std::string &name, short &value);
	virtual bool getValue(const std::string &name, unsigned short &value);
	virtual bool getValue(const std::string &name, long &value);
	virtual bool getValue(const std::string &name, unsigned long &value);
	virtual bool getValue(const std::string &name, long long &value);
	virtual bool getValue(const std::string &name, unsigned long long &value);
	virtual bool getValue(const std::string &name, float &value);
	virtual bool getValue(const std::string &name, double &value);
	virtual bool getValue(const std::string &name, std::string &value);
	virtual bool getValue(const std::string &name, Vec2f &value);
	virtual bool getValue(const std::string &name, Vec3f &value);
	virtual bool getValue(const std::string &name, Vec4f &value);
	virtual bool getValue(const std::string &name, Vec2d &value);
	virtual bool getValue(const std::string &name, Vec3d &value);
	virtual bool getValue(const std::string &name, Vec4d &value);
	virtual bool getValue(const std::string &name, Quat &value);
	virtual bool getValue(const std::string &name, Planef &value);
	virtual bool getValue(const std::string &name, Planed &value);
	virtual bool getValue(const std::string &name, Matrixf &value);
	virtual bool getValue(const std::string &name, Matrixd &value);
	virtual bool getValue(const std::string &name, Color3f &value);
	virtual bool getValue(const std::string &name, Color3d &value);
	virtual bool getValue(const std::string &name, HsvColor3f &value);
	virtual bool getValue(const std::string &name, HsvColor3d &value);
	virtual bool getValue(const std::string &name, ValueSet &value);

	//bool buildFromXml(tinyxml2::XMLDocument &xml_doc);

protected:
	virtual ~Object();

	/** ID of an object is non-zero. */
	unsigned int _id;

	/** a stack of value sets */
	ValueSetStack _vs_stack;

private:

	Object& operator = (const Object&) {return *this; }
};

#endif
