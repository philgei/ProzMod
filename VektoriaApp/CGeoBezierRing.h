#pragma once
#include "Vektoria\Root.h"
#include "Util.h"

class CGeoBezierRing :
    public CGeoBezierTable
{
public:
    CGeoBezierRing(float radius);
    ~CGeoBezierRing();
private:
    CHVector m_aav[4][4];
};
