#pragma once
#include "Vec3.h"
#include "Vec4.h"
#include "Math.h"

namespace pallas
{
    template <class T>
    inline T SGL_ABS(T a)
    {
        return (a >= 0 ? a : -a);
    }

#ifndef SGL_SWAP
#define SGL_SWAP(a,b,temp) ((temp)=(a),(a)=(b),(b)=(temp))
#endif
    template<typename T>
    class Mat4
    {
        template<typename Other> friend class Mat4;
    public:
        Mat4()
        {
            makeIdentity();
        }
        Mat4(T a00, T a01, T a02, T a03,
            T a10, T a11, T a12, T a13,
            T a20, T a21, T a22, T a23,
            T a30, T a31, T a32, T a33) 
        {
            set(a00, a01, a02, a03, a10, a11, a12, a13, a20, a21, a22, a23, a30, a31, a32, a33);
        }
        template<typename RES_T>
        Mat4(RES_T const * const ptr)
        {
            set<RES_T>(ptr);
        }
        template<typename RES_T>
        Mat4(const Mat4<RES_T>& mat)
        {
            set<RES_T>(mat);
        }

        template<typename RES_T>
        inline Mat4& operator = (const Mat4<RES_T>& rhs)
        {
            if (&rhs == this) return *this;
            set<RES_T>(rhs.ptr());
            return *this;
        }

        template<typename RES_T>
        inline void set(const Mat4<RES_T>& rhs) { set<RES_T>(rhs.ptr()); }

        template<typename RES_T>
        inline void set(RES_T const * const ptr)
        {
            T* local_ptr = (T*)_mat;
            for (int i = 0; i<16; ++i) local_ptr[i] = (T)ptr[i];
        }

        void set(T a00, T a01, T a02, T a03,
            T a10, T a11, T a12, T a13,
            T a20, T a21, T a22, T a23,
            T a30, T a31, T a32, T a33)
        {
            _mat[0][0] = a00; _mat[0][1] = a01; _mat[0][2] = a02; _mat[0][3] = a03;
            _mat[1][0] = a10; _mat[1][1] = a11; _mat[1][2] = a12; _mat[1][3] = a13;
            _mat[2][0] = a20; _mat[2][1] = a21; _mat[2][2] = a22; _mat[2][3] = a23;
            _mat[3][0] = a30; _mat[3][1] = a31; _mat[3][2] = a32; _mat[3][3] = a33;
        }

        bool isIdentity() const
        {
            return _mat[0][0] == 1 && _mat[0][1] == 0 && _mat[0][2] == 0 &&  _mat[0][3] == 0 &&
                _mat[1][0] == 0 && _mat[1][1] == 1 && _mat[1][2] == 0 &&  _mat[1][3] == 0 &&
                _mat[2][0] == 0 && _mat[2][1] == 0 && _mat[2][2] == 1 &&  _mat[2][3] == 0 &&
                _mat[3][0] == 0 && _mat[3][1] == 0 && _mat[3][2] == 0 &&  _mat[3][3] == 1;
        }

        void makeIdentity()
        {
            _mat[0][0] = 1; _mat[0][1] = 0; _mat[0][2] = 0; _mat[0][3] = 0;
            _mat[1][0] = 0; _mat[1][1] = 1; _mat[1][2] = 0; _mat[1][3] = 0;
            _mat[2][0] = 0; _mat[2][1] = 0; _mat[2][2] = 1; _mat[2][3] = 0;
            _mat[3][0] = 0; _mat[3][1] = 0; _mat[3][2] = 0; _mat[3][3] = 1;
        }
        T * ptr() { return (T*)_mat; }
        const T * ptr() const { return (const T *)_mat; }

        int compare(const Mat4& m) const
        {
            const T* lhs = reinterpret_cast<const T*>(_mat);
            const T* end_lhs = lhs + 16;
            const T* rhs = reinterpret_cast<const T*>(m._mat);
            for (; lhs != end_lhs; ++lhs, ++rhs)
            {
                if (*lhs < *rhs) return -1;
                if (*rhs < *lhs) return 1;
            }
            return 0;
        }

        bool operator < (const Mat4& m) const { return compare(m)<0; }
        bool operator == (const Mat4& m) const { return compare(m) == 0; }
        bool operator != (const Mat4& m) const { return compare(m) != 0; }

        inline T& operator()(int row, int col) { return _mat[row][col]; }
        inline T operator()(int row, int col) const { return _mat[row][col]; }

