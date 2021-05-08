#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoCogwheel : public CGeoTriangleList
{
public:
	CGeoCogwheel(float outterRadius, float innerRadius, float height, int numberOfGearPinions);
	~CGeoCogwheel();
	//CVertex* m_avertexCogwheel;
private:
	float m_outterRadius;
	float m_innerRadius;
	float m_height;
	float m_numberOfGearPinions;
	float radOfDisplacement;
	//int index;
	
	CHVector top;
	CHVector bot;
	CHVector mid;
	CHVector left;
	CHVector right;
	CHVector tangent;
	void init();
	void AddBot(float deg);
	void AddLeft(float deg);
	void AddRight(float deg);
	void AddTop(float deg);
	void VertexAdd(CHVector pos, CHVector normal);
	void TriangleAdd(CHVector vec1, CHVector vec2, CHVector vec3);
	CHVector rotateY(float angle, CHVector vec);
	CHVector translateY(float delta, CHVector vec);
	CHVector getFaceNormal(CHVector vec1, CHVector vec2, CHVector vec3);
};

