#pragma once
#include "Vektoria\Root.h"
#include "CGeoGanjaPlant.h"

#define GANJA_LOD 1

using namespace Vektoria;

class CPlantGanja : public CPlacement
{
public:
	CPlantGanja();
	~CPlantGanja();

	void Init(int iRandomSeed, float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0, float frQuality = 0.5f);


	void Fini();


	///<summary> Array mit den LoD-Unterplacements </summary> 
	CPlacement m_aPlacementLoDs[GANJA_LOD];//Number of LoDs

	///<summary> Array mit den LoD-Untergeometrien </summary> 
	CGeoGanjaPlant m_aGeoLoDs[GANJA_LOD];

protected:

	///<summary> Erzeugungsstatus </summary> 
	EStatusConstruction m_eStatusConstruction = eStatusConstruction_Start;
};

