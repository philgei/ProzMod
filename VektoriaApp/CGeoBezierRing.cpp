#include "CGeoBezierRing.h"

CGeoBezierRing::CGeoBezierRing(float radiusInner, float radiusOutter, float height)
{
	float radiusAdd = (radiusOutter - radiusInner) / 2.0f; //radiusOutter / radiusInner * 3;
	//float radiusFactor = radiusOutter / radiusInner * 3;
	for (int j = 0; j < 4; j++) {
		float radius = radiusInner;
		float heightFactor = height / 3;
		for (int i = 0; i < 4; i++) {
			float degBegin = j * 90.0f; 
			CHVector stanni = CHVector(radius, 0, i * heightFactor, 1.0f);
			CHVector mid = CHVector(radius, radius * 0.56f, i * heightFactor, 1.0f);
			m_aav[0][i] = Util::rotateZ(stanni, degBegin); // * radius // is save
			m_aav[1][i] = Util::rotateZ(mid, degBegin + 0.0f); 
			m_aav[2][i] = Util::rotateZ(mid, degBegin + 30.0f);
			m_aav[3][i] = Util::rotateZ(stanni, degBegin + 90.0f); // is save
			if (i < 2) radius += radiusAdd;
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


