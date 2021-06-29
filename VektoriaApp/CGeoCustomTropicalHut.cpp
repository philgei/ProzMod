#include "CGeoCustomTropicalHut.h"

void CGeoCustomTropicalHut::build()
{
	m_WingHut.OpenSesamy("P@ntzai74!et)");
	//m_WingPillars.OpenSesamy("P@ntzai74!et)");
	m_MatWalls.LoadPreset("WoodPlanksBankirai");

	//Grundriss erstellen

	float scaleFactor = 5;
	m_MainPrint.Add(&(CHVector(1, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(5, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(5, 0, -6) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-5, 0, -6) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-5, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-1, 0, -1) * scaleFactor));
	m_MainPrint.Add(&(CHVector(-1, 0, 3) * scaleFactor));
	m_MainPrint.Add(&(CHVector(1, 0, 3) * scaleFactor));

	//Stützen erzeugen
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

		matPillarPlacement.Translate(*m_MainPrint.m_aphvector[b]);
		matPillarPlacement.TranslateYDelta(-7.0f);
		m_WingHut.AddGeoWing(&m_aWingPillars[b], matPillarPlacement);
	}


	m_WingHut.SetMaterials(&m_MatWalls, &m_MatWalls, &m_MatWalls, &m_MatWalls, &m_MatWalls);

	m_WingHut.SetPrint(&m_MainPrint);
	m_WingHut.SetSizePrint(1, 1);
	m_WingHut.SetHeightBalustrade(2.0f);
	m_WingHut.InitPrintFlat();

	AddGeo(&m_WingHut);

}
