/*
* A copy of the Vec3b from the OpenSceneGraph library
*/

#ifndef FL_VEC3B
#define FL_VEC3B 1

/** General purpose float triple.
  * Uses include representation of color coordinates.
  * No support yet added for float * Vec3b - is it necessary?
  * Need to define a non-member non-friend operator*  etc.
  * Vec3b * float is okay
*/
class Vec3b
{
    public:

        /** Data type of vector components.*/
        typedef unsigned char value_type;

        /** Number of vector components. */
        enum { num_components = 3 };
        
        value_type _v[3];

        /** Constructor that sets all components of the vector to zero */
        Vec3b() { _v[0]=0; _v[1]=0; _v[2]=0; }
        
        Vec3b(value_type r, value_type g, value_type b) { _v[0]=r; _v[1]=g; _v[2]=b;  }

        inline bool operator == (const Vec3b& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2]; }

        inline bool operator != (const Vec3b& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2]; }

        inline bool operator <  (const Vec3b& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else return (_v[2]<v._v[2]);
        }

        inline value_type* ptr() { return _v; }
        inline const value_type* ptr() const { return _v; }

        inline void set(value_type r, value_type g, value_type b)
        {
            _v[0]=r; _v[1]=g; _v[2]=b;
        }

        inline void set( const Vec3b& rhs)
        {
            _v[0]=rhs._v[0]; _v[1]=rhs._v[1]; _v[2]=rhs._v[2];
        }

        inline value_type& operator [] (unsigned int i) { return _v[i]; }
        inline value_type operator [] (unsigned int i) const { return _v[i]; }

        inline value_type& x() { return _v[0]; }
        inline value_type& y() { return _v[1]; }
        inline value_type& z() { return _v[2]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }

        inline value_type& r() { return _v[0]; }
        inline value_type& g() { return _v[1]; }
        inline value_type& b() { return _v[2]; }

        inline value_type r() const { return _v[0]; }
        inline value_type g() const { return _v[1]; }
        inline value_type b() const { return _v[2]; }

        /** Multiply by scalar. */
        inline Vec3b operator * (float rhs) const
        {
            Vec3b col(*this);
            col *= rhs;
            return col;
        }

        /** Unary multiply by scalar. */
        inline Vec3b& operator *= (float rhs)
        {
            _v[0]=(value_type)((float)_v[0]*rhs);
            _v[1]=(value_type)((float)_v[1]*rhs);
            _v[2]=(value_type)((float)_v[2]*rhs);
            return *this;
        }

        /** Divide by scalar. */
        inline Vec3b operator / (float rhs) const
        {
            Vec3b col(*this);
            col /= rhs;
            return col;
        }

        /** Unary divide by scalar. */
        inline Vec3b& operator /= (float rhs)
        {
            float div = 1.0f/rhs;
            *this *= div;
            return *this;
        }

        /** Binary vector add. */
        inline Vec3b operator + (const Vec3b& rhs) const
        {
            return Vec3b(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
                        _v[2]+rhs._v[2]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
          * intermediate object.
        */
        inline Vec3b& operator += (const Vec3b& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            return *this;
        }

        /** Binary vector subtract. */
        inline Vec3b operator - (const Vec3b& rhs) const
        {
            return Vec3b(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
                        _v[2]-rhs._v[2]);
        }

        /** Unary vector subtract. */
        inline Vec3b& operator -= (const Vec3b& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            return *this;
        }

};    // end of class Vec3b



#endif
