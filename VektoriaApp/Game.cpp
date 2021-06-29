#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	// Hier die Initialisierung Deiner Vektoria-Objekte einfügen:
	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);

	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);

	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));

	m_zf.AddDeviceKeyboard(&m_zdk);

	m_zs.SetSkyOn(&m_zpCamera);
	//m_zs.SetSkyFlowOn(1200);

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddPlacement(&m_zpSphere);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddPlacement(&m_zpCircle);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	
	m_zs.AddPlacement(&m_pSky);

	m_zv.SetBackfaceCullingOff();


	m_zpCamera.SetTranslationSensitivity(50);
	m_zpCamera.SetRotationSensitivity(1);
	//Insel
	m_pTropical.init();
	m_zs.AddPlacement(&m_pTropical);
	//Boot
	m_Boat.Translate(-130.60f, 1.5f, -161.6);
	m_Boat.Init();
	m_zs.AddPlacement(&m_Boat);
	//Hütte
	m_Hut.build();
	m_Hut.Translate(-78, 4, -60);
	
	m_zs.AddPlacement(&m_Hut);

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	//m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);

	camPostForDebug = m_zpCamera.GetPos();

	m_zdk.PlaceWASDTerrain(
		m_zpCamera,
		m_pTropical.m_gCol,
		m_pTropical.m_gHeight,
		m_pTropical.m_gsTerrain,
		4.0f,
		3000.0f,
		m_HitpointCollision,
		m_HitpointGround,
		fTimeDelta);


	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

