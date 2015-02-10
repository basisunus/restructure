/*
* A copy of the Plane from the OpenSceneGraph library
*/

#ifndef FL_PLANED
#define FL_PLANED 1

#include "Vec3.h"
#include "Vec4.h"
#include "Matrix.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"

/** @brief A plane class. It can be used to represent an infinite plane.
  * 
  * The infinite plane is described by an implicit plane equation a*x+b*y+c*z+d = 0. Though it is not mandatory that
  * a^2+b^2+c^2 = 1 is fulfilled in general some methods require it (@see osg::Plane::distance). */
class Planed
{

    public:

        /** Type of Plane class.*/
        typedef double value_type;
        typedef Vec3d vec_type;

        /** Number of vector components. */
        enum { num_components = 3 };


        /// Default constructor
        /** The default constructor initializes all values to zero.
          * @warning Although the method osg::Plane::valid() will return true after the default constructors call the plane
          *          is mathematically invalid! Default data do not describe a valid plane. */
        inline Planed() { _fv[0]=0.0; _fv[1]=0.0; _fv[2]=0.0; _fv[3]=0.0; _lowerBBCorner = 0; _upperBBCorner = 0; }
        inline Planed(const Planed& pl) { set(pl); }
        /// Constructor
        /** The plane is described as a*x+b*y+c*z+d = 0.
          * @remark You may call osg::Plane::MakeUnitLength afterwards if the passed values are not normalized. */
        inline Planed(value_type a,value_type b,value_type c,value_type d) { set(a,b,c,d); }

        /// Constructor
        /** The plane can also be described as vec*[x,y,z,1].
          * @remark You may call osg::Plane::MakeUnitLength afterwards if the passed values are not normalized. */
        inline Planed(const Vec4f& vec) { set(vec); }
        /// Constructor
        /** The plane can also be described as vec*[x,y,z,1].
          * @remark You may call osg::Plane::MakeUnitLength afterwards if the passed values are not normalized. */
        inline Planed(const Vec4d& vec) { set(vec); }

        /// Constructor
        /** This constructor initializes the internal values directly without any checking or manipulation.
          * @param norm The normal of the plane.
          * @param d    The negative distance from the point of origin to the plane.
          * @remark You may call osg::Plane::MakeUnitLength afterwards if the passed normal was not normalized. */
        inline Planed(const vec_type& norm,value_type d) { set(norm,d); }

        /// Constructor
        /** This constructor calculates from the three points describing an infinite plane the internal values.
          * @param v1 Point in the plane.
          * @param v2 Point in the plane.
          * @param v3 Point in the plane.
          * @remark After this constructor call the plane's normal is normalized in case the three points described a mathematically
          *         valid plane.
          * @remark The normal is determined by building the cross product of (v2-v1) ^ (v3-v2). */
        inline Planed(const vec_type& v1, const vec_type& v2, const vec_type& v3) { set(v1,v2,v3); }

        /// Constructor
        /** This constructor initializes the internal values directly without any checking or manipulation.
          * @param norm  The normal of the plane.
          * @param point A point of the plane.
          * @remark You may call osg::Plane::MakeUnitLength afterwards if the passed normal was not normalized. */
        inline Planed(const vec_type& norm, const vec_type& point) { set(norm,point); }

        inline Planed& operator = (const Planed& pl)
        {
            if (&pl==this) return *this;
            set(pl);
            return *this;
        }

        inline void set(const Planed& pl) { _fv[0]=pl._fv[0]; _fv[1]=pl._fv[1]; _fv[2]=pl._fv[2]; _fv[3]=pl._fv[3]; calculateUpperLowerBBCorners(); }
        inline void set(value_type a, value_type b, value_type c, value_type d) { _fv[0]=a; _fv[1]=b; _fv[2]=c; _fv[3]=d; calculateUpperLowerBBCorners(); }

        inline void set(const Vec4f& vec) { set(vec[0],vec[1],vec[2],vec[3]); }
        inline void set(const Vec4d& vec) { set(vec[0],vec[1],vec[2],vec[3]); }

        inline void set(const vec_type& norm, double d) { set(norm[0],norm[1],norm[2],d); }

