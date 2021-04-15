#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoNPyramid :
	public CGeoTriangleList
{
public:
	CGeoNPyramid(float height, float radius);
	CVertex m_avertexPyramid[8 * 4]; //4 is numberofCuts MUSS UNTEN AUCH GEÄNDERT WERDEN!

	int index = 0;
	CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);

	void TriangleAdd(CHVector vec1, CHVector vec2, CHVector vec3);
private:
	CHVector top;
	CHVector bot;
	void initTopBot();
	void AddGroundAndFace(CHVector vec1, CHVector vec2);
	void VertexAdd(CHVector pos);

	float height;
	float radius;
	int numberOfCuts = 4; // HIER AUCH ÄNDERN
	CHVector vecLeft;
	CHVector vecRight;

};

