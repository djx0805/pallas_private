#pragma once
namespace pallas
{
namespace gfl
{
    class IGeometry
    {
    public:
        IGeometry() {};
        virtual ~IGeometry() {}
    };

    class IPoint : public IGeometry
    {
    public:
        IPoint() {}
        virtual ~IPoint() {}
    };

    class ILine : public IGeometry
    {
    public:
        ILine() {}
        virtual ~ILine() {}
    };

    class ISurface : public IGeometry
    {
    public:
        ISurface() {}
        virtual ~ISurface() {}
    };

    class ISolid : public IGeometry
    {
    public:
        ISolid() {}
        virtual ~ISolid() {}
    };
}
}