#pragma once
#include "D:\Projects\Vektoria\Lib\Vektoria\Placement.h"

#include "Vektoria\Root.h"
#include "Util.h"

class CTropicalIsland :
    public CPlacement
{
public:
    CTropicalIsland();
    ~CTropicalIsland();
    void init();

    CGeoTerrain m_TerrainWater;

    CGeoTerrain m_TerrainOri; // Gesamtes Terrain
    CGeoTerrain m_TerrainStrand;
    CGeoTerrain m_TerrainGras;
    CGeoTerrain m_TerrainSteine;

    CCut m_cutUnderSea; // Schnitt unter N.N.
    CCut m_cutStrand; //Grass
    CCut m_cutGrasslands; //Grass
    CCut m_cutRocks; //Grass

    CMaterial m_materialWater; // Wellenmaterial
    CMaterial m_materialSand; // Erdmaterial
    CMaterial m_materialGras; // Erdmaterial
    CMaterial m_materialSteine; // Erdmaterial

    CGeos m_gCol, m_gHeight; // Kollisionscontainer
    CGeoTerrains m_gsTerrain; // Terrainkollisionscontainer
};

