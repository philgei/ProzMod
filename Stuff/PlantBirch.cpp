#include "PlantBirch.h"

namespace Vektoria
{
	CPlantBirch::CPlantBirch()
	{
	}


	CPlantBirch::~CPlantBirch()
	{
	}

	void CPlantBirch::Init(int iRandomSeed, float fAge, float frTimeOfYear, float fRootCutHeight, float frQuality)
	{
		if (m_eStatusConstruction == eStatusConstruction_Initialized)
		{
			ULWarn("Tried to initialize PlantBirch twice");
			return;
		}

		for (int j = 0; j < PLANTBIRCH_LODS; j++)
		{
			AddPlacement(&m_azpLoD[j]);
			m_azpLoD[j].AddGeo(&m_azgLoD[j]);

			float fMin = m_azgLoD[j].GetOptimalLoDMin(fAge, j);
			float fMax = m_azgLoD[j].GetOptimalLoDMax(fAge, j);
			fMin *= frQuality;
			fMax *= frQuality;
			//			ULDebug("%f, %f", fMin, fMax);
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

	void CPlantBirch::Fini()
	{
		if (m_eStatusConstruction != eStatusConstruction_Initialized)
		{
			ULWarn("PlantBirch already initialized");
			return;
		}

		for (int j = 0; j < PLANTBIRCH_LODS; j++)
		{
			m_azpLoD[j].SubGeo(&m_azgLoD[j]);
			SubPlacement(&m_azpLoD[j]);
			m_azgLoD[j].Fini();
		}
		m_eStatusConstruction = eStatusConstruction_Finished;
	}

}