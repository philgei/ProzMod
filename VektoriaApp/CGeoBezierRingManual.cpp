#include "CGeoBezierRingManual.h"

CGeoBezierRingManual::CGeoBezierRingManual()
{
	float radiusEdit = 1.0f;

	m_aav[0][0] = CHVector(1.5f, 0.0f, 2.4f, 1.0f);
	m_aav[1][0] = CHVector(1.5f, 0.84f, 2.4f, 1.0f);
	m_aav[2][0] = CHVector(0.84f, 1.5f, 2.4f, 1.0f);
	m_aav[3][0] = CHVector(0.0f, 1.5f, 2.4f, 1.0f);

	m_aav[0][1] = CHVector(1.5f, 0.0f, 1.875f, 1.0f);
	m_aav[1][1] = CHVector(1.5f, 0.84f, 1.875f, 1.0f);
	m_aav[2][1] = CHVector(0.84f, 1.5f, 1.875f, 1.0f);
	m_aav[3][1] = CHVector(0.0f, 1.5f, 1.875f, 1.0f);

	m_aav[0][2] = CHVector(1.5f, 0.0f, 1.35f, 1.0f);
	m_aav[1][2] = CHVector(1.5f, 0.84f, 1.35f, 1.0f);
	m_aav[2][2] = CHVector(0.84f, 1.5f, 1.35f, 1.0f);
	m_aav[3][2] = CHVector(0.0f, 1.5f, 1.35f, 1.0f);

	m_aav[0][3] = CHVector(1.5f, 0.0f, 0.9f, 1.0f);
	m_aav[1][3] = CHVector(1.5f, 0.84f, 0.9f, 1.0f);
	m_aav[2][3] = CHVector(0.84f, 1.5f, 0.9f, 1.0f);
	m_aav[3][3] = CHVector(0.0f, 1.5f, 0.9f, 1.0f);

	/*m_aav[0][1] = CHVector(1.75f, 0.0f, 1.875f, 1.0f);
	m_aav[1][1] = CHVector(1.75f, -0.98f, 1.875f, 1.0f);
	m_aav[2][1] = CHVector(0.98f, -1.75f, 1.875f, 1.0f);
	m_aav[3][1] = CHVector(0.0f, -1.75f, 1.875f, 1.0f);

	m_aav[0][2] = CHVector(2.0f, 0.0f, 1.35f, 1.0f);
	m_aav[1][2] = CHVector(2.0f, -1.12f, 1.35f, 1.0f);
	m_aav[2][2] = CHVector(1.12f, -2.0f, 1.35f, 1.0f);
	m_aav[3][2] = CHVector(0.0f, -2.0f, 1.35f, 1.0f);

	m_aav[0][3] = CHVector(2.0f, 0.0f, 0.9f, 1.0f);
	m_aav[1][3] = CHVector(2.0f, -1.12f, 0.9f, 1.0f);
	m_aav[2][3] = CHVector(1.12f, -2.0f, 0.9f, 1.0f);
	m_aav[3][3] = CHVector(0.0f, -2.0f, 0.9f, 1.0f);*/
	AddPatch(m_aav, 20, 20);

	/*m_aav[0][0] = CHVector(0.0f, -1.5f, 2.4f, 1.0f);
	m_aav[1][0] = CHVector(-0.84f, -1.5f, 2.4f, 1.0f);
	m_aav[2][0] = CHVector(-1.5f, -0.84f, 2.4f, 1.0f);
	m_aav[3][0] = CHVector(-1.5f, 0.0f, 2.4f, 1.0f);
	m_aav[0][1] = CHVector(0.0f, -1.75f, 1.875f, 1.0f);
	m_aav[1][1] = CHVector(-0.98f, -1.75f, 1.875f, 1.0f);
	m_aav[2][1] = CHVector(-1.75f, -0.98f, 1.875f, 1.0f);
	m_aav[3][1] = CHVector(-1.75f, 0.0f, 1.875f, 1.0f);
	m_aav[0][2] = CHVector(0.0f, -2.0f, 1.35f, 1.0f);
	m_aav[1][2] = CHVector(-1.12f, -2.0f, 1.35f, 1.0f);
	m_aav[2][2] = CHVector(-2.0f, -1.12f, 1.35f, 1.0f);
	m_aav[3][2] = CHVector(-2.0f, 0.0f, 1.35f, 1.0f);
	m_aav[0][3] = CHVector(0.0f, -2.0f, 0.9f, 1.0f);
	m_aav[1][3] = CHVector(-1.12f, -2.0f, 0.9f, 1.0f);
	m_aav[2][3] = CHVector(-2.0f, -1.12f, 0.9f, 1.0f);
	m_aav[3][3] = CHVector(-2.0f, 0.0f, 0.9f, 1.0f);
	AddPatch(m_aav, 20, 20);

	m_aav[0][0] = CHVector(-1.5f, 0.0f, 2.4f, 1.0f);
	m_aav[1][0] = CHVector(-1.5f, 0.84f, 2.4f, 1.0f);
	m_aav[2][0] = CHVector(-0.84f, 1.5f, 2.4f, 1.0f);
	m_aav[3][0] = CHVector(0.0f, 1.5f, 2.4f, 1.0f);
	m_aav[0][1] = CHVector(-1.75f, 0.0f, 1.875f, 1.0f);
	m_aav[1][1] = CHVector(-1.75f, 0.98f, 1.875f, 1.0f);
	m_aav[2][1] = CHVector(-0.98f, 1.75f, 1.875f, 1.0f);
	m_aav[3][1] = CHVector(0.0f, 1.75f, 1.875f, 1.0f);
	m_aav[0][2] = CHVector(-2.0f, 0.0f, 1.35f, 1.0f);
	m_aav[1][2] = CHVector(-2.0f, 1.12f, 1.35f, 1.0f);
	m_aav[2][2] = CHVector(-1.12f, 2.0f, 1.35f, 1.0f);
	m_aav[3][2] = CHVector(0.0f, 2.0f, 1.35f, 1.0f);
	m_aav[0][3] = CHVector(-2.0f, 0.0f, 0.9f, 1.0f);
	m_aav[1][3] = CHVector(-2.0f, 1.12f, 0.9f, 1.0f);
	m_aav[2][3] = CHVector(-1.12f, 2.0f, 0.9f, 1.0f);
	m_aav[3][3] = CHVector(0.0f, 2.0f, 0.9f, 1.0f);
	AddPatch(m_aav, 20, 20);

	m_aav[0][0] = CHVector(0.0f, 1.5f, 2.4f, 1.0f);
	m_aav[1][0] = CHVector(0.84f, 1.5f, 2.4f, 1.0f);
	m_aav[2][0] = CHVector(1.5f, 0.84f, 2.4f, 1.0f);
	m_aav[3][0] = CHVector(1.5f, 0.0f, 2.4f, 1.0f);
	m_aav[0][1] = CHVector(0.0f, 1.75f, 1.875f, 1.0f);
	m_aav[1][1] = CHVector(0.98f, 1.75f, 1.875f, 1.0f);
	m_aav[2][1] = CHVector(1.75f, 0.98f, 1.875f, 1.0f);
	m_aav[3][1] = CHVector(1.75f, 0.0f, 1.875f, 1.0f);
	m_aav[0][2] = CHVector(0.0f, 2.0f, 1.35f, 1.0f);
	m_aav[1][2] = CHVector(1.12f, 2.0f, 1.35f, 1.0f);
	m_aav[2][2] = CHVector(2.0f, 1.12f, 1.35f, 1.0f);
	m_aav[3][2] = CHVector(2.0f, 0.0f, 1.35f, 1.0f);
	m_aav[0][3] = CHVector(0.0f, 2.0f, 0.9f, 1.0f);
	m_aav[1][3] = CHVector(1.12f, 2.0f, 0.9f, 1.0f);
	m_aav[2][3] = CHVector(2.0f, 1.12f, 0.9f, 1.0f);
	m_aav[3][3] = CHVector(2.0f, 0.0f, 0.9f, 1.0f);
	AddPatch(m_aav, 20, 20);*/

	Init();

	CMaterial* pzm = new CMaterial();
	pzm->LoadPreset("MetalRustyFlaking");
	SetMaterial(pzm);


}

CGeoBezierRingManual::~CGeoBezierRingManual()
{

}
