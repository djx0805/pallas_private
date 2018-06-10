#pragma once
#include "Export.h"
#include "Object.h"
#include "..\PallasGFL\BoundingBox.h"
#include "..\PallasGFL\BoundingSphere.h"
#include <unordered_map>

namespace pallas
{
	class PALLASCORE_API SceneNode : public Object
	{
	public:
		class Attribute : public Object
		{
		public:
			Attribute() {}
			virtual ~Attribute() {}
		};
	public:
		SceneNode() {}
		virtual ~SceneNode() {}
		//
		virtual void AddAttribute(Attribute* pattri) {
			mAttributes[pattri->GetID()] = pattri;
		}

		virtual Attribute* GetAttribute(const char* name) {
			auto itr = mAttributes.find(name);
			if (itr == mAttributes.end())
				return nullptr;
			//
			return itr->second.get();
		}

		virtual void RemoveAttribute(const char* name) {
			mAttributes.erase(name);
		}
	protected:
	private:
		std::unordered_map<std::string, pallas::ref_ptr<Attribute>> mAttributes;
	};
}