#ifndef FL_RAY
#define FL_RAY

#include "Vec3.h"
#include "Vec3d.h"

template<typename VT>
class RayImpl
{
public:
	typedef VT vec_type;
	typedef typename VT::value_type value_type;

	vec_type _origin;
	vec_type _direction;

	Ray() {}
	Ray(const vec_type&, const vec_type&);

	vec_type origin() {return _origin;}
	vec_type direction() {return _direction;}

	vec_type parameter(value_type t);

	bool planeIntersectParameter(vec_type &N, vec_type &p, double &t);

	void normalize();

};

typedef RayImpl<Vec3f> Rayf;
typedef RayImpl<Vec3d> Rayd;

typedef Rayd Ray;
#endif