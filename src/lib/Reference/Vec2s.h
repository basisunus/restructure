/*
* A copy of the Vec2s from the OpenSceneGraph library
*/

#ifndef FL_VEC2S
#define FL_VEC2S 1

class Vec2s
{
    public:

        /** Data type of vector components.*/
        typedef unsigned short value_type;

        /** Number of vector components. */
        enum { num_components = 2 };
        
        value_type _v[2];

        /** Constructor that sets all components of the vector to zero */
        Vec2s() { _v[0]=0; _v[1]=0; }

        Vec2s(value_type x, value_type y) { _v[0] = x; _v[1] = y; }

        inline bool operator == (const Vec2s& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1]; }
        inline bool operator != (const Vec2s& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1]; }
        inline bool operator <  (const Vec2s& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else return (_v[1]<v._v[1]);
        }

        inline value_type* ptr() { return _v; }
        inline const value_type* ptr() const { return _v; }

        inline void set( value_type x, value_type y)
        {
            _v[0]=x; _v[1]=y;
        }

        inline void set( const Vec2s& rhs)
        {
            _v[0]=rhs._v[0]; _v[1]=rhs._v[1];
        }

        inline value_type& operator [] (int i) { return _v[i]; }
        inline value_type operator [] (int i) const { return _v[i]; }

        inline value_type& x() { return _v[0]; }
        inline value_type& y() { return _v[1]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }

        inline value_type& r() { return _v[0]; }
        inline value_type& g() { return _v[1]; }

        inline value_type r() const { return _v[0]; }
        inline value_type g() const { return _v[1]; }

        inline Vec2s operator * (value_type rhs) const
        {
            return Vec2s(_v[0]*rhs, _v[1]*rhs);
        }

        inline Vec2s& operator *= (value_type rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            return *this;
        }

        inline Vec2s operator / (value_type rhs) const
        {
            return Vec2s(_v[0]/rhs, _v[1]/rhs);
        }

        inline Vec2s& operator /= (value_type rhs)
        {
            _v[0]/=rhs;
            _v[1]/=rhs;
            return *this;
        }
        
        inline Vec2s operator * (const Vec2s& rhs) const
        {
            return Vec2s(_v[0]*rhs._v[0], _v[1]*rhs._v[1]);
        }
        
        inline Vec2s operator + (const Vec2s& rhs) const
        {
            return Vec2s(_v[0]+rhs._v[0], _v[1]+rhs._v[1]);
        }

        inline Vec2s& operator += (const Vec2s& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            return *this;
        }

        inline Vec2s operator - (const Vec2s& rhs) const
        {
            return Vec2s(_v[0]-rhs._v[0], _v[1]-rhs._v[1]);
        }

        inline Vec2s& operator -= (const Vec2s& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            return *this;
        }


        inline Vec2s operator - () const
        {
            return Vec2s (-_v[0], -_v[1]);
        }
        

};    // end of class Vec2s


/** multiply by vector components. */
inline Vec2s componentMultiply(const Vec2s& lhs, const Vec2s& rhs)
{
    return Vec2s(lhs[0]*rhs[0], lhs[1]*rhs[1]);
}

/** divide rhs components by rhs vector components. */
inline Vec2s componentDivide(const Vec2s& lhs, const Vec2s& rhs)
{
    return Vec2s(lhs[0]/rhs[0], lhs[1]/rhs[1]);
}

#endif
