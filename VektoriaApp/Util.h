#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class Util
{
public:
	Util();
	~Util();
	CHVector getFaceNormal(CHVector vec1, CHVector vec2, CHVector vec3);
};
