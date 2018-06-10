#pragma once
#include "Vec2.h"
namespace pallas
{
    template<typename T>
    class Vec3
    {
    public:
        T _v[3];

        /** Constructor that sets all components of the vector to zero */
        Vec3() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; }

        inline Vec3(const Vec3& vec) { _v[0] = vec._v[0]; _v[1] = vec._v[1]; _v[2] = vec._v[2]; }

        template<typename CAST_T>
        inline operator Vec3<CAST_T>() const { return Vec3<CAST_T>(static_cast<CAST_T>(_v[0]), static_cast<CAST_T>(_v[1]), static_cast<CAST_T>(_v[2])); }

        Vec3(T x, T y, T z) { _v[0] = x; _v[1] = y; _v[2] = z; }

        template<typename RES_T>
        Vec3(const Vec2<RES_T>& v2, T zz)
        {
            _v[0] = v2[0];
            _v[1] = v2[1];
            _v[2] = zz;
        }

        inline bool operator == (const Vec3& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2]; }

        inline bool operator != (const Vec3& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2]; }

        inline bool operator <  (const Vec3& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else return (_v[2]<v._v[2]);
        }

        inline T* ptr() { return _v; }
        inline const T* ptr() const { return _v; }

        inline void set(T x, T y, T z)
        {
            _v[0] = x; _v[1] = y; _v[2] = z;
        }

        inline void set(const Vec3& rhs)
        {
            _v[0] = rhs._v[0]; _v[1] = rhs._v[1]; _v[2] = rhs._v[2];
        }

        inline T& operator [] (int i) { return _v[i]; }
        inline T operator [] (int i) const { return _v[i]; }

        inline T& x() { return _v[0]; }
        inline T& y() { return _v[1]; }
        inline T& z() { return _v[2]; }

        inline T x() const { return _v[0]; }
        inline T y() const { return _v[1]; }
        inline T z() const { return _v[2]; }
        inline Vec2<T> xy() const { return Vec2<T>(_v[0], _v[1]); }
        inline Vec2<T> yz() const { return Vec2<T>(_v[1], _v[2]); }
        inline Vec2<T> xz() const { return Vec3<T>(_v[0], _v[2]); }

        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]) || osg::isNaN(_v[2]); }

        template<typename RES_T = T>
        inline RES_T operator * (const Vec3& rhs) const
        {
            return RES_T(_v[0] * rhs._v[0]) + RES_T(_v[1] * rhs._v[1]) + RES_T(_v[2] * rhs._v[2]);
        }

        template<typename RES_T = T>
        inline const Vec3<RES_T> operator ^ (const Vec3& rhs) const
        {
            return Vec3<RES_T>(RES_T(_v[1] * rhs._v[2]) - RES_T(_v[2] * rhs._v[1]),
                RES_T(_v[2] * rhs._v[0]) - RES_T(_v[0] * rhs._v[2]),
                RES_T(_v[0] * rhs._v[1]) - RES_T(_v[1] * rhs._v[0]));
        }

        template<typename RES_T = T>
        inline const Vec3<RES_T> operator * (T rhs) const
        {
            return Vec3<RES_T>(RES_T<_v[0] * rhs>, RES_T<_v[1] * rhs>, RES_T<_v[2] * rhs>);
        }

        /** Unary multiply by scalar. */
        inline Vec3& operator *= (T rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            return *this;
        }

        template<typename RES_T = T>
        inline const Vec3<RES_T> operator / (T rhs) const
        {
            return Vec3<RES_T>(RES_T(_v[0]) / rhs, RES_T(_v[1]) / rhs, RES_T(_v[2]) / rhs);
        }

        /** Unary divide by scalar. */
        inline Vec3& operator /= (T rhs)
        {
            _v[0] /= rhs;
            _v[1] /= rhs;
            _v[2] /= rhs;
            return *this;
        }

        /** Binary vector add. */
        template<typename RES_T = T>
        inline const Vec3<RES_T> operator + (const Vec3& rhs) const
        {
            return Vec3<RES_T>(_v[0] + rhs._v[0], _v[1] + rhs._v[1], _v[2] + rhs._v[2]);
        }

        /** Unary vector add. Slightly more efficient because no temporary
        * intermediate object.
        */
        inline Vec3& operator += (const Vec3& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            return *this;
        }

        /** Binary vector subtract. */
        inline const Vec3 operator - (const Vec3& rhs) const
        {
            return Vec3(_v[0] - rhs._v[0], _v[1] - rhs._v[1], _v[2] - rhs._v[2]);
        }

        /** Unary vector subtract. */
        inline Vec3& operator -= (const Vec3& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            return *this;
        }

        /** Negation operator. Returns the negative of the Vec3d. */
        inline const Vec3 operator - () const
        {
            return Vec3(-_v[0], -_v[1], -_v[2]);
        }

        template<typename RES_T = T>
        inline RES_T length() const
        {
            return sqrt(RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]) + RES_T(_v[2] * _v[2]));
        }

        template<typename RES_T = T>
        inline RES_T length2() const
        {
            return RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]) + RES_T(_v[2] * _v[2]);
        }

        template<typename RES_T = T>
        inline RES_T normalize()
        {
            RES_T norm = Vec3::length<RES_T>();
            if (norm>0.0)
            {
                double inv = 1.0 / norm;
                _v[0] *= inv;
                _v[1] *= inv;
                _v[2] *= inv;
            }
            return(norm);
        }

    };

    template<typename T>
    inline Vec3<T> componentMultiply(const Vec3<T>& lhs, const Vec3<T>& rhs)
    {
        return Vec3<T>(lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]);
    }

    template<typename T>
    inline Vec3<T> componentDivide(const Vec3<T>& lhs, const Vec3<T>& rhs)
    {
        return Vec3<T>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]);
    }

    typedef Vec3<float> Vec3f;
    typedef Vec3<double> Vec3d;
    typedef Vec3<int> Vec3i;
    typedef Vec3<unsigned int> Vec3ui;
    typedef Vec3<short> Vec3s;
    typedef Vec3<unsigned short> Vec3us;
	typedef Vec3<char> Vec3b;
	typedef Vec3<unsigned char> Vec3ub;
}