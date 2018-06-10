#pragma once
#include "GeometryBase.h"
namespace pallas
{
namespace gfl
{
    class SimpleGeom
    {
    public:
        SimpleGeom() {}
        virtual ~SimpleGeom() {}
    };

    class Point : public IPoint, public SimpleGeom
    {

    };

    class Linestring : public ILine, public SimpleGeom
    {

    };

    class Polygon : public ISurface, public SimpleGeom
    {

    };
}
}