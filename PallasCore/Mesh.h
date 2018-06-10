#pragma once
#include "Drawable.h"
#include "VertexData.h"

namespace pallas
{
	class Mesh : public Drawable
	{
	public:
		Mesh() {}
		virtual ~Mesh() {}
		//
		virtual void SetVertexArray(RefVecArray3f* va) {
			mVertexData->SetVertexArray(va);
		}
		virtual  RefVecArray3f* GetVertexArray() {
			return mVertexData->GetVertexArray();
		}

		virtual void SetNormalArray(RefVecArray3f* na) {
			mVertexData->SetNormalArray(na);
		}
		virtual RefVecArray3f* GetNormalArray() {
			return mVertexData->GetNormalArray();
		}

		virtual int GetNumColor() {
			return mVertexData->GetNumColor();
		}
		virtual void AddColorArray(RefVecArray4f* ca) {
			mVertexData->AddColorArray(ca);
		}
		virtual RefVecArray4f* GetColorArray(int index) {
			return mVertexData->GetColorArray(index);
		}

		virtual int GetNumTextureCoord() {
			return mVertexData->GetNumTextureCoord();
		}
		virtual void AddTextureCoords(RefVecArray2f* tca) {
			mVertexData->AddTextureCoords(tca);
		}
		virtual RefVecArray2f* GetTextureCoords(int index) {
			return mVertexData->GetTextureCoords(index);
		}

		virtual void SetElementArray(RefVecArrayui* ea) {
			mVertexData->SetElementArray(ea);
		}
		virtual RefVecArrayui* GetElementArray() {
			return mVertexData->GetElementArray();
		}

		virtual void SetPrimitiveType(PrimitiveType pt) {
			mVertexData->SetPrimitiveType(pt);
		}
		virtual PrimitiveType GetPrimitiveType() {
			return mVertexData->GetPrimitiveType();
		}

		virtual VertexData* GetOrBuildVertexData() override {
			return mVertexData.get();
		}
	protected:
		pallas::ref_ptr<VertexData> mVertexData;
	};
}