        inline bool valid() const { return !isNaN(); }
        inline bool isNaN() const {
            return osg::isNaN(_mat[0][0]) || osg::isNaN(_mat[0][1]) || osg::isNaN(_mat[0][2]) || osg::isNaN(_mat[0][3]) ||
                osg::isNaN(_mat[1][0]) || osg::isNaN(_mat[1][1]) || osg::isNaN(_mat[1][2]) || osg::isNaN(_mat[1][3]) ||
                osg::isNaN(_mat[2][0]) || osg::isNaN(_mat[2][1]) || osg::isNaN(_mat[2][2]) || osg::isNaN(_mat[2][3]) ||
                osg::isNaN(_mat[3][0]) || osg::isNaN(_mat[3][1]) || osg::isNaN(_mat[3][2]) || osg::isNaN(_mat[3][3]);
        }

        template<typename RES_T>
        void preMult(const Mat4<RES_T>& other)
        {
            T t[4];
            for (int col = 0; col<4; ++col) {
                t[0] = innerProduct(other, *this, 0, col);
                t[1] = innerProduct(other, *this, 1, col);
                t[2] = innerProduct(other, *this, 2, col);
                t[3] = innerProduct(other, *this, 3, col);
                _mat[0][col] = t[0];
                _mat[1][col] = t[1];
                _mat[2][col] = t[2];
                _mat[3][col] = t[3];
            }
        }

        template<typename RES_T>
        void postMult(const Mat4<RES_T>& other)
        {
            T t[4];
            for (int row = 0; row<4; ++row)
            {
                t[0] = innerProduct(*this, other, row, 0);
                t[1] = innerProduct(*this, other, row, 1);
                t[2] = innerProduct(*this, other, row, 2);
                t[3] = innerProduct(*this, other, row, 3);
				setRow(row, t[0], t[1], t[2], t[3]);
            }
        }

        template<typename RES_T>
        inline Mat4 operator * (const Mat4<RES_T> &m) const
        {
			Mat4 r;
            r.mult(*this, m);
            return  r;
        }

        template<typename RES_T>
        inline void operator *= (const Mat4<RES_T>& other)
        {
            if (this == &other) {
                Mat4 temp(other);
                postMult(temp);
            }
            else postMult(other);
        }

        template<typename VT>
        inline Vec3<VT> preMult(const Vec3<VT>& v) const
        {
            double d = 1.0 / (_mat[0][3] * v.x() + _mat[1][3] * v.y() + _mat[2][3] * v.z() + _mat[3][3]);
            return Vec3<VT>((_mat[0][0] * v.x() + _mat[1][0] * v.y() + _mat[2][0] * v.z() + _mat[3][0])*d,
                (_mat[0][1] * v.x() + _mat[1][1] * v.y() + _mat[2][1] * v.z() + _mat[3][1])*d,
                (_mat[0][2] * v.x() + _mat[1][2] * v.y() + _mat[2][2] * v.z() + _mat[3][2])*d);
        }
        template<typename VT>
        inline Vec3<VT> postMult(const Vec3<VT>& v) const
        {
            double d = 1.0 / (_mat[3][0] * v.x() + _mat[3][1] * v.y() + _mat[3][2] * v.z() + _mat[3][3]);
            return Vec3<VT>((_mat[0][0] * v.x() + _mat[0][1] * v.y() + _mat[0][2] * v.z() + _mat[0][3])*d,
                (_mat[1][0] * v.x() + _mat[1][1] * v.y() + _mat[1][2] * v.z() + _mat[1][3])*d,
                (_mat[2][0] * v.x() + _mat[2][1] * v.y() + _mat[2][2] * v.z() + _mat[2][3])*d);
        }
        template<typename VT>
        inline Vec3<VT> operator* (const Vec3<VT>& v) const
        {
            return postMult(v);
        }
        template<typename VT>
        inline Vec4<VT> preMult(const Vec4<VT>& v) const
        {
            return Vec4<VT>((_mat[0][0] * v.x() + _mat[1][0] * v.y() + _mat[2][0] * v.z() + _mat[3][0] * v.w()),
                (_mat[0][1] * v.x() + _mat[1][1] * v.y() + _mat[2][1] * v.z() + _mat[3][1] * v.w()),
                (_mat[0][2] * v.x() + _mat[1][2] * v.y() + _mat[2][2] * v.z() + _mat[3][2] * v.w()),
                (_mat[0][3] * v.x() + _mat[1][3] * v.y() + _mat[2][3] * v.z() + _mat[3][3] * v.w()));
        }
        template<typename VT>
        inline Vec4<VT> postMult(const Vec4<VT>& v) const
        {
            return Vec4<VT>((_mat[0][0] * v.x() + _mat[0][1] * v.y() + _mat[0][2] * v.z() + _mat[0][3] * v.w()),
                (_mat[1][0] * v.x() + _mat[1][1] * v.y() + _mat[1][2] * v.z() + _mat[1][3] * v.w()),
                (_mat[2][0] * v.x() + _mat[2][1] * v.y() + _mat[2][2] * v.z() + _mat[2][3] * v.w()),
                (_mat[3][0] * v.x() + _mat[3][1] * v.y() + _mat[3][2] * v.z() + _mat[3][3] * v.w()));
        }
        template<typename VT>
        inline Vec4<VT> operator* (const Vec4<VT>& v) const
        {
            return postMult(v);
        }

