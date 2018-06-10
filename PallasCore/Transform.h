#pragma once
#include "SceneNode.h"
#include "..\PallasMath\Vec3.h"
#include "Matrix.h"

namespace pallas
{
	class Transform : public SceneNode::Attribute
	{
	public:
		Transform() {
			mName = "transform";
			mPos = Vec3d(0, 0, 0);
			mRotate = Vec3d(0, 0, 0);
			mScale = Vec3d(1, 1, 1);
		}

		void SetPosition(double x, double y, double z) {
			mPos = Vec3d(x, y, z);
		}
		Vec3d GetPosition() {
			return mPos;
		}

		void SetRotate(double x, double y, double z) {
			mRotate = Vec3d(x, y, z);
		}
		Vec3d GetRotate() {
			return mRotate;
		}

		void SetScale(double x, double y, double z) {
			mScale = Vec3d(x, y, z);
		}
		Vec3d GetScale() {
			return mScale;
		}

		Matrix GetTransformMatrix() {
			Matrix mt_r;
			mt_r.makeRotate(mRotate.x(), mRotate.y(), mRotate.z());
			//
			Matrix mt_s;
			mt_s.makeScale(mScale);
			//
			Matrix mt_t;
			mt_t.makeTranslate(mPos);
			//
			return mt_r*mt_s*mt_t;
		}
	private:
		Vec3d mPos;
		Vec3d mRotate;
		Vec3d mScale;
	};
}