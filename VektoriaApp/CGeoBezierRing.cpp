#include "CGeoBezierRing.h"

CGeoBezierRing::CGeoBezierRing(float radius)
{
	int numberOfCuts = 3;

	for (int outter = 0; outter < 4; outter++) {
		float add = outter * 90;
		float r = radius;
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				float deg = (float)j / (float)numberOfCuts * 90.f;
				deg += add;
				float z = sin(deg * PI / 180.f);
				float x = cos(deg * PI / 180.f);
				m_aav[i][j] = CHVector(x, z, radius, 1.0f);
			}
			r *= 1.1f;
			//radius *= 1.68f;
		}
		AddPatch(m_aav, 20, 20);
	}

	Init();
}

CGeoBezierRing::~CGeoBezierRing()
{
}


