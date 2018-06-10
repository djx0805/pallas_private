#pragma once
#include "GeometryBase.h"
#include "..\PallasMath\Vec3.h"
namespace pallas
{
namespace gfl
{
    class StandardPrimitives : public ISolid
    {
    public:
        StandardPrimitives() {}
        virtual ~StandardPrimitives() {}
    };

    class Sphere : public StandardPrimitives
    {
    public:
        Sphere() {}
        virtual ~Sphere() {}
        //
        void setCenter(const Vec3d& center)
        {
            mCenter = center;
        }
        Vec3d getCenter()
        {
            return mCenter;
        }

        void setRadius(double radius)
        {
            mRadius = radius;
        }
        double getRadius()
        {
            return mRadius;
        }
    private:
        Vec3d mCenter;
        double  mRadius;
    };

    class GeoSphere : public StandardPrimitives
    {

    };

    class Box : public StandardPrimitives
    {
    public:
        Box() {}
        virtual ~Box() {}
        //
        void setCenter(const Vec3d& center)
        {
            mCenter = center;
        }
        Vec3d getCenter()
        {
            return mCenter;
        }

        void setLength(double length)
        {
            mLength = length;
        }
        double getLength()
        {
            return mLength;
        }

        void setWidth(double width)
        {
            mWidth = width;
        }
        double getWidth()
        {
            return mWidth;
        }

        void setHeight(double height)
        {
            mHeight = height;
        }
        double getHeight()
        {
            return mHeight;
        }
    private:
        Vec3d mCenter;
        double mLength;
        double mWidth;
        double mHeight;
    };

    class Cone : public StandardPrimitives
    {

    };

    class Cylinder : public StandardPrimitives
    {

    };

    class Tube : public StandardPrimitives
    {

    };

    class Torus : public StandardPrimitives
    {

    };

    class Pyramid : public StandardPrimitives
    {

    };

    class Teapot : public StandardPrimitives
    {

    };

    class Plane : public StandardPrimitives
    {

    };

    class TextPlus : public StandardPrimitives
    {

    };
}
    
}