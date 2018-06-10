#pragma once
#include "SceneNode.h"
#include "..\PallasMath\Vec3.h"

namespace pallas
{
	class LightSource : public SceneNode
	{
	public:
		LightSource() {}
	protected:
		virtual ~LightSource(){}
	};

	class DirectLight : public LightSource
	{
	public:
		DirectLight() {
			mColor = Vec4f(1.0, 1.0, 1.0, 1.0);
			mDirection = Vec3f(-1, -1, -1);
		}
		//
		void SetDirection(Vec3f& dir) {
			mDirection = dir;
		}

		Vec3f GetDirecton() {
			return mDirection;
		}

		void SetColor(Vec4f color) {
			mColor = color;
		}

		Vec4f GetColor() {
			return mColor;
		}
	private:
		Vec3f mDirection;
		Vec4f mColor;
	};
}
