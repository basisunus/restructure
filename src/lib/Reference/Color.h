#ifndef FL_COLOR
#define FL_COLOR 1

#include "Vec3b.h"
#include "Vec3s.h"
#include "Vec3f.h"
#include "Vec3d.h"

typedef Vec3b Color3b;
typedef Vec3s Color3s;

class Color3f;
class Color3d;
class HsvColor3d;

class HsvColor3f : public Vec3f
{
public:
	HsvColor3f();
	HsvColor3f(value_type hue, value_type sat, value_type val)
		: Vec3f(hue, sat, val) {}
	HsvColor3f(const HsvColor3d&);
	HsvColor3f(const Color3b&);
	HsvColor3f(const Color3s&);
	HsvColor3f(const Color3f&);
	HsvColor3f(const Color3d&);

	operator HsvColor3d() const;
	operator Color3b() const;
	operator Color3s() const;
	operator Color3f() const;
	operator Color3d() const;

	inline value_type hue() const {return _v[0];}
	inline value_type sat() const {return _v[1];}
	inline value_type val() const {return _v[2];}
};

class HsvColor3d : public Vec3d
{
public:
	HsvColor3d();
	HsvColor3d(value_type hue, value_type sat, value_type val)
		: Vec3d(hue, sat, val) {}
	HsvColor3d(const HsvColor3f&);
	HsvColor3d(const Color3b&);
	HsvColor3d(const Color3s&);
	HsvColor3d(const Color3f&);
	HsvColor3d(const Color3d&);

	operator HsvColor3f() const {return HsvColor3f(static_cast<float>(_v[0]),
		static_cast<float>(_v[1]), static_cast<float>(_v[2]));}
	operator Color3b() const;
	operator Color3s() const;
	operator Color3f() const;
	operator Color3d() const;

	inline value_type hue() const {return _v[0];}
	inline value_type sat() const {return _v[1];}
	inline value_type val() const {return _v[2];}
};

class Color3f : public Vec3f
{
public:
	Color3f();
	Color3f(value_type r, value_type g, value_type b)
		: Vec3f(r, g, b) {}
	Color3f(const HsvColor3f&);
	Color3f(const HsvColor3d&);
	Color3f(const Color3b&);
	Color3f(const Color3s&);
	Color3f(const Color3d&);

	operator HsvColor3f() const;
	operator HsvColor3d() const;
	operator Color3b() const;
	operator Color3s() const;
	operator Color3d() const;

	inline value_type r() const {return _v[0];}
	inline value_type g() const {return _v[1];}
	inline value_type b() const {return _v[2];}
};

class Color3d : public Vec3d
{
public:
	Color3d();
	Color3d(value_type r, value_type g, value_type b)
		: Vec3d(r, g, b) {}
	Color3d(const HsvColor3f&);
	Color3d(const HsvColor3d&);
	Color3d(const Color3b&);
	Color3d(const Color3s&);
	Color3d(const Color3f&);

	operator HsvColor3f() const;
	operator HsvColor3d() const;
	operator Color3b() const;
	operator Color3s() const;
	operator Color3f() const;
};

typedef Color3d Color;

#endif