#pragma once

#include "MixinVector.h"
#include "Referenced.h"
#include "..\PallasMath\Vec2.h"
#include "..\PallasMath\Vec3.h"
#include  "..\PallasMath\Vec4.h"

namespace pallas
{
	template<typename VT>
	class RefVecArray : public MixinVector<VT>, public Referenced
	{
	public:
		RefVecArray() {};
		RefVecArray(size_type initial_size, const value_type& fill_value = value_type()) : MixinVector(initial_size, fill_value) {}
		~RefVecArray() {}
	};

	typedef MixinVector<int> VecArrayi;
	typedef MixinVector<float> VecArrayf;
	typedef MixinVector<double> VecArrayd;
	typedef MixinVector<short> VecArrays;
	typedef MixinVector<char> VecArrayb;
	typedef MixinVector<unsigned int> VecArrayui;
	typedef MixinVector<unsigned short> VecArrayus;
	typedef MixinVector<unsigned char> VecArrayub;
	//
	typedef RefVecArray<int> RefVecArrayi;
	typedef RefVecArray<float> RefVecArrayf;
	typedef RefVecArray<double> RefVecArrayd;
	typedef RefVecArray<short> RefVecArrays;
	typedef RefVecArray<char> RefVecArrayb;
	typedef RefVecArray<unsigned int> RefVecArrayui;
	typedef RefVecArray<unsigned short> RefVecArrayus;
	typedef RefVecArray<unsigned char> RefVecArrayub;

	typedef MixinVector<Vec2i> VecArray2i;
	typedef MixinVector<Vec2f> VecArray2f;
	typedef MixinVector<Vec2d> VecArray2d;
	typedef MixinVector<Vec2s> VecArray2s;
	typedef MixinVector<Vec2b> VecArray2b;
	typedef MixinVector<Vec2ui> VecArray2ui;
	typedef MixinVector<Vec2us> VecArray2us;
	typedef MixinVector<Vec2ub> VecArray2ub;
	//
	typedef RefVecArray<Vec2i> RefVecArray2i;
	typedef RefVecArray<Vec2f> RefVecArray2f;
	typedef RefVecArray<Vec2d> RefVecArray2d;
	typedef RefVecArray<Vec2s> RefVecArray2s;
	typedef RefVecArray<Vec2b> RefVecArray2b;
	typedef RefVecArray<Vec2ui> RefVecArray2ui;
	typedef RefVecArray<Vec2us> RefVecArray2us;
	typedef RefVecArray<Vec2ub> RefVecArray2ub;

	typedef MixinVector<Vec3i> VecArray3i;
	typedef MixinVector<Vec3f> VecArray3f;
	typedef MixinVector<Vec3d> VecArray3d;
	typedef MixinVector<Vec3s> VecArray3s;
	typedef MixinVector<Vec3b> VecArray3b;
	typedef MixinVector<Vec3ui> VecArray3ui;
	typedef MixinVector<Vec3us> VecArray3us;
	typedef MixinVector<Vec3ub> VecArray3ub;
	//
	typedef RefVecArray<Vec3i> RefVecArray3i;
	typedef RefVecArray<Vec3f> RefVecArray3f;
	typedef RefVecArray<Vec3d> RefVecArray3d;
	typedef RefVecArray<Vec3s> RefVecArray3s;
	typedef RefVecArray<Vec3b> RefVecArray3b;
	typedef RefVecArray<Vec3ui> RefVecArray3ui;
	typedef RefVecArray<Vec3us> RefVecArray3us;
	typedef RefVecArray<Vec3ub> RefVecArray3ub;

	typedef MixinVector<Vec4i> VecArray4i;
	typedef MixinVector<Vec4f> VecArray4f;
	typedef MixinVector<Vec4d> VecArray4d;
	typedef MixinVector<Vec4s> VecArray4s;
	typedef MixinVector<Vec4b> VecArray4b;
	typedef MixinVector<Vec4ui> VecArray4ui;
	typedef MixinVector<Vec4us> VecArray4us;
	typedef MixinVector<Vec4ub> VecArray4ub;
	//
	typedef RefVecArray<Vec4i> RefVecArray4i;
	typedef RefVecArray<Vec4f> RefVecArray4f;
	typedef RefVecArray<Vec4d> RefVecArray4d;
	typedef RefVecArray<Vec4s> RefVecArray4s;
	typedef RefVecArray<Vec4b> RefVecArray4b;
	typedef RefVecArray<Vec4ui> RefVecArray4ui;
	typedef RefVecArray<Vec4us> RefVecArray4us;
	typedef RefVecArray<Vec4ub> RefVecArray4ub;
}