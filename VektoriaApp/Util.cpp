#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

CHVector Util::getFaceNormal(CHVector vec1, CHVector vec2, CHVector vec3)
{
    CHVector crossA = CHVector(vec2.GetX() - vec1.GetX(), vec2.GetY() - vec1.GetY(), vec2.GetZ() - vec1.GetZ(), 0.f);
    CHVector crossB = CHVector(vec3.GetX() - vec1.GetX(), vec3.GetY() - vec1.GetY(), vec3.GetZ() - vec1.GetZ(), 0.f);

    float top = crossA.GetY() * crossB.GetZ() - crossA.GetZ() * crossB.GetY();
    float mid = crossA.GetZ() * crossB.GetX() - crossA.GetX() * crossB.GetZ();
    float bot = crossA.GetX() * crossB.GetY() - crossA.GetY() * crossB.GetX();

    CHVector normal = CHVector(top, mid, bot, 0.0f);
    normal.Norm();

    return normal;
}
