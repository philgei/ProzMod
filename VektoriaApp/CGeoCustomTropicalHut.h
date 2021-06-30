#pragma once
#include "Vektoria\Root.h"
#include "Util.h"

class CGeoCustomTropicalHut :
    public CPlacement
{
public:
    void build();

    //Materials
    CMaterial m_MatWalls;
    CMaterial m_MatRoof;
    CMaterial m_MatRoofFacades;

    //Hierarchitektur
    //Grundfläche
    CGeoWing m_WingHut;
    //Dach
    CGeoWing m_WingHutRoof;

    //Säulen an den Seiten
    CGeoWing m_aWingPillars[8];
    CGeoCylinder m_aGeoPillars[8];
    CHVectors m_RoofPrint;

    

    //Grundriss
    CHVectors m_MainPrint;
};

