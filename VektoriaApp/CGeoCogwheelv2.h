#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoCogwheelv2 : public CGeoTriangleList
{
public:
	CGeoCogwheelv2(float outterRadius, float depth, float height, int numberOfGearPinions);
	~CGeoCogwheelv2();
	//CVertex* m_avertexCogwheel;
private:
	float m_outterRadius;
	float m_innerRadius;
	float m_height;
	float m_numberOfGearPinions;
	float radOfDisplacement;
	float m_outterDistance;
	float m_innerDistance;
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

