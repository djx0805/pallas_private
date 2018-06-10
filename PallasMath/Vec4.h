#pragma once
#include "Vec3.h"
namespace pallas
{
    template<typename T>
    class Vec4
    {
    public:
        T _v[4];

        /** Constructor that sets all components of the vector to zero */
        Vec4() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; _v[3] = 0.0; }

        Vec4(T x, T y, T z, T w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        template<typename RES_T>
        Vec4(const Vec3<RES_T>& v3, T w)
        {
            _v[0] = v3[0];
            _v[1] = v3[1];
            _v[2] = v3[2];
            _v[3] = w;
        }

        inline Vec4(const Vec4& vec) { _v[0] = vec._v[0]; _v[1] = vec._v[1]; _v[2] = vec._v[2]; _v[3] = vec._v[3]; }

        template<typename CAST_T>
        inline operator Vec4<CAST_T>() const { return Vec4<CAST_T>(static_cast<CAST_T>(_v[0]), static_cast<CAST_T>(_v[1]), static_cast<CAST_T>(_v[2]), static_cast<CAST_T>(_v[3])); }


        inline bool operator == (const Vec4& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2] && _v[3] == v._v[3]; }

        inline bool operator != (const Vec4& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2] || _v[3] != v._v[3]; }

        inline bool operator <  (const Vec4& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        inline T* ptr() { return _v; }
        inline const T* ptr() const { return _v; }

        inline void set(T x, T y, T z, T w)
        {
            _v[0] = x; _v[1] = y; _v[2] = z; _v[3] = w;
        }

        inline T& operator [] (unsigned int i) { return _v[i]; }
        inline T  operator [] (unsigned int i) const { return _v[i]; }

        inline T& x() { return _v[0]; }
        inline T& y() { return _v[1]; }
        inline T& z() { return _v[2]; }
        inline T& w() { return _v[3]; }

        inline T x() const { return _v[0]; }
        inline T y() const { return _v[1]; }
        inline T z() const { return _v[2]; }
        inline T w() const { return _v[3]; }
        inline Vec2<T> xy() const { return Vec2<T>(_v[0], _v[1]); }
        inline Vec2<T> yz() const { return Vec2<T>(_v[1], _v[2]); }
        inline Vec2<T> xz() const { return Vec3<T>(_v[0], _v[2]); }
        inline Vec3<T> xyz() const { return Vec3<T>(_v[0], _v[1], _v[2]); }

        inline T& r() { return _v[0]; }
        inline T& g() { return _v[1]; }
        inline T& b() { return _v[2]; }
        inline T& a() { return _v[3]; }

        inline T r() const { return _v[0]; }
        inline T g() const { return _v[1]; }
        inline T b() const { return _v[2]; }
        inline T a() const { return _v[3]; }
        inline Vec2<T> rg() const { return Vec2<T>(_v[0], _v[1]); }
        inline Vec2<T> gb() const { return Vec2<T>(_v[1], _v[2]); }
        inline Vec2<T> rb() const { return Vec3<T>(_v[0], _v[2]); }
        inline Vec3<T> rgb() const { return Vec3<T>(_v[0], _v[1], _v[2]); }
        


        inline unsigned int asABGR() const
        {
            return (unsigned int)clampTo((_v[0] * 255.0), 0.0, 255.0) << 24 |
                (unsigned int)clampTo((_v[1] * 255.0), 0.0, 255.0) << 16 |
                (unsigned int)clampTo((_v[2] * 255.0), 0.0, 255.0) << 8 |
                (unsigned int)clampTo((_v[3] * 255.0), 0.0, 255.0);
        }

        inline unsigned int asRGBA() const
        {
            return (unsigned int)clampTo((_v[3] * 255.0), 0.0, 255.0) << 24 |
                (unsigned int)clampTo((_v[2] * 255.0), 0.0, 255.0) << 16 |
                (unsigned int)clampTo((_v[1] * 255.0), 0.0, 255.0) << 8 |
                (unsigned int)clampTo((_v[0] * 255.0), 0.0, 255.0);
        }

        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]) || osg::isNaN(_v[2]) || osg::isNaN(_v[3]); }

        template<typename RES_T = T>
        inline RES_T operator * (const Vec4& rhs) const
        {
            return RES_T(_v[0] * rhs._v[0]) +
                RES_T(_v[1] * rhs._v[1]) +
                RES_T(_v[2] * rhs._v[2]) +
                RES_T(_v[3] * rhs._v[3]);
        }

        template<typename RES_T = T>
        inline Vec4<RES_T> operator * (T rhs) const
        {
            return Vec4<RES_T>(RES_T(_v[0] * rhs), RES_T(_v[1] * rhs), RES_T(_v[2] * rhs), RES_T(_v[3] * rhs));
        }

        /** Unary multiply by scalar. */
        inline Vec4& operator *= (T rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            _v[3] *= rhs;
            return *this;
        }

        template<typename RES_T = T>
        inline Vec4<RES_T> operator / (T rhs) const
        {
            return Vec4(RES_T(_v[0]) / rhs, _v[1] / rhs, RES_T(_v[2]) / rhs, RES_T(_v[3]) / rhs);
        }

        /** Unary divide by scalar. */
        inline Vec4& operator /= (T rhs)
        {
            _v[0] /= rhs;
            _v[1] /= rhs;
            _v[2] /= rhs;
            _v[3] /= rhs;
            return *this;
        }

        template<typename RES_T = T>
        inline Vec4<RES_T> operator + (const Vec4& rhs) const
        {
            return Vec4<RES_T>(_v[0] + rhs._v[0], _v[1] + rhs._v[1],
                _v[2] + rhs._v[2], _v[3] + rhs._v[3]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
        * intermediate object.
        */
        inline Vec4& operator += (const Vec4& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;
        }

        /** Binary vector subtract. */
        inline Vec4 operator - (const Vec4& rhs) const
        {
            return Vec4(_v[0] - rhs._v[0], _v[1] - rhs._v[1],
                _v[2] - rhs._v[2], _v[3] - rhs._v[3]);
        }

        /** Unary vector subtract. */
        inline Vec4& operator -= (const Vec4& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            _v[3] -= rhs._v[3];
            return *this;
        }

        /** Negation operator. Returns the negative of the Vec4. */
        inline const Vec4 operator - () const
        {
            return Vec4(-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        template<typename RES_T = T>
        inline RES_T length() const
        {
            return sqrt(RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]) + RES_T(_v[2] * _v[2]) + RES_T(_v[3] * _v[3]));
        }

        template<typename RES_T = T>
        inline RES_T length2() const
        {
            return RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]) + RES_T(_v[2] * _v[2]) + RES_T(_v[3] * _v[3]);
        }

        template<typename RES_T = T>
        inline T normalize()
        {
            RES_T norm = Vec4::length<RES_T>();
            if (norm>0.0f)
            {
                double inv = 1.0 / norm;
                _v[0] *= inv;
                _v[1] *= inv;
                _v[2] *= inv;
                _v[3] *= inv;
            }
            return(norm);
        }

    }; 


    template<typename T>
    inline Vec4<T> componentMultiply(const Vec4<T>& lhs, const Vec4<T>& rhs)
    {
        return Vec4<T>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2], lhs[3] * rhs[3]);
    }

    template<typename T>
    inline Vec4<T> componentDivide(const Vec4<T>& lhs, const Vec4<T>& rhs)
    {
        return Vec4<T>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3]);
    }

    typedef Vec4<float> Vec4f;
    typedef Vec4<double> Vec4d;
    typedef Vec4<int> Vec4i;
    typedef Vec4<unsigned int> Vec4ui;
    typedef Vec4<short> Vec4s;
    typedef Vec4<unsigned short> Vec4us;
	typedef Vec4<char> Vec4b;
	typedef Vec4<unsigned char> Vec4ub;
}