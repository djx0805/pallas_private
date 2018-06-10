#pragma once
namespace pallas
{
    template<typename T>
    class Vec2
    {
    public:
        T _v[2];

        Vec2() { _v[0] = 0; _v[1] = 0; }

        Vec2(T x, T y) { _v[0] = x; _v[1] = y; }

        inline Vec2(const Vec2& vec) { _v[0] = vec._v[0]; _v[1] = vec._v[1]; }

        template<typename CAST_T>
        inline operator Vec2<CAST_T>() const { return Vec2<CAST_T>(static_cast<CAST_T>(_v[0]), static_cast<CAST_T>(_v[1])); }


        inline bool operator == (const Vec2& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1]; }

        inline bool operator != (const Vec2& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1]; }

        inline bool operator <  (const Vec2& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else return (_v[1]<v._v[1]);
        }

        inline T* ptr() { return _v; }
        inline const T* ptr() const { return _v; }

        inline void set(T x, T y) { _v[0] = x; _v[1] = y; }

        inline T& operator [] (int i) { return _v[i]; }
        inline T operator [] (int i) const { return _v[i]; }

        inline T& x() { return _v[0]; }
        inline T& y() { return _v[1]; }

        inline T x() const { return _v[0]; }
        inline T y() const { return _v[1]; }


        inline bool valid() const { return !isNaN(); }

        inline bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]); }

        template<typename RES_T = T>
        inline RES_T operator * (const Vec2& rhs) const
        {
            return RES_T(_v[0] * rhs._v[0]) + RES_T(_v[1] * rhs._v[1]);
        }

        template<typename RES_T = T>
        inline const Vec2<RES_T> operator * (T rhs) const
        {
            return Vec2<RES_T>(RES_T(_v[0] * rhs), RES_T(_v[1] * rhs));
        }

        inline Vec2& operator *= (T rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            return *this;
        }

        template<typename RES_T = T>
        inline const Vec2<RES_T> operator / (T rhs) const
        {
            return Vec2<RES_T>(RES_T(_v[0]) / RES_T(rhs), RES_T(_v[1]) / RES_T(rhs));
        }

        inline Vec2& operator /= (T rhs)
        {
            _v[0] /= rhs;
            _v[1] /= rhs;
            return *this;
        }

        template<typename RES_T = T>
        inline const Vec2<RES_T> operator + (const Vec2& rhs) const
        {
            return Vec2<RES_T>(RES_T(_v[0] + rhs._v[0]), RES_T(_v[1] + rhs._v[1]));
        }

        inline Vec2& operator += (const Vec2& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            return *this;
        }

        inline const Vec2 operator - (const Vec2& rhs) const
        {
            return Vec2(_v[0] - rhs._v[0], _v[1] - rhs._v[1]);
        }

        inline Vec2& operator -= (const Vec2& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            return *this;
        }

        inline const Vec2 operator - () const
        {
            return Vec2(-_v[0], -_v[1]);
        }

        template<typename RES_T = T>
        inline RES_T length() const
        {
            return sqrt(RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]));
        }

        template<typename RES_T = T>
        inline RES_T length2(void) const
        {
            return RES_T(_v[0] * _v[0]) + RES_T(_v[1] * _v[1]);
        }

        template<typename RES_T = T>
        inline RES_T normalize()
        {
            RES_T norm = Vec2::length<RES_T>();
            if (norm>0.0)
            {
                double inv = 1.0 / norm;
                _v[0] *= inv;
                _v[1] *= inv;
            }
            return(norm);
        }

    };    // end of class Vec2d


    template<typename T>
    inline Vec2<T> componentMultiply(const Vec2<T>& lhs, const Vec2<T>& rhs)
    {
        return Vec2<T>(lhs[0] * rhs[0], lhs[1] * rhs[1]);
    }

    template<typename T>
    inline Vec2<T> componentDivide(const Vec2<T>& lhs, const Vec2<T>& rhs)
    {
        return Vec2<T>(lhs[0] / rhs[0], lhs[1] / rhs[1]);
    }


    typedef Vec2<float> Vec2f;
    typedef Vec2<double> Vec2d;
    typedef Vec2<int> Vec2i;
    typedef Vec2<unsigned int> Vec2ui;
    typedef Vec2<short> Vec2s;
    typedef Vec2<unsigned short> Vec2us;
	typedef Vec2<char> Vec2b;
	typedef Vec2<unsigned char> Vec2ub;
}
