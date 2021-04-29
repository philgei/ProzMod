#include "CGeoBezierRing.h"

CGeoBezierRing::CGeoBezierRing(float radius)
{
	int numberOfCuts = 3;

	//for (int outter = 0; outter < 4; outter++) {
	//	float add = outter * 90;
	//	float r = radius;
	//	for (int i = 0; i < 4; i++) 
	//	{
	//		for (int j = 0; j < 4; j++) 
	//		{
	//			float deg = (float)j / (float)numberOfCuts * 90.f;
	//			deg += add;
	//			float z = sin(deg * PI / 180.f);
	//			float x = cos(deg * PI / 180.f);
	//			m_aav[i][j] = CHVector(x, z, radius, 1.0f);
	//		}
	//		r *= 1.1f;
	//		//radius *= 1.68f;
	//	}
	//	AddPatch(m_aav, 20, 20);
	//}
	

	//for (int j = 0; j < 4; j++) {
	//	float deg = j * 90.0f;
	//	float height = 2.4f;
	//	radius = 1.5f;
	//	for (int i = 0; i < 4; i++) {
	//		//float deg = i * 30.0f;
	//		float displacement = radius * sin((deg + 30.f) * PI / 180.0f);
	//		if (j % 2 == 1) displacement = radius * cos((deg + 30.f) * PI / 180.0f);
	//		float x = sin(deg * PI / 180.0f) * radius;
	//		float y = cos(deg * PI / 180.0f) * radius;
	//		float x2 = sin((deg - 90.f) * PI / 180.0f) * radius;
	//		float y2 = cos((deg - 90.f) * PI / 180.0f) * radius;
	//		m_aav[0][i] = CHVector(x, y, height, 1.0f);
	//		m_aav[1][i] = CHVector(x, displacement, height, 1.0f);
	//		m_aav[2][i] = CHVector(displacement, x, height, 1.0f);
	//		m_aav[3][i] = CHVector(x2, y2, height, 1.0f);
	//		height += 0.2f;
	//		radius += 0.25f;
	//		//if (radius > 2.0f) radius = 2.0f;
	//	}
	//	AddPatch(m_aav, 20, 20);
	//}

	for (int j = 0; j < 4; j++) {
		float height = 2.4f;
		float radius = 1.0f;
		for (int i = 0; i < 4; i++) {
			float degreeOfBegin = j * 90.0f; 
			float rightY = sin(degreeOfBegin * PI / 180.f);
			float rightX = cos(degreeOfBegin * PI / 180.f);
			float leftY = sin((degreeOfBegin + 90.f) * PI / 180.f);
			float leftX = cos((degreeOfBegin + 90.f) * PI / 180.f);
			float sinus = sin(degreeOfBegin * PI / 180.f);
			float cosinus = cos(degreeOfBegin * PI / 180.f);

			float cosinus0 = cos(degreeOfBegin * PI / 180.f);
			float sinus0 = sin(degreeOfBegin * PI / 180.f);
			float cosinus30 = cos((degreeOfBegin + 30.f) * PI / 180.f);
			float sinus30 = sin((degreeOfBegin + 30.f) * PI / 180.f);
			float sinus90 = sin((degreeOfBegin + 90.f) * PI / 180.f);
			float cosinus90 = cos((degreeOfBegin + 90.f) * PI / 180.f);
			float displacement = cos(30.0f * PI / 180.f);// *radius;
			m_aav[0][i] = CHVector(cosinus0, sinus0, height, 1.0f); // * radius // is save

			m_aav[1][i] = CHVector(cosinus0 + sinus0 * displacement,
							sinus0, height, 1.0f);
			m_aav[2][i] = CHVector(sinus0 + cosinus0 * displacement, sinus90, height, 1.0f);

			m_aav[3][i] = CHVector(cosinus90, sinus90, height, 1.0f); // is save
		}
		AddPatch(m_aav, 20, 20);
	}

	

	

	Init();

	CMaterial* pzm = new CMaterial();
	pzm->LoadPreset("MetalRustyFlaking");
	SetMaterial(pzm);
}

CGeoBezierRing::~CGeoBezierRing()
{
}


