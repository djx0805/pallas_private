#pragma once
#include "Drawable.h"
#include "..\PallasGFL\GeometryBase.h"
#include <memory>
namespace pallas
{
    class PALLASCORE_API ShapeDrawable : public Drawable
    {
    public:
        ShapeDrawable() {}

        virtual ~ShapeDrawable() {}
        //
        void SetShape(gfl::ISolid* pshape) {
            mShape = std::shared_ptr<gfl::ISolid>(pshape);
        }
        void SetShape(const std::shared_ptr<gfl::ISolid>& shape) {
            mShape = shape;
        }
        gfl::ISolid* GetShape() {
            return mShape.get();
        }
        std::shared_ptr<gfl::ISolid>& GetShapeRef() {
            return mShape;
        }
    protected:
        std::shared_ptr<gfl::ISolid> mShape;
    };
}