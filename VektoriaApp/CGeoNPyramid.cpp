#include "CGeoNPyramid.h"

CGeoNPyramid::CGeoNPyramid() {
	initTopBot();



	Init();
}

void CGeoNPyramid::TriangleAdd(CVertex vec1, CVertex vec2, CVertex vec3)
{
	//add only one Triangle
	//is called from Ground and Face Function to generate the 2 faces
}

void CGeoNPyramid::initTopBot()
{
	CHVector topPos = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
	CHVector botPos = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
	top.Init(topPos, topPos.Normal(), vTangent, 0.0f, 0.0f);
	bot.Init(botPos, botPos.Normal(), vTangent, 0.0f, 0.0f);
}

void CGeoNPyramid::AddGroundAndFace(CVertex vec1, CVertex vec2)
{
	TriangleAdd(vec1, vec2, top); //generate top Triangle
	TriangleAdd(vec1, bot, vec2); //generate bot Trianle
}

