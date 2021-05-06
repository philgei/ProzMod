#include "CGeoSierpinskyTriangle.h"

CGeoSierpinskyTriangle::CGeoSierpinskyTriangle()
{
    SetAxiom("x");

    //AddRule("f=f<f>f>f<f");
    AddRule("x=(L0.2)(r0.5)f[<x]f[vx](r2.0)[>x]f[<x]>fx");
    AddRule("f=<f>fvf^f");
    // Setzte die Default-Winkel auf 120°:
    /* SetDefaultAngles(TWOPI / 3.0f,
        TWOPI / 3.0f, TWOPI / 3.0f); */

        SetTurtleStartDir(CHVector(0, -1, 0, 0));

    SetRootCutHeight(-10000);

    SetDefaultAngles(UM_DEG2RAD(25),
        UM_DEG2RAD(25),
        UM_DEG2RAD(25));

    // Erzeuge das L-System:
    Create(5);
}

CGeoSierpinskyTriangle::~CGeoSierpinskyTriangle()
{
}
