#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"
#include "CGeoPointCircle.h"
#include "CGeoDreamCatcher.h"
#include "CGeoPyramid.h"
#include "CGeoNPyramid.h"
#include "CGeoBezierRing.h"
#include "CGeoSierpinskyTriangle.h"
#include "CGeoCogwheel.h"
#include "CGeoGanjaPlant.h"
#include "PlantGanja.h"

using namespace Vektoria;


class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird w�hrend der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergr��e ver�ndert hat

private:
    // Hier ist Platz f�r Deine Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CPlacement m_zpSphere;
	CPlacement m_zpCircle;
	CGeoSphere m_zgSphere;
	CFrame m_zf;
	CViewport m_zv;
	CCamera m_zc;
	CLightParallel m_zl;

	CDeviceKeyboard m_zdk;
	CMaterial m_zm;

	CPlacement m_pSky;
	CGeoSphere m_gSky;

	/*CPlacement m_placeGanja;
	CGeoGanjaPlant m_GeoGanjaPlant;*/

	CPlacement m_placementCogwheel;
	CGeoCogwheel* m_geoCogwheel = new CGeoCogwheel(4,3,2,32);
};