		/** Optimized version of preMult(translate(v)); */
		template<typename VT>
		inline void preMultTranslate(const Vec3<VT>& v) {
			for (unsigned i = 0; i < 3; ++i)
			{
				double tmp = v[i];
				if (tmp == 0)
					continue;
				_mat[3][0] += tmp*_mat[i][0];
				_mat[3][1] += tmp*_mat[i][1];
				_mat[3][2] += tmp*_mat[i][2];
				_mat[3][3] += tmp*_mat[i][3];
			}
		}
		/** Optimized version of postMult(translate(v)); */
		template<typename VT>
		inline void postMultTranslate(const Vec3<VT>& v) {
			for (unsigned i = 0; i < 3; ++i)
			{
				double tmp = v[i];
				if (tmp == 0)
					continue;
				_mat[0][i] += tmp*_mat[0][3];
				_mat[1][i] += tmp*_mat[1][3];
				_mat[2][i] += tmp*_mat[2][3];
				_mat[3][i] += tmp*_mat[3][3];
			}
		}

		/** Optimized version of preMult(scale(v)); */
		template<typename VT>
		inline void preMultScale(const Vec3<VT>& v) {
			_mat[0][0] *= v[0]; _mat[0][1] *= v[0]; _mat[0][2] *= v[0]; _mat[0][3] *= v[0];
			_mat[1][0] *= v[1]; _mat[1][1] *= v[1]; _mat[1][2] *= v[1]; _mat[1][3] *= v[1];
			_mat[2][0] *= v[2]; _mat[2][1] *= v[2]; _mat[2][2] *= v[2]; _mat[2][3] *= v[2];
		}
		/** Optimized version of postMult(scale(v)); */
		template<typename VT>
		inline void postMultScale(const Vec3<VT>& v) {
			_mat[0][0] *= v[0]; _mat[1][0] *= v[0]; _mat[2][0] *= v[0]; _mat[3][0] *= v[0];
			_mat[0][1] *= v[1]; _mat[1][1] *= v[1]; _mat[2][1] *= v[1]; _mat[3][1] *= v[1];
			_mat[0][2] *= v[2]; _mat[1][2] *= v[2]; _mat[2][2] *= v[2]; _mat[3][2] *= v[2];
		}

        template<typename VT>
        void makeScale(const Vec3<VT>& s)
        {
            setRow(0, s.x(), 0, 0, 0);
            setRow(1, 0, s.y(), 0, 0);
            setRow(2, 0, 0, s.z(), 0);
            setRow(3, 0, 0, 0, 1);
        }

        inline Vec3d getTrans() const { return Vec3d(_mat[3][0], _mat[3][1], _mat[3][2]); }

        inline Vec3d getScale() const {
            Vec3d x_vec(_mat[0][0], _mat[1][0], _mat[2][0]);
            Vec3d y_vec(_mat[0][1], _mat[1][1], _mat[2][1]);
            Vec3d z_vec(_mat[0][2], _mat[1][2], _mat[2][2]);
            return Vec3d(x_vec.length(), y_vec.length(), z_vec.length());
        }

        template<typename VT>
        void makeTranslate(const Vec3<VT>& t)
        {
            setRow(0, 1, 0, 0, 0);
            setRow(1, 0, 1, 0, 0);
            setRow(2, 0, 0, 1, 0);
            setRow(3, t.x(), t.y(), t.z(), 1);
        }

