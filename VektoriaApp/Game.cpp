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

	//m_zm.LoadPreset("Sun");
	m_zm.MakeTextureGlow("textures\\ENV.jpg");
	//m_zm.SetGlowStrength(30);

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

	m_zv.SetBloomOn();

	m_zv.SetBackfaceCullingOff();



	/*m_GeoGanjaPlant.SetRandomSeed(1337);

	m_GeoGanjaPlant.Iterate(10);
	m_GeoGanjaPlant.Init(&m_GeoGanjaPlant);

	m_zs.AddPlacement(&m_placeGanja);
	m_placeGanja.AddGeo(&m_GeoGanjaPlant);*/

	//m_zv.SetBackfaceCullingOff();
	m_zv.SetBackfaceCullingOn();

	//m_zs.AddPlacement(&m_placementCogwheel);
	//m_placementCogwheel.AddGeo(m_geoCogwheel);


	m_zpCamera.Translate(10, 0, 100);


	m_zpCamera.SetTranslationSensitivity(50);
	m_zpCamera.SetRotationSensitivity(1);

	m_pTropical.init();

	m_zs.AddPlacement(&m_pTropical);

	m_Birke.SetRandomSeed(42);
	m_Birke.Iterate(10.0f, 0.40f, 0.0f);
	m_Birke.Init(&m_Birke, 0);

	m_zs.AddPlacement(&m_pBirke);

	//float height = m_pTropical.m_zgTerrain.GetHeight(20, 20);

	//m_pBirke.Translate(20, height, 20);

	m_pBirke.AddGeo(&m_Birke);

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	//m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);


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


	//m_placeGanja.RotateY(fTime);
	//m_placementCogwheel.RotateY(fTime);

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

