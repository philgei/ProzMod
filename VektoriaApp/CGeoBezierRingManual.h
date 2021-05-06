#pragma once
#include "Vektoria\Root.h"
#include "Util.h"

class CGeoBezierRingManual : public CGeoBezierTable
{
public:
	CGeoBezierRingManual();
	~CGeoBezierRingManual();
private:
	CHVector m_aav[4][4];
};

