#pragma once
#include "Vektoria\Root.h"

using namespace Vektoria;
class CGeoDreamCatcher: public CGeoLineList
{
public:
	CGeoDreamCatcher(float fRadius);

	CVertex m_avertexCircle[360];
};

