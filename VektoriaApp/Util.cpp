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

    //return normal;

    normal = crossA ^ crossB;
    normal.Norm();

    return  normal;
}

CHVector Util::rotateZ(CHVector vec, float degree)
{
    float x = vec.GetX() * cos(degToRad(degree)) - vec.GetY() * sin(degToRad(degree));
    float y = vec.GetX() * sin(degToRad(degree)) + vec.GetY() * cos(degToRad(degree));
    return CHVector(x, y, vec.GetZ(), vec.GetW());
}

float Util::degToRad(float deg)
{
    return deg * PI / 180.f;
}

float Util::radToDeg(float rad)
{
    return rad / PI * 180.f;
}