        template<typename VT>
        void makeRotate(double angle, const Vec3<VT>& axis)
        {
            double const a = angle;
            double const c = cos(a);
            double const s = sin(a);

            axis.normalize();
            Vec3d temp((1.0 - c) * axis);

            _mat[0][0] = c + temp[0] * axis[0];
            _mat[0][1] = temp[0] * axis[1] + s * axis[2];
            _mat[0][2] = temp[0] * axis[2] - s * axis[1];

            _mat[1][0] = temp[1] * axis[0] - s * axis[2];
            _mat[1][1] = c + temp[1] * axis[1];
            _mat[1][2] = temp[1] * axis[2] + s * axis[0];

            _mat[2][0] = temp[2] * axis[0] + s * axis[1];
            _mat[2][1] = temp[2] * axis[1] - s * axis[0];
            _mat[2][2] = c + temp[2] * axis[2];
        }

        void makeRotate(T anglex, T angley, T anglez)
        {
            Mat4 RX;
            RX.setRow(0, 1, 0, 0, 0);
            RX.setRow(1, 0, cos(anglex), sin(anglex), 0);
            RX.setRow(2, 0, -sin(anglex), cos(anglex), 0);
            RX.setRow(3, 0, 0, 0, 1);
            //
            Mat4 RY;
            RY.setRow(0, cos(angley), 0, -sin(angley), 0);
            RY.setRow(1, 0, 1, 0, 0);
            RY.setRow(2, sin(angley), 0, cos(angley), 0);
            RY.setRow(3, 0, 0, 0, 1);
            //
            Mat4 RZ;
            RZ.setRow(0, cos(anglez), sin(anglez), 0, 0);
            RZ.setRow(1, -sin(anglez), cos(anglez), 0, 0);
            RZ.setRow(2, 0, 0, 1, 0);
            RZ.setRow(3, 0, 0, 0, 1);
            //
            Mat4 R = RX*RY*RZ;
            memcpy(_mat, R._mat, sizeof(T) * 16);
        }

        void makeOrtho(double left, double right,
            double bottom, double top,
            double zNear, double zFar)
        {
            double tx = -(right + left) / (right - left);
            double ty = -(top + bottom) / (top - bottom);
            double tz = -(zFar + zNear) / (zFar - zNear);
            setRow(0, 2.0 / (right - left), 0.0, 0.0, 0.0);
            setRow(1, 0.0, 2.0 / (top - bottom), 0.0, 0.0);
            setRow(2, 0.0, 0.0, -2.0 / (zFar - zNear), 0.0);
            setRow(3, tx, ty, tz, 1.0);
        }

        /** Get the orthographic settings of the orthographic projection matrix.
        * Note, if matrix is not an orthographic matrix then invalid values
        * will be returned.
        */
        bool getOrtho(double& left, double& right,
            double& bottom, double& top,
            double& zNear, double& zFar) const
        {
            if (_mat[0][3] != 0.0 || _mat[1][3] != 0.0 || _mat[2][3] != 0.0 || _mat[3][3] != 1.0) return false;

            zNear = (_mat[3][2] + 1.0) / _mat[2][2];
            zFar = (_mat[3][2] - 1.0) / _mat[2][2];

            left = -(1.0 + _mat[3][0]) / _mat[0][0];
            right = (1.0 - _mat[3][0]) / _mat[0][0];

            bottom = -(1.0 + _mat[3][1]) / _mat[1][1];
            top = (1.0 - _mat[3][1]) / _mat[1][1];

            return true;
        }

        /** Set to a 2D orthographic projection.
        * See glOrtho2D for further details.
        */
        inline void makeOrtho2D(double left, double right,
            double bottom, double top)
        {
            makeOrtho(left, right, bottom, top, -1.0, 1.0);
        }


        /** Set to a perspective projection.
        * See glFrustum for further details.
        */
        void makeFrustum(double left, double right,
            double bottom, double top,
            double zNear, double zFar)
        {
            // note transpose of Matrix_implementation wr.t OpenGL documentation, since the OSG use post multiplication rather than pre.
            double A = (right + left) / (right - left);
            double B = (top + bottom) / (top - bottom);
            double C = (fabs(zFar)>DBL_MAX) ? -1. : -(zFar + zNear) / (zFar - zNear);
            double D = (fabs(zFar)>DBL_MAX) ? -2.*zNear : -2.0*zFar*zNear / (zFar - zNear);
            setRow(0, 2.0*zNear / (right - left), 0.0, 0.0, 0.0);
            setRow(1, 0.0, 2.0*zNear / (top - bottom), 0.0, 0.0);
            setRow(2, A, B, C, -1.0);
            setRow(3, 0.0, 0.0, D, 0.0);
        }

