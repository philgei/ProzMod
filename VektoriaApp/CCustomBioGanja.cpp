#include "CCustomBioGanja.h"

CCustomBioGanja::CCustomBioGanja()
{
}

CCustomBioGanja::~CCustomBioGanja()
{
}

void CCustomBioGanja::grow()
{
	//Ich habs sehr lange versucht. Hat leider nicht geklappt :( 
	//m_matLeaf.MakeTextureDiffuse("textures\\ganjaleaf - Copy.png");
	m_matLeaf.MakeTextureDiffuse("textures\\ganjaGreen.png");
	//Desshalb halt einfarbig 

	m_matBio.LoadPreset("BarkChelidoniumMajus");
	m_geoBio.SetMaterial(&m_matBio);

	CHVector avOuter[37];
	//Stiel:
	avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
	avOuter[1] = CHVector(0.02f, 0.0f, 1.0f, 1.0f);
	avOuter[2] = CHVector(0.02f, 0.0f, 0.73f, 1.0f);
	//Blatt 1
	avOuter[3] = CHVector(0.021f, 0.0f, 0.73f, 1.0f);
	avOuter[4] = CHVector(0.15f, 0.0f, 0.78f, 1.0f);
	avOuter[5] = CHVector(0.34f, 0.0f, 0.82f, 1.0f);
	avOuter[6] = CHVector(0.59f, 0.0f, 0.88f, 1.0f);
	avOuter[7] = CHVector(0.46f, 0.0f, 0.80f, 1.0f);
	avOuter[8] = CHVector(0.31f, 0.0f, 0.76f, 1.0f);
	avOuter[9] = CHVector(0.16f, 0.0f, 0.73f, 1.0f);
	avOuter[10] = CHVector(0.021f, 0.0f, 0.72f, 1.0f);
	//Blatt 2
	avOuter[11] = CHVector(0.024f, 0.0f, 0.695f, 1.0f);
	avOuter[12] = CHVector(0.26f, 0.0f, 0.72f, 1.0f);
	avOuter[13] = CHVector(0.61f, 0.0f, 0.71f, 1.0f);
	avOuter[14] = CHVector(1.0f, 0.0f, 0.62f, 1.0f);
	avOuter[15] = CHVector(0.65f, 0.0f, 0.63f, 1.0f);
	avOuter[16] = CHVector(0.28f, 0.0f, 0.66f, 1.0f);
	avOuter[17] = CHVector(0.028f, 0.0f, 0.742f, 1.0f);
	//Blatt 3
	avOuter[18] = CHVector(0.02f, 0.0f, 0.69f, 1.0f);
	avOuter[19] = CHVector(0.379f, 0.0f, 0.590f, 1.0f);
	avOuter[20] = CHVector(0.640f, 0.0f, 0.423f, 1.0f);
	avOuter[21] = CHVector(0.961f, 0.0f, 0.063f, 1.0f);
	avOuter[22] = CHVector(0.512f, 0.0f, 0.268f, 1.0f);
	avOuter[23] = CHVector(0.240f, 0.0f, 0.434f, 1.0f);
	avOuter[24] = CHVector(0.01f, 0.0f, 0.715f, 1.0f);

	//Blatt 4
	avOuter[30] = CHVector(0.013f, 0.0f, 0.71f, 1.0f);
	avOuter[31] = CHVector(0.016f, 0.0f, 0.66f, 1.0f);
	avOuter[32] = CHVector(0.11f, 0.0f, 0.55f, 1.0f);
	avOuter[33] = CHVector(0.15f, 0.0f, 0.46f, 1.0f);
	avOuter[34] = CHVector(0.11f, 0.0f, 0.27f, 1.0f);
	avOuter[35] = CHVector(0.04f, 0.0f, 0.16f, 1.0f);
	avOuter[36] = CHVector(0.00f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 37; i++) {
		m_geoLeaf.AddOuter(&avOuter[i]);
	}
		


	m_geoLeaf.Init(&m_matLeaf, true, true);
	m_geoBio.SetGeoLeaf(&m_geoLeaf);


	//Regeln
	{

		m_geoBio.SetDefaultAngles(HALFPI / 3, HALFPI / 3, HALFPI / 3);
		m_geoBio.SetTurtleStartRadius(0.005);
		m_geoBio.SetTurtleStartHeight(0.4);
		m_geoBio.SetTurtleStartBendingLateral(5);

		m_geoBio.SetAxiom("A");

		m_geoBio.AddRule("A=fV");
		m_geoBio.AddRule("V=(l2.0)[++<fK][++++<fK][++++++<fK]+++++(l0.48)fV");
		m_geoBio.AddRule("K=(l2.0)[++<f(l0.5)h][++++<f(l0.5)h][++++++<f(l0.5)h]");
	}


	



	//m_geoBio.SetAxiom("A");


	//m_geoBio.AddRule("X=YY");
	//m_geoBio.AddRule("Y=F[<fh]f");


	//m_geoBio.AddRule("A=/(l0.9)(r0.95)+f[<Z][>Z]A");
	//m_geoBio.AddRule("Z=(l0.01)(r0.3)f(l50)X");
	//m_geoBio.AddRule("X=!fh(l0.5)X");

	m_geoBio.Create(7);

	AddGeo(&m_geoBio);
}
