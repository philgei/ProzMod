#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoNPyramid : public CGeoTriangleList
{
	CGeoNPyramid();

	std::vector<CVertex> m_avertexNPyramid;

	int index = 0;
	CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);

	void TriangleAdd(CVertex vec1, CVertex vec2, CVertex vec3);
private:
	CVertex top;
	CVertex bot;
	void initTopBot();
	void AddGroundAndFace(CVertex vec1, CVertex vec2);
};