        /** Get the frustum settings of a perspective projection matrix.
        * Note, if matrix is not a perspective matrix then invalid values
        * will be returned.
        */
        bool getFrustum(double& left, double& right,
            double& bottom, double& top,
            double& zNear, double& zFar) const
        {
            if (_mat[0][3] != 0.0 || _mat[1][3] != 0.0 || _mat[2][3] != -1.0 || _mat[3][3] != 0.0)
                return false;

            // note: near and far must be used inside this method instead of zNear and zFar
            // because zNear and zFar are references and they may point to the same variable.
            double temp_near = _mat[3][2] / (_mat[2][2] - 1.0);
            double temp_far = _mat[3][2] / (1.0 + _mat[2][2]);

            left = temp_near * (_mat[2][0] - 1.0) / _mat[0][0];
            right = temp_near * (1.0 + _mat[2][0]) / _mat[0][0];

            top = temp_near * (1.0 + _mat[2][1]) / _mat[1][1];
            bottom = temp_near * (_mat[2][1] - 1.0) / _mat[1][1];

            zNear = temp_near;
            zFar = temp_far;

            return true;
        }

        /** Set to a symmetrical perspective projection.
        * See gluPerspective for further details.
        * Aspect ratio is defined as width/height.
        */
        void makePerspective(double fovy, double aspectRatio,
            double zNear, double zFar)
        {
            // calculate the appropriate left, right etc.
            double tan_fovy = tan(DegreesToRadians(fovy*0.5));
            double right = tan_fovy * aspectRatio * zNear;
            double left = -right;
            double top = tan_fovy * zNear;
            double bottom = -top;
            makeFrustum(left, right, bottom, top, zNear, zFar);
        }

        /** Get the frustum settings of a symmetric perspective projection
        * matrix.
        * Return false if matrix is not a perspective matrix,
        * where parameter values are undefined.
        * Note, if matrix is not a symmetric perspective matrix then the
        * shear will be lost.
        * Asymmetric matrices occur when stereo, power walls, caves and
        * reality center display are used.
        * In these configuration one should use the AsFrustum method instead.
        */
        bool getPerspective(double& fovy, double& aspectRatio,
            double& zNear, double& zFar) const
        {
            double right = 0.0;
            double left = 0.0;
            double top = 0.0;
            double bottom = 0.0;

            // note: near and far must be used inside this method instead of zNear and zFar
            // because zNear and zFar are references and they may point to the same variable.
            double temp_near = 0.0;
            double temp_far = 0.0;

            // get frustum and compute results
            bool r = getFrustum(left, right, bottom, top, temp_near, temp_far);
            if (r)
            {
                fovy = RadiansToDegrees(atan(top / temp_near) - atan(bottom / temp_near));
                aspectRatio = (right - left) / (top - bottom);
            }
            zNear = temp_near;
            zFar = temp_far;
            return r;
        }


        /** Set the position and orientation to be a view matrix,
        * using the same convention as gluLookAt.
        */
        void makeLookAt(const Vec3d& eye, const Vec3d& center, const Vec3d& up)
        {
            Vec3d f(center - eye);
            f.normalize();
            Vec3d s(f^up);
            s.normalize();
            Vec3d u(s^f);
            u.normalize();

            set(
                s[0], u[0], -f[0], 0.0,
                s[1], u[1], -f[1], 0.0,
                s[2], u[2], -f[2], 0.0,
                0.0, 0.0, 0.0, 1.0);

            preMultTranslate(-eye);
        }

        /** Get to the position and orientation of a modelview matrix,
        * using the same convention as gluLookAt.
        */
        void getLookAt(Vec3d& eye, Vec3d& center, Vec3d& up,
            T lookDistance = 1.0f) const
        {
            Mat4 inv;
            inv.invert(*this);

            // note: e and c variables must be used inside this method instead of eye and center
            // because eye and center are references and they may point to the same variable.
            Vec3d e = osg::Vec3d(0.0, 0.0, 0.0)*inv;
            up = transform3x3(*this, osg::Vec3d(0.0, 1.0, 0.0));
            Vec3d c = transform3x3(*this, osg::Vec3d(0.0, 0.0, -1));
            c.normalize();
            c = e + c*lookDistance;

            // assign the results
            eye = e;
            center = c;
        }

