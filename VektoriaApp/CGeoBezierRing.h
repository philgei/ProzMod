#pragma once
#include "Vektoria\Root.h"
#include "Util.h"

class CGeoBezierRing :
    public CGeoBezierTable
{
public:
    CGeoBezierRing(float radiusInner, float radiusOutter, float height);
    ~CGeoBezierRing();
private:
    CHVector m_aav[4][4];
    Util util;
};

