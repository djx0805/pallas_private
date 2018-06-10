#pragma once
#include "Object.h"
#include <unordered_map>

namespace pallas
{
	class RenderSetting : public Referenced
	{
	public:
		enum  Type
		{
			RS_POLYGON_MODE
		};
		class Setting : public Referenced
		{
		public:
			Setting(Type type) { mType = type; }
			virtual ~Setting() {}
			Type GetType() { return mType; }
		private:
			Type mType;
		};
	public:
		class  PolygonMode : public Setting
		{
		public:
			enum Mode {
				POINT,
				LINE,
				FILL
			};

			enum Face {
				FRONT_AND_BACK,
				FRONT,
				BACK
			};

			PolygonMode() : Setting(Type::RS_POLYGON_MODE) {
				mModeFront = FILL;
				mModeBack = FILL;
			}

			PolygonMode(Face face, Mode mode) : Setting(Type::RS_POLYGON_MODE) {
				mModeFront = FILL;
				mModeBack = FILL;
				//
				if (face == FRONT) {
					mModeFront = mode;
				}
				else if (face == BACK) {
					mModeBack = mode;
				}
				else if (face == FRONT_AND_BACK) {
					mModeFront = mode;
					mModeBack = mode;
				}
			}

			PolygonMode(const PolygonMode& pm) : Setting(Type::RS_POLYGON_MODE) {
				mModeBack = pm.mModeBack;
				mModeFront = pm.mModeFront;
			}

			void setMode(Face face, Mode mode) {
				if (face == FRONT) {
					mModeFront = mode;
				}
				else if (face == BACK) {
					mModeBack = mode;
				}
				else if (face == FRONT_AND_BACK) {
					mModeFront = mode;
					mModeBack = mode;
				}
			}
			Mode getMode(Face face) const {
				if (face == FRONT) {
					return mModeFront;
				}
				else if (face == BACK) {
					return mModeBack;
				}
			}
		protected:
			virtual ~PolygonMode();

			Mode mModeFront;
			Mode mModeBack;
		};
		
	public:
		RenderSetting() {}
		virtual ~RenderSetting() {}
		//
		PolygonMode* getPolygonMode() {
			auto itr = mSettings.find(Type::RS_POLYGON_MODE);
			if (itr == mSettings.end())
				return nullptr;
			//
			return (PolygonMode*)itr->second.get();
		}
		void setPolygonMode(PolygonMode* pm) {
			mSettings[Type::RS_POLYGON_MODE] = pm;
		}
	private:
		std::unordered_map<Type, ref_ptr<Setting>> mSettings;
	};
}
