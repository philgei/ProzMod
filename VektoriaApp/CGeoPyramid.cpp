#include "CGeoPyramid.h"

CGeoPyramid::CGeoPyramid() {
	CHVector VL = CHVector(-0.5f, 0.0f, 0.5f, 1.0f);
	CHVector VR = CHVector(0.5f, 0.0f, 0.5f, 1.0f);
	CHVector HL = CHVector(-0.5f, 0.0f, -0.5f, 1.0f);
	CHVector HR = CHVector(0.5f, 0.0f, -0.5f, 1.0f);
	CHVector O = CHVector(0.0f, 1.0f, 0.0f, 1.0f);

	VertexAdd(VL);
	VertexAdd(VR);
	VertexAdd(O);

	VertexAdd(VR);
	VertexAdd(HR);
	VertexAdd(O);

	VertexAdd(HR);
	VertexAdd(HL);
	VertexAdd(O);

	VertexAdd(HL);
	VertexAdd(VL);
	VertexAdd(O);

	VertexAdd(HL);
	VertexAdd(HR);
	VertexAdd(VL);

	VertexAdd(HR);
	VertexAdd(VR);
	VertexAdd(VL);


	Init();
}

void CGeoPyramid::VertexAdd(CHVector pos)
{
	m_avertexPyramid[index].Init(pos, pos.Normal(), vTangent, 0.0f, 0.0f);
	AddVertex(&m_avertexPyramid[index]);
	index++;
}
