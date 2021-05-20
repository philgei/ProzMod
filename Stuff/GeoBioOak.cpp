#include "GeoBioOak.h"
#include "root.h"


#include "RootGlobals.h"


namespace Vektoria
{

CGeoBioOak::CGeoBioOak()
{
}


CGeoBioOak::~CGeoBioOak()
{
}

// Eichen können bis zu 35 bis 40 Meter hoch werden

void CGeoBioOak::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
{
	m_zmBark.LoadPreset("BarkOak");
 	m_zmBark.SetDisplacementOn();
	m_zmBark.SetDisplacementStrength(0.05f);

	SetMaterial(&m_zmBark);

	m_fAge = fAge;
	m_frTimeOfYear = frTimeOfYear;
	m_fRootCutHeight = fRootCutHeight;

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;

	if (frTimeShifted > 0.1f && frTimeShifted < 0.9f) // Außerhalb Februar bis November
		m_bHasLeaves = true;
	m_fAgeStopped = m_fAge;
	if (m_fAgeStopped > 500.0f)
		m_fAgeStopped = 500.f;
	if (m_fAgeStopped < 2.1f)
		m_fAgeStopped = 2.1f;
	float fyRootOffset = 0.0f;
	if (m_fAgeStopped > 100.0f)
	{
		m_iIterations = 15;
		fyRootOffset = 1.0f;
	}
	else if (m_fAgeStopped > 50.0f)
	{
		m_iIterations = 14;
		fyRootOffset = 0.8f;
	}
	else if (m_fAgeStopped > 20.0f)
	{
		m_iIterations = 13;
		fyRootOffset = 0.6f;
	}
	else if (m_fAgeStopped > 10.0f)
	{
		m_iIterations = 12;
		fyRootOffset = 0.5f;
	}
	else if (m_fAgeStopped > 5.0f)
	{
		m_iIterations = 11;
		fyRootOffset = 0.5f;
	}
	else if (m_fAgeStopped > 2.0f)
	{
		m_iIterations = 9;
		fyRootOffset = 0.01f;
	}
	else if (m_fAgeStopped > 1.0f)
	{
		m_iIterations = 8;
		fyRootOffset = 0.001f;
	}
	else
	{
		m_iIterations = 8;
		fyRootOffset = 0.001f;
	}


	//------------------------
	// Erzeuge Stamm und Geäst:
	//------------------------

	if (m_bHasLeaves)
	{
		SetAxiom("Z");
		AddRule("25:Z=(>10)f(<10)(l0.8)K");
		AddRule("25:Z=(^15)f(v13)(l0.8)K");
		AddRule("25:Z=(>5)f(<4)(l0.8)K");
		AddRule("25:Z=(v2)f(^2)(l0.8)K");

		AddRule("30:K=_[(+0)(r0.80)(>80)X][(+123)(r0.75)(>52)X][(+239)(r0.72)(>48)X]°(r0.80)f[X]"); 
		AddRule("30:K=_[(+0)(r0.75)(>70)X][(+120)(r0.75)(>62)X][(+219)(r0.72)(>68)X]°(r0.80)(>8)f[X]"); 
		AddRule("40:K=_[(+0)(r0.75)(>60)X][(+140)(r0.85)(>42)X][(+219)(r0.72)(>58)X]°(r0.85)(v10)f[X]"); 

		AddRule("5:X=°+(r0.80)__f[(l0.90)(>5)X]{b=-1,(l0.7)(r0.8)f[^(l1.7)h]f(l1.7)h}");
		AddRule("45:X=°+(r0.80)__f[(l0.79)<_(r0.80)X][(l0.87)(>15)X]{b=-1,(l0.7)(r0.8)f[^(l1.7)h]f(l1.7)h}");
		AddRule("25:X=°+(r0.80)__f[(l0.79)<_(r0.80)X][(l0.86)(>9)X]{b=-1,(l0.75)(r0.8)f[^(l1.7)h]f(l1.7)h}");
		AddRule("25:X=°+(r0.80)__f[(l0.79)(<35)_(r0.80)X][(l0.85)(>25)X]{b=-1,(l0.6)(r0.8)f[^(l1.7)h]f(l1.7)h}");
		
	}
	else
	{
		SetAxiom("Z");
		AddRule("25:Z=(>10)f(<10)(l0.8)K");
		AddRule("25:Z=(^15)f(v13)(l0.8)K");
		AddRule("25:Z=(>5)f(<4)(l0.8)K");
		AddRule("25:Z=(v2)f(^2)(l0.8)K");
		AddRule("30:K=_[(+0)(r0.80)(>80)X][(+123)(r0.75)(>52)X][(+239)(r0.72)(>48)X]°(r0.80)f[X]"); // +(r0.80)(+60)f[(l0.79)(>70)X][(l0.90)(+120)(>)X][(l0.90)(+240)(>45)X]
		AddRule("30:K=_[(+0)(r0.75)(>70)X][(+120)(r0.75)(>62)X][(+219)(r0.72)(>68)X]°(r0.80)(>8)f[X]"); // +(r0.80)(+60)f[(l0.79)(>70)X][(l0.90)(+120)(>)X][(l0.90)(+240)(>45)X]
		AddRule("40:K=_[(+0)(r0.75)(>60)X][(+140)(r0.85)(>42)X][(+219)(r0.72)(>58)X]°(r0.85)(v10)f[X]"); // +(r0.80)(+60)f[(l0.79)(>70)X][(l0.90)(+120)(>)X][(l0.90)(+240)(>45)X]
		AddRule("5:X=°+(r0.80)__f[(l0.90)(>5)X]");
		AddRule("45:X=°+(r0.80)__f[(l0.79)<_(r0.80)X][(l0.87)(>15)X]");
		AddRule("25:X=°+(r0.80)__f[(l0.79)<_(r0.80)X][(l0.86)(>9)X]");
		AddRule("25:X=°+(r0.80)__f[(l0.79)(<35)_(r0.80)X][(l0.85)(>25)X]");
	}
	CGeoLSystem::Iterate(m_iIterations, m_acAxiom);

	// ---------------
	// Erzeuge Wurzel:
	// ---------------

	if (fRootCutHeight < 0.0f)
	{
		m_pzgRoot = new CGeoLSystem();
		m_pzgRoot->SetMaterial(m_pmaterial);
		m_pzgRoot->m_random.m_uRand = m_random.m_uRand;

		
		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, fyRootOffset, 0.0f, 1.0f));

