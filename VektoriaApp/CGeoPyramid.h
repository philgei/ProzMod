#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoPyramid : public CGeoTriangleList
{
public:
	CGeoPyramid();

	CVertex m_avertexPyramid[18];

	int index = 0;
	CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);

	void VertexAdd(CHVector pos);
};

