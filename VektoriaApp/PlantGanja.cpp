#include "PlantGanja.h"

CPlantGanja::CPlantGanja()
{
}

CPlantGanja::~CPlantGanja()
{
}

void CPlantGanja::Init(int iRandomSeed, float fAge, float frTimeOfYear, float fRootCutHeight, float frQuality)
{
	if (m_eStatusConstruction == eStatusConstruction_Initialized)
	{
		ULWarn("Tried to initialize PlantChelidoniumMajus twice");
		return;
	}

	for (int j = 0; j < GANJA_LOD; j++)
	{
		AddPlacement(&m_aPlacementLoDs[j]);
		m_aPlacementLoDs[j].AddGeo(&m_aGeoLoDs[j]);

		float fMin = m_aGeoLoDs[j].GetOptimalLoDMin(fAge, j);
		float fMax = m_aGeoLoDs[j].GetOptimalLoDMax(fAge, j);
		fMin *= frQuality;
		fMax *= frQuality;
		m_aPlacementLoDs[j].SetLoD(
			fMin,
			fMax);
		if (j == 0)
		{
			m_aGeoLoDs[0].m_random.SRand(iRandomSeed);
			m_aGeoLoDs[0].Iterate(fAge, frTimeOfYear, -3.0f);
		}
		m_aGeoLoDs[j].Init(&m_aGeoLoDs[0], j);
	}
	m_aGeoLoDs[0].DeIterate();
	m_eStatusConstruction = eStatusConstruction_Initialized;
}

void CPlantGanja::Fini()
{
	if (m_eStatusConstruction != eStatusConstruction_Initialized)
	{
		ULWarn("PlantChelidoniumMajus already initialized");
		return;
	}

	for (int j = 0; j < GANJA_LOD; j++)
	{
		m_aPlacementLoDs[j].SubGeo(&m_aGeoLoDs[j]);
		SubPlacement(&m_aPlacementLoDs[j]);
		m_aGeoLoDs[j].Fini();
	}
	m_eStatusConstruction = eStatusConstruction_Finished;
}