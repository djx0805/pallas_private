#pragma once
#include "..\PallasMath\Mat4.h"
#include "Referenced.h"

namespace pallas
{
#ifdef  _USE_FLOAT_MATRIX
	typedef Mat4f Matrix;
#else
	typedef Mat4d Matrix;
#endif //  FLOAT_MATRIX

	//
	class RefMatrix : public Referenced, public Matrix
	{
	public:
		RefMatrix() {}
		RefMatrix(const Matrix& m) : Matrix(m) {}
	};
}