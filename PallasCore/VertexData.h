#pragma once
#include "ref_ptr.h"
#include "VecArray.h"

namespace pallas
{
	enum  PrimitiveType
	{
		PT_POINTS,
		PT_LINES,
		PT_LINE_STRIP,
		PT_LINE_LOOP,
		PT_TRIANGLES,
		PT_TRIANGLE_STRIP,
		PT_TRIANGLE_FAN
	};

	class VertexData : public Referenced
	{
	public:
		VertexData() {}
		~VertexData() {}
		//
		void SetVertexArray(RefVecArray3f* va) {
			mVertexArray = va;
		}
		RefVecArray3f* GetVertexArray() {
			return mVertexArray.get();
		}

		void SetNormalArray(RefVecArray3f* na) {
			mNormalArray = na;
		}
		RefVecArray3f* GetNormalArray() {
			return mNormalArray.get();
		}

		int GetNumColor() {
			return mColors.size();
		}
		void AddColorArray(RefVecArray4f* ca) {
			mColors.push_back(ca);
		}
		RefVecArray4f* GetColorArray(int index) {
			return mColors[index].get();
		}

		int GetNumTextureCoord() {
			return mTextureCoords.size();
		}
		void AddTextureCoords(RefVecArray2f* tca) {
			mTextureCoords.push_back(tca);
		}
		RefVecArray2f* GetTextureCoords(int index) {
			return mTextureCoords[index].get();
		}

		void SetElementArray(RefVecArrayui* ea) {
			mElementArray = ea;
		}
		RefVecArrayui* GetElementArray() {
			return mElementArray.get();
		}

		void SetPrimitiveType(PrimitiveType pt) {
			mPrimitiveType = pt;
		}
		PrimitiveType GetPrimitiveType() {
			return mPrimitiveType;
		}
	protected:
		pallas::ref_ptr<RefVecArray3f> mVertexArray;
		pallas::ref_ptr<RefVecArray3f> mNormalArray;
		pallas::ref_ptr<RefVecArrayui> mElementArray;
		std::vector<pallas::ref_ptr<RefVecArray4f> > mColors;
		std::vector<pallas::ref_ptr<RefVecArray2f> > mTextureCoords;
		PrimitiveType mPrimitiveType;
	};
}