        inline void set(const vec_type& v1, const vec_type& v2, const vec_type& v3)
        {
            vec_type norm = (v2-v1)^(v3-v2);
            value_type length = norm.length();
            if (length>1e-6) norm/= length;
            else norm.set(0.0,0.0,0.0);
            set(norm[0],norm[1],norm[2],-(v1*norm));
        }

        inline void set(const vec_type& norm, const vec_type& point)
        {
            value_type d = -norm[0]*point[0] - norm[1]*point[1] - norm[2]*point[2];
            set(norm[0],norm[1],norm[2],d);
        }

        /** flip/reverse the orientation of the plane.*/
        inline void flip()
        {
            _fv[0] = -_fv[0];
            _fv[1] = -_fv[1];
            _fv[2] = -_fv[2];
            _fv[3] = -_fv[3];
            calculateUpperLowerBBCorners();
        }

        /** This method multiplies the coefficients of the plane equation with a constant factor so that the
          * equation a^2+b^2+c^2 = 1 holds. */
        inline void makeUnitLength()
        {
            value_type inv_length = 1.0 / sqrt(_fv[0]*_fv[0] + _fv[1]*_fv[1]+ _fv[2]*_fv[2]);
            _fv[0] *= inv_length;
            _fv[1] *= inv_length;
            _fv[2] *= inv_length;
            _fv[3] *= inv_length;
        }

        /** calculate the upper and lower bounding box corners to be used
          * in the intersect(BoundingBox&) method for speeding calculations.*/
        inline void calculateUpperLowerBBCorners()
        {
            _upperBBCorner = (_fv[0]>=0.0?1:0) |
                             (_fv[1]>=0.0?2:0) |
                             (_fv[2]>=0.0?4:0);

            _lowerBBCorner = (~_upperBBCorner)&7;

        }

        /// Checks if all internal values describing the plane have valid numbers
        /** @warning This method does not check if the plane is mathematically correctly described!
          * @remark  The only case where all elements have valid numbers and the plane description is invalid occurs if the plane's normal
          *          is zero. */
        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const { return ::isNaN(_fv[0]) || ::isNaN(_fv[1]) || ::isNaN(_fv[2]) || ::isNaN(_fv[3]); }

        inline bool operator == (const Planed& plane) const { return _fv[0]==plane._fv[0] && _fv[1]==plane._fv[1] && _fv[2]==plane._fv[2] && _fv[3]==plane._fv[3]; }

        inline bool operator != (const Planed& plane) const { return _fv[0]!=plane._fv[0] || _fv[1]!=plane._fv[1] || _fv[2]!=plane._fv[2] || _fv[3]!=plane._fv[3]; }

        /** A plane is said to be smaller than another plane if the first non-identical element of the internal array is smaller than the
          * corresponding element of the other plane. */
        inline bool operator <  (const Planed& plane) const
        {
            if (_fv[0]<plane._fv[0]) return true;
            else if (_fv[0]>plane._fv[0]) return false;
            else if (_fv[1]<plane._fv[1]) return true;
            else if (_fv[1]>plane._fv[1]) return false;
            else if (_fv[2]<plane._fv[2]) return true;
            else if (_fv[2]>plane._fv[2]) return false;
            else return (_fv[3]<plane._fv[3]);
        }


        inline value_type* ptr() { return _fv; }
        inline const value_type* ptr() const { return _fv; }

        //inline Vec4_type asVec4() const { return Vec4_type(_fv[0],_fv[1],_fv[2],_fv[3]); }

        inline value_type& operator [] (unsigned int i) { return _fv[i]; }
        inline value_type operator [] (unsigned int i) const { return _fv[i]; }


        inline vec_type getNormal() const { return vec_type(_fv[0],_fv[1],_fv[2]); }
      
