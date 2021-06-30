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
    //Grundfl�che
    CGeoWing m_WingHut;
    //Dach
    CGeoWing m_WingHutRoof;

    //S�ulen an den Seiten
    CGeoWing m_aWingPillars[8];
    CGeoCylinder m_aGeoPillars[8];
    CHVectors m_RoofPrint;

    

    //Grundriss
    CHVectors m_MainPrint;
};

