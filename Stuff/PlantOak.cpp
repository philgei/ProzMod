#include "PlantOak.h"

namespace Vektoria
{
	CPlantOak::CPlantOak()
	{
	}


	CPlantOak::~CPlantOak()
	{
	}

	void CPlantOak::Init(int iRandomSeed, float fAge, float frTimeOfYear, float fRootCutHeight, float frQuality)
	{
		if (m_eStatusConstruction == eStatusConstruction_Initialized)
		{
			ULWarn("Tried to initialize PlantOak twice");
			return;
		}

		for (int j = 0; j < PLANTOAK_LODS; j++)
		{
			AddPlacement(&m_azpLoD[j]);
			m_azpLoD[j].AddGeo(&m_azgLoD[j]);

			float fMin = m_azgLoD[j].GetOptimalLoDMin(fAge, j);
			float fMax = m_azgLoD[j].GetOptimalLoDMax(fAge, j);
			fMin *= frQuality;
			fMax *= frQuality;
			m_azpLoD[j].SetLoD(
				fMin,
				fMax);
			if (j == 0)
			{
				m_azgLoD[0].m_random.SRand(iRandomSeed);
				m_azgLoD[0].Iterate(fAge, frTimeOfYear, -3.0f);
			}
			m_azgLoD[j].Init(&m_azgLoD[0], j);
		}
		m_azgLoD[0].DeIterate();
		m_eStatusConstruction = eStatusConstruction_Initialized;
	}

	void CPlantOak::Fini()
	{
		if (m_eStatusConstruction != eStatusConstruction_Initialized)
		{
			ULWarn("PlantOak already initialized");
			return;
		}

		for (int j = 0; j < PLANTOAK_LODS; j++)
		{
			m_azpLoD[j].SubGeo(&m_azgLoD[j]);
			SubPlacement(&m_azpLoD[j]);
			m_azgLoD[j].Fini();
		}
		m_eStatusConstruction = eStatusConstruction_Finished;
	}

}