#include "CGeoNPyramid.h"
#include <cmath>

CGeoNPyramid::CGeoNPyramid(float height, float radius) {
	this->height = height;
	this->radius = radius;
	initTopBot();

	for (int i = 0; i < numberOfCuts; i++) {
		float deg = (float)i / (float)numberOfCuts * 360.f;
		float z = sin(deg * PI / 180.f);
		float x = cos(deg * PI / 180.f);
		float deg2 = (float)(i + 1) / (float)numberOfCuts * 360.f;
		float z2 = sin(deg2 * PI / 180.f);
		float x2 = cos(deg2 * PI / 180.f);
		vecLeft = CHVector(x, 0.0f, z, 1.0f);
		vecRight = CHVector(x2, 0.0f, z2, 1.0f);
		AddGroundAndFace(vecLeft, vecRight);
	}

	Init();
}

void CGeoNPyramid::TriangleAdd(CHVector vec1, CHVector vec2, CHVector vec3)
{
	//add only one Triangle
	//is called from Ground and Face Function to generate the 2 faces

	CHVector normal = CHVector(); //get Triangle normal here
	normal = vec1.Normal();
	//get CrossProduct of Triangle //TODO LATER
	//use Normal of Crossproduct as Normal //TODO LATER
	//get Vector from vec1 to vec2 and use as Tangent //TODO LATER

	VertexAdd(vec1);
	VertexAdd(vec2);
	VertexAdd(vec3);

}

void CGeoNPyramid::initTopBot()
{
	top = CHVector(0.0f, height, 0.0f, 1.0f);
	bot = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
}

void CGeoNPyramid::AddGroundAndFace(CHVector vec1, CHVector vec2)
{
	TriangleAdd(vec1, vec2, top); //generate top Triangle
	TriangleAdd(bot, vec1, vec2); //generate bot Trianle
}

void CGeoNPyramid::VertexAdd(CHVector pos)
{
	/*CVertex vec = CVertex();
	vec.Init(pos, pos.Normal(), vTangent, 0.0f, 0.0f);
	AddVertex(&vec);*/

	m_avertexPyramid[index].Init(pos, pos.Normal(), vTangent, 0.0f, 0.0f);
	AddVertex(&m_avertexPyramid[index]);
	index++;
}

