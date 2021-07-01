#pragma once
#include "Vektoria\Root.h"
#include "Util.h"
class CCustomBioCoral :
    public CPlacement
{
public:
    CCustomBioCoral();
    ~CCustomBioCoral();

    void grow();

    CFileWavefront m_file;
    CGeoTriangleTable* m_gLeaf;


    CGeoBio m_GeoBio;
};