        /** invert the matrix rhs, automatically select invert_4x3 or invert_4x4. */
        inline bool invert(const Mat4& rhs)
        {
            bool is_4x3 = (rhs._mat[0][3] == 0.0 && rhs._mat[1][3] == 0.0 &&  rhs._mat[2][3] == 0.0 && rhs._mat[3][3] == 1.0);
            return is_4x3 ? invert_4x3(rhs) : invert_4x4(rhs);
        }

        /** ortho-normalize the 3x3 rotation & scale matrix */
        void orthoNormalize(const Mat4& rhs)
        {
            double x_colMag = (rhs._mat[0][0] * rhs._mat[0][0]) + (rhs._mat[1][0] * rhs._mat[1][0]) + (rhs._mat[2][0] * rhs._mat[2][0]);
            double y_colMag = (rhs._mat[0][1] * rhs._mat[0][1]) + (rhs._mat[1][1] * rhs._mat[1][1]) + (rhs._mat[2][1] * rhs._mat[2][1]);
            double z_colMag = (rhs._mat[0][2] * rhs._mat[0][2]) + (rhs._mat[1][2] * rhs._mat[1][2]) + (rhs._mat[2][2] * rhs._mat[2][2]);

            if (!equivalent((double)x_colMag, 1.0) && !equivalent((double)x_colMag, 0.0))
            {
                x_colMag = sqrt(x_colMag);
                _mat[0][0] = rhs._mat[0][0] / x_colMag;
                _mat[1][0] = rhs._mat[1][0] / x_colMag;
                _mat[2][0] = rhs._mat[2][0] / x_colMag;
            }
            else
            {
                _mat[0][0] = rhs._mat[0][0];
                _mat[1][0] = rhs._mat[1][0];
                _mat[2][0] = rhs._mat[2][0];
            }

            if (!equivalent((double)y_colMag, 1.0) && !equivalent((double)y_colMag, 0.0))
            {
                y_colMag = sqrt(y_colMag);
                _mat[0][1] = rhs._mat[0][1] / y_colMag;
                _mat[1][1] = rhs._mat[1][1] / y_colMag;
                _mat[2][1] = rhs._mat[2][1] / y_colMag;
            }
            else
            {
                _mat[0][1] = rhs._mat[0][1];
                _mat[1][1] = rhs._mat[1][1];
                _mat[2][1] = rhs._mat[2][1];
            }

            if (!equivalent((double)z_colMag, 1.0) && !equivalent((double)z_colMag, 0.0))
            {
                z_colMag = sqrt(z_colMag);
                _mat[0][2] = rhs._mat[0][2] / z_colMag;
                _mat[1][2] = rhs._mat[1][2] / z_colMag;
                _mat[2][2] = rhs._mat[2][2] / z_colMag;
            }
            else
            {
                _mat[0][2] = rhs._mat[0][2];
                _mat[1][2] = rhs._mat[1][2];
                _mat[2][2] = rhs._mat[2][2];
            }

            _mat[3][0] = rhs._mat[3][0];
            _mat[3][1] = rhs._mat[3][1];
            _mat[3][2] = rhs._mat[3][2];

            _mat[0][3] = rhs._mat[0][3];
            _mat[1][3] = rhs._mat[1][3];
            _mat[2][3] = rhs._mat[2][3];
            _mat[3][3] = rhs._mat[3][3];
        }
    private:
        inline void setRow(short row, T v1, T v2, T v3, T v4)
        {
            _mat[row][0] = v1;
            _mat[row][1] = v2;
            _mat[row][2] = v3;
            _mat[row][3] = v4;
        }

        template<typename RES_T1, typename RES_T2>
        inline T innerProduct(const Mat4<RES_T1>& ma, const Mat4<RES_T2>& mb, short r, short c)
        {
			return T(ma._mat[r][0] * mb._mat[0][c])
				+ T(ma._mat[r][1] * mb._mat[1][c])
				+ T(ma._mat[r][2] * mb._mat[2][c])
				+ T(ma._mat[r][3] * mb._mat[3][c]);
        }