        /** Calculate the distance between a point and the plane.
          * @remark This method only leads to real distance values if the plane's norm is 1.
          * @sa osg::Plane::makeUnitLength */
        inline double distance(const Vec3f& v) const
        {
            return _fv[0]*v.x()+
                   _fv[1]*v.y()+
                   _fv[2]*v.z()+
                   _fv[3];
        }
        /** Calculate the distance between a point and the plane.
          * @remark This method only leads to real distance values if the plane's norm is 1.
          * @sa osg::Plane::makeUnitLength */
        inline double distance(const Vec3d& v) const
        {
            return _fv[0]*v.x()+
                   _fv[1]*v.y()+
                   _fv[2]*v.z()+
                   _fv[3];
        }

        /** calculate the dot product of the plane normal and a point.*/
        inline double dotProductNormal(const Vec3f& v) const
        {
            return _fv[0]*v.x()+
                   _fv[1]*v.y()+
                   _fv[2]*v.z();
        }

        /** calculate the dot product of the plane normal and a point.*/
        inline double dotProductNormal(const Vec3d& v) const
        {
            return _fv[0]*v.x()+
                   _fv[1]*v.y()+
                   _fv[2]*v.z();
        }

        /** intersection test between plane and vertex list
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline int intersect(const std::vector<Vec3f>& vertices) const
        {
            if (vertices.empty()) return -1;

            int noAbove = 0;
            int noBelow = 0;
            int noOn = 0;
            for(std::vector<Vec3f>::const_iterator itr=vertices.begin();
                itr != vertices.end();
                ++itr)
            {
                double d = distance(*itr);
                if (d>0.0f) ++noAbove;
                else if (d<0.0f) ++noBelow;
                else ++noOn;
            }

            if (noAbove>0)
            {
                if (noBelow>0) return 0;
                else return 1;
            }
            return -1; // treat points on line as outside...
        }

        /** intersection test between plane and vertex list
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline int intersect(const std::vector<Vec3d>& vertices) const
        {
            if (vertices.empty()) return -1;

            int noAbove = 0;
            int noBelow = 0;
            int noOn = 0;
            for(std::vector<Vec3d>::const_iterator itr=vertices.begin();
                itr != vertices.end();
                ++itr)
            {
                double d = distance(*itr);
                if (d>0.0) ++noAbove;
                else if (d<0.0) ++noBelow;
                else ++noOn;
            }

            if (noAbove>0)
            {
                if (noBelow>0) return 0;
                else return 1;
            }
            return -1; // treat points on line as outside...
        }

        /** intersection test between plane and bounding sphere.
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline int intersect(const BoundingSphere& bs) const
        {
            double d = distance(bs.center());

            if (d>bs.radius()) return 1;
            else if (d<-bs.radius()) return -1;
            else return 0;
        }


        /** intersection test between plane and bounding sphere.
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline int intersect(const BoundingBox& bb) const
        {
            // if lowest point above plane than all above.
            if (distance(bb.corner(_lowerBBCorner))>0.0f) return 1;

            // if highest point is below plane then all below.
            if (distance(bb.corner(_upperBBCorner))<0.0f) return -1;

            // d_lower<=0.0f && d_upper>=0.0f
            // therefore must be crossing plane.
            return 0;

        }

        /** Transform the plane by matrix.  Note, this operation carries out
          * the calculation of the inverse of the matrix since a plane 
          * must be multiplied by the inverse transposed to transform it. This
          * make this operation expensive.  If the inverse has been already
          * calculated elsewhere then use transformProvidingInverse() instead.
          * See http://www.worldserver.com/turk/computergraphics/NormalTransformations.pdf*/
        //inline void transform(const osg::Matrix& matrix)
        //{
        //    osg::Matrix inverse;
        //    inverse.invert(matrix);
        //    transformProvidingInverse(inverse);
        //}

        /** Transform the plane by providing a pre inverted matrix.
          * see transform for details. */
        //inline void transformProvidingInverse(const osg::Matrix& matrix)
        //{
        //    // note pre multiplications, which effectively transposes matrix.
        //    Vec4_type vec(_fv[0],_fv[1],_fv[2],_fv[3]);
        //    vec = matrix * vec;
        //    set(vec);
        //    makeUnitLength();
        //}

    protected:

        /** Vec member variable. */
        value_type _fv[4];

        // variables cached to optimize calcs against bounding boxes.
        unsigned int        _upperBBCorner;
        unsigned int        _lowerBBCorner;


};

#endif 