		m_pzgRoot->SetAxiom("R");
		m_pzgRoot->AddRule("R=(l0.001)(r0.1)f(l1000)(r10)Z");
		
		m_pzgRoot->AddRule("50:Z=(l0.8)[(>57)fX][(v40)fX][(<42)fX][(-10)(^62)fX][(+20)(^48)fX]°(r1.10)f[X]");
		m_pzgRoot->AddRule("50:Z=(l0.8)[(>42)fX][(v58)fX][(-5)(<52)fX][(-15)(^50)fX][(+14)(^68)fX]°(r1.10)f[X]");
		


		m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(r0.80)(>10)X]");
		m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.89)<(r0.80)X][(l0.87)(r0.80)(>15)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.92)(<45)(r0.80)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.89)(<35)(r0.80)X][(l0.95)(r0.80)(>25)X]");

		
		/*
		m_pzgRoot->SetAxiom("R");
		m_pzgRoot->AddRule("R=(l0.001)(r0.1)f(l1000)(r10)Z");
		m_pzgRoot->AddRule("50:Z=(l0.8)[(+0)(>90)X][(+123)(>92)X][(+239)(>88)X]°(r0.80)f[X]");
		m_pzgRoot->AddRule("50:Z=(l0.8)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X]°(r0.80)(>9)f[X]");
		m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(>10)X]");
		m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.79)<(r0.80)X][(l0.87)(>15)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<45)(r0.80)X][(l0.86)(>9)X]");
		m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<35)(r0.80)X][(l0.85)(>25)X]");
		*/
		m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);
	}


}

void CGeoBioOak::DeIterate()
{
	((CGeoLSystem*)this)->DeIterate();
	if (m_pzgRoot)
		m_pzgRoot->DeIterate();
}


