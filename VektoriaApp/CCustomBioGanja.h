#pragma once
#include "Vektoria\Root.h"
#include "Util.h"
class CCustomBioGanja :
    public CPlacement
{
public:
    CCustomBioGanja();
    ~CCustomBioGanja();

    void grow();

    CGeoBio m_geoBio;
    //Blätter
    CGeoLeaf m_geoLeaf;
    CMaterial m_matLeaf;

    //Material Baum
    CMaterial m_matBio;

    CFileWavefront m_file;
    CGeoTriangleTable* m_gLeaf;
};

