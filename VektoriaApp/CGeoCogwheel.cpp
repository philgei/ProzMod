#include "CGeoCogwheel.h"

CGeoCogwheel::CGeoCogwheel(float outterRadius, float innerRadius, float height, int numberOfGearPinions)
{
	m_outterRadius = outterRadius;
	m_innerRadius = innerRadius;
	m_height = height;
	m_numberOfGearPinions = numberOfGearPinions;
	float degree = 360.0f / m_numberOfGearPinions; //bei 4 sollte hier 90 rauskommen
	init();
	for (int i = 0; i < m_numberOfGearPinions; i++) {
		// for each step DO:
		// 2 Bot Triangles bot -> mid -> left + bot -> right -> mid
		AddBot(i * degree);
		// 2 Top Triangles
		AddTop(i * degree);
		// 2 Left Triangles
		AddLeft(i * degree);
		// 2 Right Triangles
		AddRight(i * degree);
	}
	//AddBot(0.f);
}

CGeoCogwheel::~CGeoCogwheel()
{

}

void CGeoCogwheel::init()
{
	//m_avertexCogwheel = new CVertex[8 * m_numberOfGearPinions];
	float radOfDisplacement = 360.0f / m_numberOfGearPinions / 2.0f;
	top = CHVector(0.0f, m_height, 0.0f, 1.0f);
	bot = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
	mid = CHVector(m_outterRadius, 0, 0, 1.0f);

	left =	rotateY(radOfDisplacement,	CHVector(m_innerRadius, 0, 0, 1.0f));
	right = rotateY(-radOfDisplacement, CHVector(m_innerRadius, 0, 0, 1.0f));
}

void CGeoCogwheel::AddBot(float deg)
{
	// 2 Bot Triangles bot -> mid -> left + bot -> right -> mid
	CHVector midTmp = rotateY(deg, mid);
	CHVector leftTmp = rotateY(deg, left);
	CHVector rightTmp = rotateY(deg, right);
	TriangleAdd(bot, midTmp, leftTmp);
	TriangleAdd(bot, rightTmp, midTmp);
}

void CGeoCogwheel::AddLeft(float deg)
{
	CHVector midBot = rotateY(deg, mid);
	CHVector midTop = translateY(m_height, rotateY(deg, mid));

	CHVector leftBot = rotateY(deg, left);
	CHVector leftTop = translateY(m_height, rotateY(deg, left));

	// 2 Left Triangles LU -> MU -> MO + LU -> MO -> LO
	TriangleAdd(leftBot, midBot, midTop);
	TriangleAdd(leftBot, midTop, leftTop);

}

void CGeoCogwheel::AddRight(float deg)
{
	CHVector midBot = rotateY(deg, mid);
	CHVector midTop = translateY(m_height, rotateY(deg, mid));

	CHVector rightBot = rotateY(deg, right);
	CHVector rightTop = translateY(m_height, rotateY(deg, right));

	// 2 Left Triangles MU -> RU -> RO + MU -> RO -> MO
	TriangleAdd(midBot, rightBot, rightTop);
	TriangleAdd(midBot, rightTop, midTop);
}

void CGeoCogwheel::AddTop(float deg)
{
	CHVector midTmp = translateY(m_height, rotateY(deg, mid));
	CHVector leftTmp = translateY(m_height, rotateY(deg, left));
	CHVector rightTmp = translateY(m_height, rotateY(deg, right));
	TriangleAdd(top, midTmp, leftTmp);
	TriangleAdd(top, rightTmp, midTmp);
}

void CGeoCogwheel::VertexAdd(CHVector pos, CHVector normal)
{
	/*CVertex vertexAdd;
	vertexAdd.Init(pos, normal, tangent, 0.0f, 0.0f);*/

	CVertex* addVec = new CVertex();
	addVec->Init(pos, normal, tangent, 0.0f, 0.0f);
	AddVertex(addVec);

	/*m_avertexCogwheel[index].Init(pos, normal, tangent, 0.0f, 0.0f);
	AddVertex(&m_avertexCogwheel[index]);
	index++;*/
}

void CGeoCogwheel::TriangleAdd(CHVector vec1, CHVector vec2, CHVector vec3)
{
	CHVector normal = getFaceNormal(vec1, vec2, vec3); //get Triangle normal here
	//get CrossProduct of Triangle //TODO LATER
	//use Normal of Crossproduct as Normal //TODO LATER
	//get Vector from vec1 to vec2 and use as Tangent //TODO LATER

	VertexAdd(vec1, normal);
	VertexAdd(vec2, normal);
	VertexAdd(vec3, normal);
}

CHVector CGeoCogwheel::rotateY(float angle, CHVector vec)
{
	float x = vec.GetX() * cos(angle * PI / 180.f) - vec.GetZ() * sin(angle * PI / 180.f);
	float z = vec.GetX() * sin(angle * PI / 180.f) + vec.GetZ() * cos(angle * PI / 180.f);
	return CHVector(x, 0, z, 1.0f);
}

CHVector CGeoCogwheel::translateY(float delta, CHVector vec)
{
	return CHVector(vec.GetX(), vec.GetY() + delta, vec.GetZ(), vec.GetW());
}

CHVector CGeoCogwheel::getFaceNormal(CHVector vec1, CHVector vec2, CHVector vec3)
{
	CHVector crossA = CHVector(vec2.GetX() - vec1.GetX(), vec2.GetY() - vec1.GetY(), vec2.GetZ() - vec1.GetZ(), 0.f);
	CHVector crossB = CHVector(vec3.GetX() - vec1.GetX(), vec3.GetY() - vec1.GetY(), vec3.GetZ() - vec1.GetZ(), 0.f);

	float top = crossA.GetY() * crossB.GetZ() - crossA.GetZ() * crossB.GetY();
	float mid = crossA.GetZ() * crossB.GetX() - crossA.GetX() * crossB.GetZ();
	float bot = crossA.GetX() * crossB.GetY() - crossA.GetY() * crossB.GetX();

	CHVector normal = CHVector(top, mid, bot, 0.0f);
	normal.Norm();

	//return normal;

	normal = crossA ^ crossB;
	normal.Norm();

	return  normal;
}
