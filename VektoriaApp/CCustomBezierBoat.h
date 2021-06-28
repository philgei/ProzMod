#pragma once
#include "Vektoria\Root.h"
#include "Util.h"

class CCustomBezierBoat :
	public CPlacement
{
public:
	CCustomBezierBoat(float lenght, float width, float height, float bugRoundness = 0.5f);
	~CCustomBezierBoat();

	void Init();

private:
	void setBaseGeoWithWithMirrow(bool mirrow, CGeoBezierTable& geo, CMaterial* mat);
	float stepWidth;
	float bugSchuwng;
	float halfWidth; 
	float m_height;
	
	CGeoBezierTable m_GeoRight;
	CGeoBezierTable m_GeoLeft;

	CGeoBezierTable m_GeoSeat1;


	Util util;
};

