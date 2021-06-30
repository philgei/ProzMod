#include "CGeoCustomTropicalHut.h"

void CGeoCustomTropicalHut::build()
{
	m_WingHut.OpenSesamy("P@ntzai74!et)");
	//Materials
	m_MatWalls.LoadPreset("WoodPlanksBankirai");
	m_MatRoof.LoadPreset("Bark");
	m_MatRoofFacades.LoadPreset("WoodPlanksSpaced");

	//Grundriss erstellen________________________________________________________________
	float scaleFactor = 5;
	m_MainPrint.Add(&(CHVector(1, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(5, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(5, 0, -6) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-5, 0, -6) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-5, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-1, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-1, 0, 3) * scaleFactor));
	m_MainPrint.Add(&(CHVector(1, 0, 3) * scaleFactor));

	//Stützen erzeugen________________________________________________________________
	CHMat matPillarPlacement;
	//Die Hohen Stützen
	for (size_t a = 0; a < 6; a++)
	{
		m_aGeoPillars[a].Init(0.5, 0.5, 17, nullptr);
		m_aGeoPillars[a].SetMaterial(&m_MatWalls);
		m_aGeoPillars[a].SetTextureRepeat(5.5f, 5.5f); //Klappt nicht :(
		m_aWingPillars[a].AddGeo(&m_aGeoPillars[a]);
		matPillarPlacement.Translate(*m_MainPrint.m_aphvector[a]);
		matPillarPlacement.TranslateYDelta(-7.0f);
		m_WingHut.AddGeoWing(&m_aWingPillars[a], matPillarPlacement);
	}
	//Die Niedrigen Stützen
	for (size_t b = 6; b < 8; b++)
	{
		m_aGeoPillars[b].Init(0.5, 0.5, 10, nullptr);
		m_aWingPillars[b].AddGeo(&m_aGeoPillars[b]);
		m_aGeoPillars[b].SetMaterial(&m_MatWalls);
		matPillarPlacement.Translate(*m_MainPrint.m_aphvector[b]);
		matPillarPlacement.TranslateYDelta(-7.0f);
		m_WingHut.AddGeoWing(&m_aWingPillars[b], matPillarPlacement);
	}

	//Dach_____________________________________________________________
	CHMat matRoofPlacement;

	float heightPillars = 10;
	//Da die gesammtfläche nicht rechteckig ist, hier noch ein grundriss
	m_RoofPrint.Add(&((CHVector(5, 0, -1) * scaleFactor) + 
		CHVector(1,0,1)));
	m_RoofPrint.Add(&((CHVector(5, 0, -6) * scaleFactor) +
		CHVector(1, 0, -1)));
	m_RoofPrint.Add(&((CHVector(-5, 0, -6) * scaleFactor) +
		CHVector(-1, 0, -1)));
	m_RoofPrint.Add(&((CHVector(-5, 0, -1) * scaleFactor) +
		CHVector(-1, 0, 1)));


	matRoofPlacement.TranslateY(heightPillars);

	m_WingHut.AddGeoWing(&m_WingHutRoof, matRoofPlacement);

	m_WingHutRoof.SetPrint(&m_RoofPrint);
	m_WingHutRoof.SetHeightRoof(10);

	m_WingHutRoof.SetMaterialRoof(&m_MatRoof);
	m_WingHutRoof.SetMaterialFacade(&m_MatRoofFacades);
	m_WingHutRoof.SetTextureRepeat(2.5f, 2.5f);
	m_WingHutRoof.InitPrintTent();


	//Grundfläche mit Geländer________________________________________________________________
	m_WingHut.SetMaterials(&m_MatWalls, &m_MatWalls, &m_MatWalls, &m_MatWalls, &m_MatWalls);
	m_WingHut.SetPrint(&m_MainPrint);
	m_WingHut.SetSizePrint(1, 1);
	//Glaubt man zwar nicht, aber es macht ein schönes Geländer
	m_WingHut.SetHeightBalustrade(2.0f);
	m_WingHut.InitPrintFlat();


	//Geländer beim eingang deaktivieren
	m_WingHut.GetWall(6, EGeoWingPart())->Fini();

	//Wings and Walls ans Placement hängen________________________________________________________________
	AddGeo(&m_WingHut);

}
