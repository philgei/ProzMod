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

    //Hierarchitektur
    CGeoWing m_WingHut;



    //Tempel
    CPlacement m_zpTemple;
    CGeoWing m_zgWingTemple;
    CGeoWing m_zgWingMainBlock;
    CGeoWing m_zgWingBase;
    CGeoWing m_zgWingPillar;

    CGeoWindow m_zgWindowDoor;

    CGeoWall m_zgWallBaseplates[4];
    CGeoWall m_zgWallRamp;
    CGeoWing m_zgWingRamp;

    //Roof
    CGeoWall m_zgWallRoof[2]; //0=Grundvolumen; 1=A back and front;
    CGeoWindow m_zgWindowRoof;
    CGeoWing m_zgWingRoof;
    CGeoWing m_zgWingRoofTrinagle;

    CMaterial m_zmTemple;
};

