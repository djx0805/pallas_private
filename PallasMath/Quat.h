#pragma once
#include<cmath>
#include <limits>
#include <stdlib.h>
#include <float.h>
#include "Vec4.h"
#include "Mat4.h"

namespace pallas
{
    class Quat
    {

    public:
        typedef double value_type;

        value_type  _v[4];    // a four-vector

        inline Quat() { _v[0] = 0.0; _v[1] = 0.0; _v[2] = 0.0; _v[3] = 1.0; }

        inline Quat(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        inline Quat(const Vec4f& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        inline Quat(const Vec4d& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        inline Quat(value_type angle, const Vec3f& axis)
        {
            makeRotate(angle, axis);
        }
        inline Quat(value_type angle, const Vec3d& axis)
        {
            makeRotate(angle, axis);
        }

        inline Quat(value_type angle1, const Vec3f& axis1,
            value_type angle2, const Vec3f& axis2,
            value_type angle3, const Vec3f& axis3)
        {
            makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
        }

        inline Quat(value_type angle1, const Vec3d& axis1,
            value_type angle2, const Vec3d& axis2,
            value_type angle3, const Vec3d& axis3)
        {
            makeRotate(angle1, axis1, angle2, axis2, angle3, axis3);
        }

        inline Quat& operator = (const Quat& v) { _v[0] = v._v[0];  _v[1] = v._v[1]; _v[2] = v._v[2]; _v[3] = v._v[3]; return *this; }

        inline bool operator == (const Quat& v) const { return _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2] && _v[3] == v._v[3]; }

        inline bool operator != (const Quat& v) const { return _v[0] != v._v[0] || _v[1] != v._v[1] || _v[2] != v._v[2] || _v[3] != v._v[3]; }

        inline bool operator <  (const Quat& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        /* ----------------------------------
        Methods to access data members
        ---------------------------------- */

        inline Vec4d asVec4() const
        {
            return Vec4d(_v[0], _v[1], _v[2], _v[3]);
        }

        inline Vec3d asVec3() const
        {
            return Vec3d(_v[0], _v[1], _v[2]);
        }

        inline void set(value_type x, value_type y, value_type z, value_type w)
        {
            _v[0] = x;
            _v[1] = y;
            _v[2] = z;
            _v[3] = w;
        }

        inline void set(const Vec4f& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        inline void set(const Vec4d& v)
        {
            _v[0] = v.x();
            _v[1] = v.y();
            _v[2] = v.z();
            _v[3] = v.w();
        }

        template<typename VT>
        void set(const Mat4<VT>& matrix)
        {
            value_type s;
            value_type tq[4];
            int    i, j;

            // Use tq to store the largest trace
            tq[0] = 1 + matrix(0, 0) + matrix(1, 1) + matrix(2, 2);
            tq[1] = 1 + matrix(0, 0) - matrix(1, 1) - matrix(2, 2);
            tq[2] = 1 - matrix(0, 0) + matrix(1, 1) - matrix(2, 2);
            tq[3] = 1 - matrix(0, 0) - matrix(1, 1) + matrix(2, 2);

            // Find the maximum (could also use stacked if's later)
            j = 0;
            for (i = 1; i<4; i++) j = (tq[i]>tq[j]) ? i : j;

            // check the diagonal
            double QX = _v[0], QY = _v[1], QZ = _v[2], QW = _v[3];
            if (j == 0)
            {
                /* perform instant calculation */
                QW = tq[0];
                QX = matrix(1,2) - matrix(2,1);
                QY = matrix(2,0) - matrix(0,2);
                QZ = matrix(0,1) - matrix(1,0);
            }
            else if (j == 1)
            {
                QW = matrix(1,2) - matrix(2,1);
                QX = tq[1];
                QY = matrix(0,1) + matrix(1,0);
                QZ = matrix(2,0) + matrix(0,2);
            }
            else if (j == 2)
            {
                QW = matrix(2,0) - matrix(0,2);
                QX = matrix(0,1) + matrix(1,0);
                QY = tq[2];
                QZ = matrix(1,2) + matrix(2,1);
            }
            else /* if (j==3) */
            {
                QW = matrix(0,1) - matrix(1,0);
                QX = matrix(2,0) + matrix(0,2);
                QY = matrix(1,2) + matrix(2,1);
                QZ = tq[3];
            }

            s = sqrt(0.25 / tq[j]);
            QW *= s;
            QX *= s;
            QY *= s;
            QZ *= s;
        }

        template<typename VT>
        void get(Mat4<VT>& matrix) const
        {
            double length2 = this->length2();
            if (fabs(length2) <= std::numeric_limits<double>::min())
            {
               matrix.set(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            }
            else
            {
                double rlength2;
                // normalize quat if required.
                // We can avoid the expensive sqrt in this case since all 'coefficients' below are products of two q components.
                // That is a square of a square root, so it is possible to avoid that
                if (length2 != 1.0)
                {
                    rlength2 = 2.0 / length2;
                }
                else
                {
                    rlength2 = 2.0;
                }

                // Source: Gamasutra, Rotating Objects Using Quaternions
                //
                //http://www.gamasutra.com/features/19980703/quaternions_01.htm

                double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
                double QX = _v[0], QY = _v[1], QZ = _v[2], QW = _v[3];
                // calculate coefficients
                x2 = rlength2*QX;
                y2 = rlength2*QY;
                z2 = rlength2*QZ;

                xx = QX * x2;
                xy = QX * y2;
                xz = QX * z2;

                yy = QY * y2;
                yz = QY * z2;
                zz = QZ * z2;

                wx = QW * x2;
                wy = QW * y2;
                wz = QW * z2;

                // Note.  Gamasutra gets the matrix assignments inverted, resulting
                // in left-handed rotations, which is contrary to OpenGL and OSG's
                // methodology.  The matrix assignment has been altered in the next
                // few lines of code to do the right thing.
                // Don Burns - Oct 13, 2001
                matrix(0,0) = 1.0 - (yy + zz);
                matrix(1,0) = xy - wz;
                matrix(2,0) = xz + wy;


                matrix(0,1) = xy + wz;
                matrix(1,1) = 1.0 - (xx + zz);
                matrix(2,1) = yz - wx;

                matrix(0,2) = xz - wy;
                matrix(1,2) = yz + wx;
                matrix(2,2) = 1.0 - (xx + yy);
            }
        }


        inline value_type & operator [] (int i) { return _v[i]; }
        inline value_type   operator [] (int i) const { return _v[i]; }

        inline value_type & x() { return _v[0]; }
        inline value_type & y() { return _v[1]; }
        inline value_type & z() { return _v[2]; }
        inline value_type & w() { return _v[3]; }

        inline value_type x() const { return _v[0]; }
        inline value_type y() const { return _v[1]; }
        inline value_type z() const { return _v[2]; }
        inline value_type w() const { return _v[3]; }

        /** return true if the Quat represents a zero rotation, and therefore can be ignored in computations.*/
        bool zeroRotation() const { return _v[0] == 0.0 && _v[1] == 0.0 && _v[2] == 0.0 && _v[3] == 1.0; }


        /* -------------------------------------------------------------
        BASIC ARITHMETIC METHODS
        Implemented in terms of Vec4s.  Some Vec4 operators, e.g.
        operator* are not appropriate for quaternions (as
        mathematical objects) so they are implemented differently.
        Also define methods for conjugate and the multiplicative inverse.
        ------------------------------------------------------------- */
        /// Multiply by scalar
        inline const Quat operator * (value_type rhs) const
        {
            return Quat(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs, _v[3] * rhs);
        }

        /// Unary multiply by scalar
        inline Quat& operator *= (value_type rhs)
        {
            _v[0] *= rhs;
            _v[1] *= rhs;
            _v[2] *= rhs;
            _v[3] *= rhs;
            return *this;        // enable nesting
        }

        /// Binary multiply
        inline const Quat operator*(const Quat& rhs) const
        {
            return Quat(rhs._v[3] * _v[0] + rhs._v[0] * _v[3] + rhs._v[1] * _v[2] - rhs._v[2] * _v[1],
                rhs._v[3] * _v[1] - rhs._v[0] * _v[2] + rhs._v[1] * _v[3] + rhs._v[2] * _v[0],
                rhs._v[3] * _v[2] + rhs._v[0] * _v[1] - rhs._v[1] * _v[0] + rhs._v[2] * _v[3],
                rhs._v[3] * _v[3] - rhs._v[0] * _v[0] - rhs._v[1] * _v[1] - rhs._v[2] * _v[2]);
        }

        /// Unary multiply
        inline Quat& operator*=(const Quat& rhs)
        {
            value_type x = rhs._v[3] * _v[0] + rhs._v[0] * _v[3] + rhs._v[1] * _v[2] - rhs._v[2] * _v[1];
            value_type y = rhs._v[3] * _v[1] - rhs._v[0] * _v[2] + rhs._v[1] * _v[3] + rhs._v[2] * _v[0];
            value_type z = rhs._v[3] * _v[2] + rhs._v[0] * _v[1] - rhs._v[1] * _v[0] + rhs._v[2] * _v[3];
            _v[3] = rhs._v[3] * _v[3] - rhs._v[0] * _v[0] - rhs._v[1] * _v[1] - rhs._v[2] * _v[2];

            _v[2] = z;
            _v[1] = y;
            _v[0] = x;

            return (*this);            // enable nesting
        }

        /// Divide by scalar
        inline Quat operator / (value_type rhs) const
        {
            value_type div = 1.0 / rhs;
            return Quat(_v[0] * div, _v[1] * div, _v[2] * div, _v[3] * div);
        }

        /// Unary divide by scalar
        inline Quat& operator /= (value_type rhs)
        {
            value_type div = 1.0 / rhs;
            _v[0] *= div;
            _v[1] *= div;
            _v[2] *= div;
            _v[3] *= div;
            return *this;
        }

        /// Binary divide
        inline const Quat operator/(const Quat& denom) const
        {
            return ((*this) * denom.inverse());
        }

        /// Unary divide
        inline Quat& operator/=(const Quat& denom)
        {
            (*this) = (*this) * denom.inverse();
            return (*this);            // enable nesting
        }

        /// Binary addition
        inline const Quat operator + (const Quat& rhs) const
        {
            return Quat(_v[0] + rhs._v[0], _v[1] + rhs._v[1],
                _v[2] + rhs._v[2], _v[3] + rhs._v[3]);
        }

        /// Unary addition
        inline Quat& operator += (const Quat& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;            // enable nesting
        }

        /// Binary subtraction
        inline const Quat operator - (const Quat& rhs) const
        {
            return Quat(_v[0] - rhs._v[0], _v[1] - rhs._v[1],
                _v[2] - rhs._v[2], _v[3] - rhs._v[3]);
        }

        /// Unary subtraction
        inline Quat& operator -= (const Quat& rhs)
        {
            _v[0] -= rhs._v[0];
            _v[1] -= rhs._v[1];
            _v[2] -= rhs._v[2];
            _v[3] -= rhs._v[3];
            return *this;            // enable nesting
        }

        /** Negation operator - returns the negative of the quaternion.
        Basically just calls operator - () on the Vec4 */
        inline const Quat operator - () const
        {
            return Quat(-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /// Length of the quaternion = sqrt( vec . vec )
        value_type length() const
        {
            return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3]);
        }

        /// Length of the quaternion = vec . vec
        value_type length2() const
        {
            return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3];
        }

        /// Conjugate
        inline Quat conj() const
        {
            return Quat(-_v[0], -_v[1], -_v[2], _v[3]);
        }

        /// Multiplicative inverse method: q^(-1) = q^*/(q.q^*)
        inline const Quat inverse() const
        {
            return conj() / length2();
        }

        /* --------------------------------------------------------
        METHODS RELATED TO ROTATIONS
        Set a quaternion which will perform a rotation of an
        angle around the axis given by the vector (x,y,z).
        Should be written to also accept an angle and a Vec3?

        Define Spherical Linear interpolation method also

        Not inlined - see the Quat.cpp file for implementation
        -------------------------------------------------------- */
        void makeRotate(value_type  angle, value_type  x, value_type  y, value_type  z)
        {
            const value_type epsilon = 0.0000001;

            value_type length = sqrt(x*x + y*y + z*z);
            if (length < epsilon)
            {
                // ~zero length axis, so reset rotation to zero.
                *this = Quat();
                return;
            }

            value_type inversenorm = 1.0 / length;
            value_type coshalfangle = cos(0.5*angle);
            value_type sinhalfangle = sin(0.5*angle);

            _v[0] = x * sinhalfangle * inversenorm;
            _v[1] = y * sinhalfangle * inversenorm;
            _v[2] = z * sinhalfangle * inversenorm;
            _v[3] = coshalfangle;
        }

        void makeRotate(value_type  angle, const Vec3d& vec)
        {
            makeRotate(angle, vec[0], vec[1], vec[2]);
        }

        void makeRotate(value_type  angle1, const Vec3d& axis1,
            value_type  angle2, const Vec3d& axis2,
            value_type  angle3, const Vec3d& axis3)
        {
            Quat q1; q1.makeRotate(angle1, axis1);
            Quat q2; q2.makeRotate(angle2, axis2);
            Quat q3; q3.makeRotate(angle3, axis3);

            *this = q1*q2*q3;
        }

        /** Make a rotation Quat which will rotate vec1 to vec2.
        Generally take a dot product to get the angle between these
        and then use a cross product to get the rotation axis
        Watch out for the two special cases of when the vectors
        are co-incident or opposite in direction.*/
        void makeRotate(const Vec3d& from, const Vec3d& to)
        {
            // This routine takes any vector as argument but normalized
            // vectors are necessary, if only for computing the dot product.
            // Too bad the API is that generic, it leads to performance loss.
            // Even in the case the 2 vectors are not normalized but same length,
            // the sqrt could be shared, but we have no way to know beforehand
            // at this point, while the caller may know.
            // So, we have to test... in the hope of saving at least a sqrt
            Vec3d sourceVector = from;
            Vec3d targetVector = to;

            value_type fromLen2 = from.length2();
            value_type fromLen;
            // normalize only when necessary, epsilon test
            if ((fromLen2 < 1.0 - 1e-7) || (fromLen2 > 1.0 + 1e-7)) {
                fromLen = sqrt(fromLen2);
                sourceVector /= fromLen;
            }
            else fromLen = 1.0;

            value_type toLen2 = to.length2();
            // normalize only when necessary, epsilon test
            if ((toLen2 < 1.0 - 1e-7) || (toLen2 > 1.0 + 1e-7)) {
                value_type toLen;
                // re-use fromLen for case of mapping 2 vectors of the same length
                if ((toLen2 > fromLen2 - 1e-7) && (toLen2 < fromLen2 + 1e-7)) {
                    toLen = fromLen;
                }
                else toLen = sqrt(toLen2);
                targetVector /= toLen;
            }


            // Now let's get into the real stuff
            // Use "dot product plus one" as test as it can be re-used later on
            double dotProdPlus1 = 1.0 + sourceVector * targetVector;

            // Check for degenerate case of full u-turn. Use epsilon for detection
            if (dotProdPlus1 < 1e-7) {

                // Get an orthogonal vector of the given vector
                // in a plane with maximum vector coordinates.
                // Then use it as quaternion axis with pi angle
                // Trick is to realize one value at least is >0.6 for a normalized vector.
                if (fabs(sourceVector.x()) < 0.6) {
                    const double norm = sqrt(1.0 - sourceVector.x() * sourceVector.x());
                    _v[0] = 0.0;
                    _v[1] = sourceVector.z() / norm;
                    _v[2] = -sourceVector.y() / norm;
                    _v[3] = 0.0;
                }
                else if (fabs(sourceVector.y()) < 0.6) {
                    const double norm = sqrt(1.0 - sourceVector.y() * sourceVector.y());
                    _v[0] = -sourceVector.z() / norm;
                    _v[1] = 0.0;
                    _v[2] = sourceVector.x() / norm;
                    _v[3] = 0.0;
                }
                else {
                    const double norm = sqrt(1.0 - sourceVector.z() * sourceVector.z());
                    _v[0] = sourceVector.y() / norm;
                    _v[1] = -sourceVector.x() / norm;
                    _v[2] = 0.0;
                    _v[3] = 0.0;
                }
            }

            else {
                // Find the shortest angle quaternion that transforms normalized vectors
                // into one other. Formula is still valid when vectors are colinear
                const double s = sqrt(0.5 * dotProdPlus1);
                const Vec3d tmp = sourceVector ^ targetVector / (2.0*s);
                _v[0] = tmp.x();
                _v[1] = tmp.y();
                _v[2] = tmp.z();
                _v[3] = s;
            }
        }

        void makeRotate_original(const Vec3d& from, const Vec3d& to)
        {
            const value_type epsilon = 0.0000001;

            value_type length1 = from.length();
            value_type length2 = to.length();

            // dot product vec1*vec2
            value_type cosangle = from*to / (length1*length2);

            if (fabs(cosangle - 1) < epsilon)
            {
                // cosangle is close to 1, so the vectors are close to being coincident
                // Need to generate an angle of zero with any vector we like
                // We'll choose (1,0,0)
                makeRotate(0.0, 0.0, 0.0, 1.0);
            }
            else if (fabs(cosangle + 1.0) < epsilon)
            {
                // vectors are close to being opposite, so will need to find a
                // vector orthongonal to from to rotate about.
                Vec3d tmp;
                if (fabs(from.x())<fabs(from.y()))
                    if (fabs(from.x())<fabs(from.z())) tmp.set(1.0, 0.0, 0.0); // use x axis.
                    else tmp.set(0.0, 0.0, 1.0);
                else if (fabs(from.y())<fabs(from.z())) tmp.set(0.0, 1.0, 0.0);
                else tmp.set(0.0, 0.0, 1.0);

                Vec3d fromd(from.x(), from.y(), from.z());

                // find orthogonal axis.
                Vec3d axis(fromd^tmp);
                axis.normalize();

                _v[0] = axis[0]; // sin of half angle of PI is 1.0.
                _v[1] = axis[1]; // sin of half angle of PI is 1.0.
                _v[2] = axis[2]; // sin of half angle of PI is 1.0.
                _v[3] = 0; // cos of half angle of PI is zero.

            }
            else
            {
                // This is the usual situation - take a cross-product of vec1 and vec2
                // and that is the axis around which to rotate.
                Vec3d axis(from^to);
                value_type angle = acos(cosangle);
                makeRotate(angle, axis);
            }
        }

        /** Return the angle and vector components represented by the quaternion.*/
        void getRotate(value_type & angle, value_type & x, value_type & y, value_type & z) const
        {
            value_type sinhalfangle = sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);

            angle = 2.0 * atan2(sinhalfangle, _v[3]);
            if (sinhalfangle)
            {
                x = _v[0] / sinhalfangle;
                y = _v[1] / sinhalfangle;
                z = _v[2] / sinhalfangle;
            }
            else
            {
                x = 0.0;
                y = 0.0;
                z = 1.0;
            }
        }

        /** Return the angle and vector represented by the quaternion.*/
        void getRotate(value_type & angle, Vec3d& vec) const
        {
            value_type x, y, z;
            getRotate(angle, x, y, z);
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
        }

        /** Spherical Linear Interpolation.
        As t goes from 0 to 1, the Quat object goes from "from" to "to". */
        void slerp(value_type  t, const Quat& from, const Quat& to)
        {
            const double epsilon = 0.00001;
            double omega, cosomega, sinomega, scale_from, scale_to;

            Quat quatTo(to);
            // this is a dot product

            cosomega = from.asVec4() * to.asVec4();

            if (cosomega <0.0)
            {
                cosomega = -cosomega;
                quatTo = -to;
            }

            if ((1.0 - cosomega) > epsilon)
            {
                omega = acos(cosomega);  // 0 <= omega <= Pi (see man acos)
                sinomega = sin(omega);  // this sinomega should always be +ve so
                                        // could try sinomega=sqrt(1-cosomega*cosomega) to avoid a sin()?
                scale_from = sin((1.0 - t)*omega) / sinomega;
                scale_to = sin(t*omega) / sinomega;
            }
            else
            {
                /* --------------------------------------------------
                The ends of the vectors are very close
                we can use simple linear interpolation - no need
                to worry about the "spherical" interpolation
                -------------------------------------------------- */
                scale_from = 1.0 - t;
                scale_to = t;
            }

            *this = (from*scale_from) + (quatTo*scale_to);
            // so that we get a Vec4
        }

        /** Rotate a vector by this quaternion.*/
        Vec3f operator* (const Vec3f& v) const
        {
            // nVidia SDK implementation
            Vec3f uv, uuv;
            Vec3f qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv;
            uv *= (2.0f * _v[3]);
            uuv *= 2.0f;
            return v + uv + uuv;
        }

        /** Rotate a vector by this quaternion.*/
        Vec3d operator* (const Vec3d& v) const
        {
            // nVidia SDK implementation
            Vec3d uv, uuv;
            Vec3d qvec(_v[0], _v[1], _v[2]);
            uv = qvec ^ v;
            uuv = qvec ^ uv;
            uv *= (2.0f * _v[3]);
            uuv *= 2.0f;
            return v + uv + uuv;
        }

    protected:

    }; 
}
