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
	// m_zf.SetApiRender(eApiRender_DirectX11_Shadermodel50_Monolight);
	m_zf.Init(hwnd, procOS); 
	m_zv.InitFull(&m_zc);
	m_zl.Init(CHVector(1.0f, 1.0f, 1.0f), CColor(1.0f, 1.0f, 1.0f));
	//m_zgSphere.Init(1.5F, nullptr, 50, 50);

	m_zf.AddDeviceKeyboard(&m_zdk);

	//m_zm.LoadPreset("Sun");
	m_zm.MakeTextureGlow("textures\\ENV.jpg");
	//m_zm.SetGlowStrength(30);

	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);
	m_zs.AddPlacement(&m_zpSphere);
	m_zs.AddPlacement(&m_zpCamera);
	m_zs.AddPlacement(&m_zpCircle);
	m_zs.AddLightParallel(&m_zl);
	m_zpCamera.AddCamera(&m_zc);
	
	m_zs.AddPlacement(&m_pSky);
	
	/*m_pSky.AddGeo(&m_gSky);
	m_pSky.SetSky();
	m_gSky.Init(500, nullptr);
	m_gSky.Flip();*/

	//m_zpSphere.AddGeo(&m_zgSphere);
	//m_zs.AddPlacement(&m_pGrid);

	//m_pGrid.TranslateZ(-20.f);
	//m_pGrid.AddGeo(&m_gGrid);
	//m_gGrid.SetAxis(eAxisZ);
	//m_gGrid.Init(20,20, nullptr, 20, 20);


	m_zpCircle.AddGeo(pzgPointCircle);
	pzgPointCircle->SetMaterial(&m_zm);
	m_zv.SetBloomOn();

	m_zv.SetBackfaceCullingOff();

	m_zs.AddPlacement(&M_PlaceRing);
	M_PlaceRing.AddGeo(m_gRing);

	m_zv.SetBackfaceCullingOff();
	//m_zv.SetWireframeOn();

	//m_zs.AddPlacement(&m_pNPyramide);
	//m_pNPyramide.AddGeo(m_gNPyramide);

	//m_zs.AddPlacement(&m_PlacePyramid);
	//m_PlacePyramid.AddGeo(m_Pyramid);
	//m_Pyramid->SetMaterial(&m_zm);
	

	//m_zv.SetBloomWidth(2);
	//m_zv.SetBloomStrengthFar(50);
	//m_zv.SetBloomStrengthNear(50);


	m_zpCamera.TranslateZ(30.0f);

	//m_zpCamera.TranslateY(2.0f);
	//m_zpCamera.RotateX(-2.0f);


}

void CGame::Tick(float fTime, float fTimeDelta)
{

	//m_PlacePyramid.RotateY(fTime);
	//m_PlacePyramid.RotateXDelta(fTime*13.45);
	//m_pNPyramide.RotateY(fTime);

	//M_PlaceRing.RotateY(fTime);

	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);
	// Hier die Echtzeit-Veränderungen einfügen:
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