        template<typename RES_T1, typename RES_T2>
        void mult(const Mat4<RES_T1>& lhs, const Mat4<RES_T2>& rhs)
        {
            if (&lhs == this)
            {
                postMult(rhs);
                return;
            }
            if (&rhs == this)
            {
                preMult(lhs);
                return;
            }

            // PRECONDITION: We assume neither &lhs nor &rhs == this
            // if it did, use preMult or postMult instead
            _mat[0][0] = innerProduct(lhs, rhs, 0, 0);
            _mat[0][1] = innerProduct(lhs, rhs, 0, 1);
            _mat[0][2] = innerProduct(lhs, rhs, 0, 2);
            _mat[0][3] = innerProduct(lhs, rhs, 0, 3);
            _mat[1][0] = innerProduct(lhs, rhs, 1, 0);
            _mat[1][1] = innerProduct(lhs, rhs, 1, 1);
            _mat[1][2] = innerProduct(lhs, rhs, 1, 2);
            _mat[1][3] = innerProduct(lhs, rhs, 1, 3);
            _mat[2][0] = innerProduct(lhs, rhs, 2, 0);
            _mat[2][1] = innerProduct(lhs, rhs, 2, 1);
            _mat[2][2] = innerProduct(lhs, rhs, 2, 2);
            _mat[2][3] = innerProduct(lhs, rhs, 2, 3);
            _mat[3][0] = innerProduct(lhs, rhs, 3, 0);
            _mat[3][1] = innerProduct(lhs, rhs, 3, 1);
            _mat[3][2] = innerProduct(lhs, rhs, 3, 2);
            _mat[3][3] = innerProduct(lhs, rhs, 3, 3);
        }

        /** 4x3 matrix invert, not right hand column is assumed to be 0,0,0,1. */
        bool invert_4x3(const Mat4& mat)
        {
            if (&mat == this)
            {
                Mat4 tm(mat);
                return invert_4x3(tm);
            }

            register T r00, r01, r02,
                r10, r11, r12,
                r20, r21, r22;
            // Copy rotation components directly into registers for speed
            r00 = mat._mat[0][0]; r01 = mat._mat[0][1]; r02 = mat._mat[0][2];
            r10 = mat._mat[1][0]; r11 = mat._mat[1][1]; r12 = mat._mat[1][2];
            r20 = mat._mat[2][0]; r21 = mat._mat[2][1]; r22 = mat._mat[2][2];

            // Partially compute inverse of rot
            _mat[0][0] = r11*r22 - r12*r21;
            _mat[0][1] = r02*r21 - r01*r22;
            _mat[0][2] = r01*r12 - r02*r11;

            // Compute determinant of rot from 3 elements just computed
            register value_type one_over_det = 1.0 / (r00*_mat[0][0] + r10*_mat[0][1] + r20*_mat[0][2]);
            r00 *= one_over_det; r10 *= one_over_det; r20 *= one_over_det;  // Saves on later computations

                                                                            // Finish computing inverse of rot
            _mat[0][0] *= one_over_det;
            _mat[0][1] *= one_over_det;
            _mat[0][2] *= one_over_det;
            _mat[0][3] = 0.0;
            _mat[1][0] = r12*r20 - r10*r22; // Have already been divided by det
            _mat[1][1] = r00*r22 - r02*r20; // same
            _mat[1][2] = r02*r10 - r00*r12; // same
            _mat[1][3] = 0.0;
            _mat[2][0] = r10*r21 - r11*r20; // Have already been divided by det
            _mat[2][1] = r01*r20 - r00*r21; // same
            _mat[2][2] = r00*r11 - r01*r10; // same
            _mat[2][3] = 0.0;
            _mat[3][3] = 1.0;

            // We no longer need the rxx or det variables anymore, so we can reuse them for whatever we want.  But we will still rename them for the sake of clarity.

#define d r22
            d = mat._mat[3][3];

            if (osg::square(d - 1.0) > 1.0e-6)  // Involves perspective, so we must
            {                       // compute the full inverse

                Matrix_implementation TPinv;
                _mat[3][0] = _mat[3][1] = _mat[3][2] = 0.0;

#define px r00
#define py r01
#define pz r02
#define one_over_s  one_over_det
#define a  r10
#define b  r11
#define c  r12

                a = mat._mat[0][3]; b = mat._mat[1][3]; c = mat._mat[2][3];
                px = _mat[0][0] * a + _mat[0][1] * b + _mat[0][2] * c;
                py = _mat[1][0] * a + _mat[1][1] * b + _mat[1][2] * c;
                pz = _mat[2][0] * a + _mat[2][1] * b + _mat[2][2] * c;

#undef a
#undef b
#undef c
#define tx r10
#define ty r11
#define tz r12

                tx = mat._mat[3][0]; ty = mat._mat[3][1]; tz = mat._mat[3][2];
                one_over_s = 1.0 / (d - (tx*px + ty*py + tz*pz));

                tx *= one_over_s; ty *= one_over_s; tz *= one_over_s;  // Reduces number of calculations later on

                                                                       // Compute inverse of trans*corr
                TPinv._mat[0][0] = tx*px + 1.0;
                TPinv._mat[0][1] = ty*px;
                TPinv._mat[0][2] = tz*px;
                TPinv._mat[0][3] = -px * one_over_s;
                TPinv._mat[1][0] = tx*py;
                TPinv._mat[1][1] = ty*py + 1.0;
                TPinv._mat[1][2] = tz*py;
                TPinv._mat[1][3] = -py * one_over_s;
                TPinv._mat[2][0] = tx*pz;
                TPinv._mat[2][1] = ty*pz;
                TPinv._mat[2][2] = tz*pz + 1.0;
                TPinv._mat[2][3] = -pz * one_over_s;
                TPinv._mat[3][0] = -tx;
                TPinv._mat[3][1] = -ty;
                TPinv._mat[3][2] = -tz;
                TPinv._mat[3][3] = one_over_s;

                preMult(TPinv); // Finish computing full inverse of mat

#undef px
#undef py
#undef pz
#undef one_over_s
#undef d
            }
            else // Rightmost column is [0; 0; 0; 1] so it can be ignored
            {
                tx = mat._mat[3][0]; ty = mat._mat[3][1]; tz = mat._mat[3][2];

                // Compute translation components of mat'
                _mat[3][0] = -(tx*_mat[0][0] + ty*_mat[1][0] + tz*_mat[2][0]);
                _mat[3][1] = -(tx*_mat[0][1] + ty*_mat[1][1] + tz*_mat[2][1]);
                _mat[3][2] = -(tx*_mat[0][2] + ty*_mat[1][2] + tz*_mat[2][2]);

#undef tx
#undef ty
#undef tz
            }

            return true;
        }