void CGeoBioOak::Init(CGeoBioOak * pzgTemplate, unsigned int uLoD)
{
	if(!pzgTemplate)
	{
		return;
	}
	CopyThis(*pzgTemplate);
	SetMaterial(pzgTemplate->m_pmaterial);

	if(pzgTemplate->m_iToKill<=0)
	{
		return;
	}

	char * acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

	if (!acTurtleOrdersMain)
	{
		return;
	}

	float frTimeShifted = m_frTimeOfYear + 0.25f;
	if (frTimeShifted > 1.0f)
		frTimeShifted -= 1.0f;


	if (m_bHasLeaves)
	{
		// ----------------------
		// Erzeuge Blattmaterial: 
		// ----------------------

	//	m_zmLeaf.LoadPreset("LeafBlossom");

		m_zmLeaf.LoadPreset("LeafOak");
		// m_zmLeaf.SetChromaKeyingOn();
		/*

		// Nicht Löschen!
		m_zmLeaf.MakeTextureDiffuse(".\\..\\..\\Lib\\Materials\\LeafOak\\LeafOakD.jpg");
		m_zmLeaf.MakeTextureSpecular(".\\..\\..\\Lib\\Materials\\LeafOak\\LeafOakS.jpg");
		m_zmLeaf.MakeTextureBump(".\\..\\..\\Lib\\Materials\\LeafOak\\LeafOakB.jpg");
		m_zmLeaf.MakeTextureThickness(".\\..\\..\\Lib\\Materials\\LeafOak\\LeafOakT.jpg",CColor(0.3,1.0,0.3));
		m_zmLeaf.SetSpecularSharpness(100.0f);
		m_zmLeaf.SetLightScatteringOn();
		m_zmLeaf.SavePreset("LeafOak");
		*/
		//	m_zmLeaf.Log();
		SetMaterialLeaf(&m_zmLeaf);

		float faLeafColoring = 0.0f; 
		float frColorScaling = 1.0f;
		if (frTimeShifted >= 0.7f) // Ab Anfang September
		{
			faLeafColoring = (frTimeShifted - 0.7f) / -0.2f*THIRDPI;
			m_zmLeaf.RotateHue(faLeafColoring);
			if (frTimeShifted >= 0.8f)
			{
				frColorScaling = 1.0f - (frTimeShifted - 0.8f) / 0.3f;
				m_zmLeaf.ScaleDelta(frColorScaling);
			}
		}

		// --------------
		// Erzeuge Blatt: 
		// --------------

		m_zgLeafMain.SetMiddle(CHVector(0.0f, 0.03f, 0.607f, 1.0f));

		SetMinLeafBending(-QUARTERPI);
		SetMaxLeafBending(HALFPI*1.2f);
		SetMinLeafFolding(-HALFPI*0.5f);
		SetMaxLeafFolding(HALFPI);

		if (uLoD == 0)
		{
			/*
			CHVector avOuter[34];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.5f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.5f, 0.0f, 0.5f, 1.0f);
			avOuter[3] = CHVector(0.5f, 0.0f, 0.0f, 1.0f);
			avOuter[4] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

			for (int i = 0; i < 5; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);
				*/
			CHVector avOuter[34];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.97f, 1.0f);

			//1.Ausbuchtung:
			avOuter[3] = CHVector(0.04f, 0.0f, 0.97f, 1.0f);
			avOuter[4] = CHVector(0.17f, 0.0f, 0.83f, 1.0f);
			avOuter[5] = CHVector(0.18f, 0.0f, 0.810f, 1.0f);
			avOuter[6] = CHVector(0.14f, 0.0f, 0.79f, 1.0f);

			//2.Ausbuchtung:
			avOuter[7] = CHVector(0.14f, 0.0f, 0.76f, 1.0f);
			avOuter[8] = CHVector(0.28f, 0.0f, 0.69f, 1.0f);
			avOuter[9] = CHVector(0.32f, 0.0f, 0.65f, 1.0f);
			avOuter[10] = CHVector(0.30f, 0.0f, 0.62f, 1.0f);
			avOuter[11] = CHVector(0.25f, 0.0f, 0.60f, 1.0f);
			avOuter[12] = CHVector(0.17f, 0.0f, 0.60f, 1.0f);

			//3.Ausbuchtung:
			avOuter[13] = CHVector(0.16f, 0.0f, 0.59f, 1.0f);
			avOuter[14] = CHVector(0.40f, 0.0f, 0.45f, 1.0f);
			avOuter[15] = CHVector(0.43f, 0.0f, 0.40f, 1.0f);
			avOuter[16] = CHVector(0.43f, 0.0f, 0.35f, 1.0f);
			avOuter[17] = CHVector(0.40f, 0.0f, 0.33f, 1.0f);
			avOuter[18] = CHVector(0.28f, 0.0f, 0.34f, 1.0f);

			//4.Ausbuchtung:
			avOuter[19] = CHVector(0.26f, 0.0f, 0.33f, 1.0f);
			avOuter[20] = CHVector(0.26f, 0.0f, 0.30f, 1.0f);
			avOuter[21] = CHVector(0.27f, 0.0f, 0.28f, 1.0f);
			avOuter[22] = CHVector(0.29f, 0.0f, 0.24f, 1.0f);
			avOuter[23] = CHVector(0.29f, 0.0f, 0.20f, 1.0f);
			avOuter[24] = CHVector(0.27f, 0.0f, 0.18f, 1.0f);

			//5.Ausbuchtung:
			avOuter[25] = CHVector(0.15f, 0.0f, 0.17f, 1.0f);
			avOuter[26] = CHVector(0.15f, 0.0f, 0.16f, 1.0f);
			avOuter[27] = CHVector(0.16f, 0.0f, 0.10f, 1.0f);
			avOuter[28] = CHVector(0.16f, 0.0f, 0.08f, 1.0f);
			avOuter[29] = CHVector(0.13f, 0.0f, 0.06f, 1.0f);

			//6.Ausbuchtung:
			avOuter[30] = CHVector(0.10f, 0.0f, 0.06f, 1.0f);
			avOuter[31] = CHVector(0.07f, 0.0f, 0.06f, 1.0f);
			avOuter[32] = CHVector(0.02f, 0.0f, 0.00f, 1.0f);
			avOuter[33] = CHVector(0.0f, 0.0f, 0.00f, 1.0f);

			for (int i = 0; i < 34; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.05f);
			SetGeoLeaf(&m_zgLeafMain);
		}
		else if (uLoD == 1)
		{
			CHVector avOuter[20];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.015f, 0.0f, 0.97f, 1.0f);

			//1.Ausbuchtung:
			avOuter[2] = CHVector(0.04f, 0.0f, 0.97f, 1.0f);
			avOuter[3] = CHVector(0.18f, 0.0f, 0.810f, 1.0f);

			//2.Ausbuchtung:
			avOuter[4] = CHVector(0.14f, 0.0f, 0.76f, 1.0f);
			avOuter[5] = CHVector(0.32f, 0.0f, 0.65f, 1.0f);
			avOuter[6] = CHVector(0.25f, 0.0f, 0.60f, 1.0f);

			//3.Ausbuchtung:
			avOuter[7] = CHVector(0.16f, 0.0f, 0.59f, 1.0f);
			avOuter[8] = CHVector(0.43f, 0.0f, 0.40f, 1.0f);
			avOuter[9] = CHVector(0.40f, 0.0f, 0.33f, 1.0f);

			//4.Ausbuchtung:
			avOuter[10] = CHVector(0.26f, 0.0f, 0.33f, 1.0f);
			avOuter[11] = CHVector(0.27f, 0.0f, 0.28f, 1.0f);
			avOuter[12] = CHVector(0.29f, 0.0f, 0.20f, 1.0f);

			//5.Ausbuchtung:
			avOuter[13] = CHVector(0.15f, 0.0f, 0.17f, 1.0f);
			avOuter[14] = CHVector(0.16f, 0.0f, 0.10f, 1.0f);
			avOuter[15] = CHVector(0.13f, 0.0f, 0.06f, 1.0f);

			//6.Ausbuchtung:
			avOuter[16] = CHVector(0.10f, 0.0f, 0.06f, 1.0f);
			avOuter[17] = CHVector(0.07f, 0.0f, 0.06f, 1.0f);
			avOuter[18] = CHVector(0.02f, 0.0f, 0.00f, 1.0f);
			avOuter[19] = CHVector(0.0f, 0.0f, 0.00f, 1.0f);

			for (int i = 0; i < 20; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.2f);
			SetGeoLeaf(&m_zgLeafMain);


		}
		else if (uLoD == 2)
		{
			CHVector avOuter[8];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);

			//1.Ausbuchtung:
			avOuter[1] = CHVector(0.04f, 0.0f, 0.97f, 1.0f);

			//2.Ausbuchtung:
			avOuter[2] = CHVector(0.32f, 0.0f, 0.65f, 1.0f);

			//3.Ausbuchtung:
			avOuter[3] = CHVector(0.43f, 0.0f, 0.40f, 1.0f);

			//4.Ausbuchtung:
			avOuter[4] = CHVector(0.27f, 0.0f, 0.28f, 1.0f);

			//5.Ausbuchtung:
			avOuter[5] = CHVector(0.16f, 0.0f, 0.10f, 1.0f);

			//6.Ausbuchtung:
			avOuter[6] = CHVector(0.07f, 0.0f, 0.06f, 1.0f);
			avOuter[7] = CHVector(0.0f, 0.0f, 0.00f, 1.0f);

			for (int i = 0; i < 8; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.2f);
			SetGeoLeaf(&m_zgLeafMain);


		}
		else
		{
			CHVector avOuter[3];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);

			avOuter[1] = CHVector(1.0f, 0.0f, 0.40f, 1.0f);

			avOuter[2] = CHVector(0.0f, 0.0f, 0.00f, 1.0f);

			for (int i = 0; i < 3; i++)
				m_zgLeafMain.AddOuter(&avOuter[i]);
			m_zgLeafMain.Init(&m_zmLeaf, true, true, 0.0f, 0.0f, 0.2f);
			CHMat mLoD;
			if (uLoD == 4)
			{
				mLoD.Scale(3);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(20);

			}
			else if (uLoD == 5)
			{
				mLoD.Scale(7.5f);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(200);
			}
			else if (uLoD >= 6)
			{
				mLoD.Scale(20);
				m_zgLeafMain.Transform(mLoD);
				SetLeafSkipFactor(2000);
			}
			SetGeoLeaf(&m_zgLeafMain);


		}


		float fLeafScaling = 0.0f;
		if (frTimeShifted >= 0.1f && frTimeShifted <= 0.9f) // Von Februar bis November
			fLeafScaling = 1.6f*(frTimeShifted - 0.1f) / 0.8f;
		if (fLeafScaling > 1.0f)
			fLeafScaling = 1.0f;

		CHMat mScale;
		mScale.Scale(fLeafScaling);
		m_zgLeafMain.Transform(mScale);
	}

	float fStartHeight = 0.0f;
	float fStartRadius = 0.0f;
	float fSwakeRandom = 0.0f;
	float fLongitude = 16;
	float fLattitude = 26;
	if (m_fAgeStopped > 100.0f)
	{
		fLongitude = 32;
		fLattitude = 32;
		fStartHeight = 4.5f + (m_fAgeStopped-100.0f)/400.0f*1.0f;
		fStartRadius = 1.5f + (m_fAgeStopped - 100.0f) / 400.0f*1.0f;
		fSwakeRandom = 0.00f;
	}
	else if (m_fAgeStopped > 50.0f)
	{
		fLongitude = 26;
		fLattitude = 26;
		fStartHeight = 2.5f + (m_fAgeStopped - 50.0f) / 50.0f*2.0f;
		fStartRadius = 0.5f + (m_fAgeStopped - 50.0f) / 50.0f*1.0f;
		fSwakeRandom = 0.00f;
	}
	else if (m_fAgeStopped > 20.0f)
	{
		fLongitude = 22;
		fLattitude = 22;
		fStartHeight = 2.0f + (m_fAgeStopped - 20.0f) / 30.0f*0.5f;
		fStartRadius = 0.2f + (m_fAgeStopped - 20.0f) / 30.0f*0.3f;
		fSwakeRandom = 0.00f;
	}
	else if (m_fAgeStopped > 10.0f)
	{
		fLongitude = 18;
		fLattitude = 18;
		fStartHeight = 1.0f + (m_fAgeStopped - 10.0f) / 10.0f*1.0f;
		fStartRadius = 0.1f + (m_fAgeStopped - 10.0f) / 10.0f*0.1f;
		fSwakeRandom = 0.0f;
	}
	else if (m_fAgeStopped > 5.0f)
	{
		fLongitude = 12;
		fLattitude = 10;
		fStartHeight = 0.8f + (m_fAgeStopped - 5.0f) / 5.0f*0.2f;
		fStartRadius = 0.05f + (m_fAgeStopped - 5.0f) / 5.0f*0.05f;
		fSwakeRandom = 0.00f;
	}
	else if (m_fAgeStopped > 2.0f)
	{
		fLongitude = 12;
		fLattitude = 10;
		fStartHeight = 0.5f + (m_fAgeStopped - 2.0f) / 3.0f*0.3f;
		fStartRadius = 0.02f + (m_fAgeStopped - 2.0f) / 3.0f*0.03f;
		fSwakeRandom = 0.00f;
	}
	else if (m_fAgeStopped > 1.0f)
	{
		fLongitude = 12;
		fLattitude = 6;
		fStartHeight = 0.3f + (m_fAgeStopped - 1.0f) / 1.0f*0.2f;
		fStartRadius = 0.01f + (m_fAgeStopped - 1.0f) / 1.0f*0.01f;
		fSwakeRandom = 0.000f;
	}
	else
	{
		fLongitude = 12;
		fLattitude = 5;
		fStartHeight = m_fAgeStopped * 0.3f;
		fStartRadius = m_fAgeStopped * 0.01f;
		fSwakeRandom = 0.0000f;
	}

	SetDefaultAngles(PHI / 2.0f, PHI / 2.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
	SetDefaultFactorGravitation(0.1f);


	// SetSwakeRandomFactor(fSwakeRandom);
	SetTurtleStartHeight(fStartHeight);
	SetTurtleStartRadius(fStartRadius);
	if (uLoD == 0)
	{
		SetTurtleEndLongitude(6.0f);
		SetTurtleEndLattitude(4.0f);
	}
	else if (uLoD == 1)
	{
		fLongitude /= 2.0f;
		fLattitude /= 2.0f;
		SetTurtleEndLongitude(5.0f);
		SetTurtleEndLattitude(3.0f);
	}
	else if (uLoD == 2)
	{
		fLongitude /= 3.0f;
		fLattitude /= 5.0f;
//		if (fLongitude < 4)
//			fLongitude = 4;
		SetTurtleEndLongitude(4.0f);
		SetTurtleEndLattitude(2.0f);
	}
	else if (uLoD == 3)
	{
		fLongitude /= 4.0f;
		fLattitude /= 6.0f;
		SetTurtleEndLongitude(0.0f);
		SetTurtleEndLattitude(0.0f);
	}
	else // if (uLoD >= 4)
	{
		fLongitude /= 8.0f;
		fLattitude /= 10.0f;
		SetTurtleEndLongitude(0.0f);
		SetTurtleEndLattitude(0.0f);
	}

	SetTurtleStartLongitude(fLongitude);
	SetTurtleStartLattitude(fLattitude);

	Interprete(acTurtleOrdersMain);

	// ---------------
	// Erzeuge Wurzel:
	// ---------------


	if (pzgTemplate->m_pzgRoot && uLoD < 2)
	{
		if (!m_pzgRoot)
			m_pzgRoot = new CGeoLSystem();

		m_pzgRoot->SetMaterial(pzgTemplate->m_pzgRoot->m_pmaterial);
		char * acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
		m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

		m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
		m_pzgRoot->SetDefaultFactorGravitation(0.1f);

//		m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentlänge (Default: 1.0)
		m_pzgRoot->SetTurtleStartDir(CHVector(0.0f, -1.0f, 0.0f, 0.0f));
		//		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, 2.5f, 0.0f, 1.0f));

		m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
		m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
		// m_pzgRoot->SetSwakeRandomFactor(fSwakeRandom);
		m_pzgRoot->SetTurtleStartHeight(fStartHeight);
		m_pzgRoot->SetTurtleStartRadius(fStartRadius);
		m_pzgRoot->SetTurtleStartLongitude(fLongitude);
		m_pzgRoot->SetTurtleStartLattitude(fLattitude);
		m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
		m_pzgRoot->SetDefaultFactorGravitation(0.1f);

		m_pzgRoot->Interprete(acTurtleOrdersRoot);

		AddGeo(m_pzgRoot);
	}

}

float CGeoBioOak::GetOptimalLoDMin(float fAge, unsigned int uLoD)
{
	if (uLoD == 0)
		return 0.0f;
	return (50.f + m_fAgeStopped * 0.5f) * (1.0f+powf(4.0f, uLoD-1));
}

float  CGeoBioOak::GetOptimalLoDMax(float fAge, unsigned int uLoD)
{
	return (50.f + m_fAgeStopped*0.5f) * (1.0f+powf(4.0f, uLoD));
}


}
