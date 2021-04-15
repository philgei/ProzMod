#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class CGeoPintCircle : public CGeoPointList
{
public:
	CGeoPintCircle(float fRadius);

	CVertex m_avertexCircle[360];
};

