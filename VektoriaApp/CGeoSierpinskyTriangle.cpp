#include "CGeoSierpinskyTriangle.h"

CGeoSierpinskyTriangle::CGeoSierpinskyTriangle()
{
	SetAxiom("X");
	AddRule(
		"X=!+(r0.8)_f[(l0.8)<_(r0.8)X][(l0.9)(>15)X]");
	SetDefaultFactorGravitation(0.01);


    // Erzeuge das L-System:
    Create(17);
}

CGeoSierpinskyTriangle::~CGeoSierpinskyTriangle()
{
}
