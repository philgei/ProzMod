#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class Util
{
public:
	Util();
	~Util();
	static CHVector getFaceNormal(CHVector vec1, CHVector vec2, CHVector vec3);
	static CHVector rotateZ(CHVector vec, float degree);
	static float degToRad(float deg);
	static float radToDeg(float rad);
};