        /** full 4x4 matrix invert. */
        bool invert_4x4(const Mat4& mat)
        {
            if (&mat == this) {
                Mat4 tm(mat);
                return invert_4x4(tm);
            }

            unsigned int indxc[4], indxr[4], ipiv[4];
            unsigned int i, j, k, l, ll;
            unsigned int icol = 0;
            unsigned int irow = 0;
            double temp, pivinv, dum, big;

            // copy in place this may be unnecessary
            *this = mat;

            for (j = 0; j<4; j++) ipiv[j] = 0;

            for (i = 0; i<4; i++)
            {
                big = 0.0;
                for (j = 0; j<4; j++)
                    if (ipiv[j] != 1)
                        for (k = 0; k<4; k++)
                        {
                            if (ipiv[k] == 0)
                            {
                                if (SGL_ABS(operator()(j, k)) >= big)
                                {
                                    big = SGL_ABS(operator()(j, k));
                                    irow = j;
                                    icol = k;
                                }
                            }
                            else if (ipiv[k] > 1)
                                return false;
                        }
                ++(ipiv[icol]);
                if (irow != icol)
                    for (l = 0; l<4; l++) SGL_SWAP(operator()(irow, l),
                        operator()(icol, l),
                        temp);

                indxr[i] = irow;
                indxc[i] = icol;
                if (operator()(icol, icol) == 0)
                    return false;

                pivinv = 1.0 / operator()(icol, icol);
                operator()(icol, icol) = 1;
                for (l = 0; l<4; l++) operator()(icol, l) *= pivinv;
                for (ll = 0; ll<4; ll++)
                    if (ll != icol)
                    {
                        dum = operator()(ll, icol);
                        operator()(ll, icol) = 0;
                        for (l = 0; l<4; l++) operator()(ll, l) -= operator()(icol, l)*dum;
                    }
            }
            for (int lx = 4; lx>0; --lx)
            {
                if (indxr[lx - 1] != indxc[lx - 1])
                    for (k = 0; k<4; k++) SGL_SWAP(operator()(k, indxr[lx - 1]),
                        operator()(k, indxc[lx - 1]), temp);
            }

            return true;
        }
    private:
        T _mat[4][4];
    };

    template<typename VT, typename MT>
    inline Vec3<VT> operator* (const Vec3<VT>& v, const Mat4<MT>& m)
    {
        return m.preMult(v);
    }

    template<typename VT, typename MT>
    inline Vec4<VT> operator* (const Vec4<VT>& v, const Mat4<MT>& m)
    {
        return m.preMult(v);
    }

    typedef Mat4<float> Mat4f;
    typedef Mat4<double> Mat4d;
}