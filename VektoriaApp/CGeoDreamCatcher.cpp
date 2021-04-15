#include "CGeoDreamCatcher.h"

CGeoDreamCatcher::CGeoDreamCatcher(float fRadius)
{
	for (int i = 0; i < 360; i++)
	{

		float fr = ((float)i / 360);
		float fa = fr * TWOPI;

		CHVector vPos = CHVector(fRadius * sin(fa), fRadius * cos(fa), 0.0f, 1.0f);
		CHVector vNormal = vPos;
		vNormal.Normal();

		CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);

		float fu = fr;
		float fv = 0.0f;

		m_avertexCircle[i].Init(vPos, vNormal, vTangent, fu, fv);

		AddVertex(&m_avertexCircle[i]);

		for (int j = i; j < 360; j++)
		{

		}

	}
	Init();
}
