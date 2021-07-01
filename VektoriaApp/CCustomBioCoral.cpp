#include "CCustomBioCoral.h"

CCustomBioCoral::CCustomBioCoral()
{
}

CCustomBioCoral::~CCustomBioCoral()
{
}

void CCustomBioCoral::grow()
{
	//Blatt
	{
		m_gLeaf = m_file.LoadGeo("meshes\\leaf.obj", true);
		m_GeoBio.SetGeoLeaf(m_gLeaf, 0);
	}
	

	m_GeoBio.m_fAgeStopped = 3;


	m_GeoBio.m_iIterations = 3;
	m_GeoBio.m_iTurtleStartLongitude = 15;
	m_GeoBio.m_iTurtleStartLattitude = 23;


	m_GeoBio.SetDefaultAngles(HALFPI / 2, HALFPI / 2, HALFPI / 2);
	m_GeoBio.SetDefaultFactorGravitation(0.1f);
	m_GeoBio.SetDefaultFactorSide(0.01f);
	m_GeoBio.SetTurtleStartHeight(1);
	m_GeoBio.SetTurtleStartRadius(0.04);

	//m_GeoBio.SetMaterialLeaf

	m_GeoBio.SetAxiom("A");

	m_GeoBio.AddRule("A=/(l0.9)(r0.95)+f[<Z][>Z]A");
	m_GeoBio.AddRule("Z=(l0.01)(r0.3)f(l50)X");
	m_GeoBio.AddRule("X=!f(l0.5)X");

	m_GeoBio.Create(5);

	AddGeo(&m_GeoBio);
}
