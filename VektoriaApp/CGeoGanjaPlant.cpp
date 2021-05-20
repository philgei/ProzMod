#include "CGeoGanjaPlant.h"

	CGeoGanjaPlant::CGeoGanjaPlant()
	{
	}


	CGeoGanjaPlant::~CGeoGanjaPlant()
	{
	}

	void CGeoGanjaPlant::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
	{
		m_fAge = fAge;
		m_frTimeOfYear = frTimeOfYear;
		m_fRootCutHeight = fRootCutHeight;

		float frTimeShifted = m_frTimeOfYear + 0.25f;
		if (frTimeShifted > 1.0f)
			frTimeShifted -= 1.0f;

		m_fAgeStopped = fAge;

		// Das Schöllkraut wird ca. 3 Jahre alt:
		if (m_fAgeStopped > 3.0f)
			m_fAgeStopped = 3.0f;
		if (m_fAgeStopped < 0.01f)
			m_fAgeStopped = 0.01f;

		// Das Schöllkraut kann bis zu 60 cm groß werden
		// Stängel hat ca. 6cm -10cm Höhe bis zur ersten Verzweigung, wenn erwachsen:
		// Stängel hat ca. 2mm - 3mm Radius an der Basis, wenn erwachsen:
		if (m_fAgeStopped > 0.1f)
		{
			m_iIterations = 19;
			m_iTurtleStartLongitude = 20;
			m_iTurtleStartLattitude = 28;

			//m_fTurtleStartLength = 1.6f;
			//m_fTurtleStartRadius = 0.2f;
			m_fTurtleStartLength = 0.6f + (m_fAgeStopped - 0.01f) * 0.01f;
			m_fTurtleStartRadius = 0.02f + (m_fAgeStopped - 0.1f) * 0.00033f;
		}
		else
		{
			m_iIterations = 18;
			m_iTurtleStartLongitude = 15;
			m_iTurtleStartLattitude = 23;
			m_fTurtleStartLength = 0.06f * (m_fAgeStopped * 10.0f);
			m_fTurtleStartRadius = 0.002f * (m_fAgeStopped * 10.0f);
		}

		SetDefaultAngles(HALFPI, HALFPI, HALFPI);
		SetDefaultFactorGravitation(0.5f);
		SetTurtleStartHeight(m_fTurtleStartLength);
		SetTurtleStartRadius(m_fTurtleStartRadius);
		//------------------------
		// Erzeuge Stamm und Geäst:
		//------------------------

		// A: Anfang
		// X: Stängel 
		// Z: Zweig mit Blättern
		// B: Blütenverzweigung
		// Y: Blüte

		// Soll Blüten (Y) ausbilden, wenn Stägelradius unter einem mm:

		SetAxiom("A");

		//	AddRule("A=f(<70)fZ");

			// AddRule("20:A=[(<20)f][(>23)f][(^53)f]");
			/*
			AddRule("20:A=(l0.1)(^12)f(l10)f°(v10)X");
			AddRule("20:A=(l0.1)(^10)f(l10)f[°(<30)fX][°(>23)fX][°°(^53)fX]");
			AddRule("30:A=(l0.1)(v12)f(l10)f[°(<23)fX](+10)[°(<30)fX][°(>23)fX][°(>53)fX][°(v7)fX]");
			AddRule("30:A=(l0.1)(^15)f(l10)f[°(<20)fX][°(>23)fX][°°(v53)fX](+5)[°°(^63)fX][°(<12)fX]");
			*/

		AddRule("50:A=(l0.1)f(l10)f[°(<90)f(>80)X][°(>90)f(<80)fX][°(^90)f(v80)fX]");
		//AddRule("50:A=(l0.1)f(l10)f[°(<90)f(>80)X][°(>90)f(<80)fX][°(^90)f(v80)fX][°(v20)f(^4)fX]");

		AddRule("20:X={r>0.01,°(^14)[(^70)(r0.5)Z]+(r0.8)(l0.9)fX}{r<0.010,fB}");
		AddRule("20:X={r>0.01,°(<5)[(^72)(r0.6)Z]+(r0.9)(l0.85)fX}{r<0.010,fB}");
		AddRule("30:X={r>0.01,°(v12)[(^73)(r0.7)Z]+[(^30)(r0.8)(l0.9)fX][(v40)°(l0.9)fX]}{r<0.010,fB}");
		AddRule("30:X={r>0.01,°(>22)[(^87)(r0.5)Z]+(r0.9)(l0.9)fX}{r<0.010,B}");

		AddRule("50:B=°(l0.8)(r0.7)[(^60)fY][(v72)fY][(>72)fY][(<72)fY][(<5)fY]");
		AddRule("50:B=°(l0.85)(r0.8)[(^60)fY](+120)[(^62)fY](+120)[(^42)fY]");


		// Der Zweig:
		AddRule("50:Z=&f(l0.8)[(<70)(r80)(l2)&2l][(>70)(r80)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r100)(l2.5)1l");
		AddRule("50:Z=&f(l0.8)[(<70)(r80)(l2)&2l][(>70)(r80)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r100)(l2.5)1l");

		// Die Blüte:
		AddRule("Y=(r10.0)(l0.5)[<b][^b][>b][vb](l0.6)[(<20.2)c][(^18.4)c][(>20.4)c][(v22.4)c](+40.0)[(<10.2)c][(^11.4)c][(>14.4)c][(v12.4)c]");

		CGeoLSystem::Iterate(m_iIterations, m_acAxiom);


		// ---------------
		// Erzeuge Wurzel:
		// ---------------


		/*
		if (fRootCutHeight < 0.0f)
		{

			m_pzgRoot = new CGeoLSystem();
			m_pzgRoot->m_random.m_uRand = m_random.m_uRand;

			m_pzgRoot->SetAxiom("'Z");
			m_pzgRoot->AddRule("50:Z=(l0.8)[(+0)(>90)X][(+123)(>92)X][(+239)(>88)X]°(r0.80)f[X]");
			m_pzgRoot->AddRule("50:Z=(l0.8)[(+10)(>85)X][(+113)(>82)X][(+219)(>98)X]°(r0.80)(>9)f[X]");
			m_pzgRoot->AddRule("5:X=#+(r0.80)_f[(l0.90)(>10)X]");
			m_pzgRoot->AddRule("45:X=#+(r0.80)_f[(l0.79)<(r0.80)X][(l0.87)(>15)X]");
			m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<45)(r0.80)X][(l0.86)(>9)X]");
			m_pzgRoot->AddRule("25:X=#+(r0.80)_f[(l0.79)(<35)(r0.80)X][(l0.85)(>25)X]");


			m_pzgRoot->Iterate(m_iIterations, m_pzgRoot->m_acAxiom);

		}
		*/
		m_zmBlossom.LoadPreset("LeafBlossom");

	}

	void CGeoGanjaPlant::DeIterate()
	{
		((CGeoLSystem*)this)->DeIterate();
		if (m_pzgRoot)
			m_pzgRoot->DeIterate();
	}


	void CGeoGanjaPlant::Init(CGeoGanjaPlant* pzgTemplate, unsigned int uLoD)
	{
		if (!pzgTemplate)
		{
			return;
		}
		CopyThis(*pzgTemplate);

		if (pzgTemplate->m_iToKill <= 0)
		{
			return;
		}

		char* acTurtleOrdersMain = pzgTemplate->m_pacToKill[pzgTemplate->m_iToKill - 1];

		if (!acTurtleOrdersMain)
		{
			return;
		}

		float frTimeShifted = m_frTimeOfYear + 0.25f;
		if (frTimeShifted > 1.0f)
			frTimeShifted -= 1.0f;
		// 0= 22.Dez. 0.5=22.Juni 0.75 = 22 Sep.

		// ---------------------
		// Erzeuge Mittel-Blatt: 
		// ---------------------

		m_zmLeafMid.LoadPreset("LeafChelidoniumMajusMid");
		{
			CHVector avOuter[210];

			int iK = 0;

			//S:
			avOuter[iK++] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[iK++] = CHVector(0.015f, 0.0f, 1.0f, 1.0f);
			avOuter[iK++] = CHVector(0.015f, 0.0f, 0.825f, 1.0f);

			// 1 Vorkerbe:
			avOuter[iK++] = CHVector(0.07f, 0.0f, 0.81f, 1.0f);
			avOuter[iK++] = CHVector(0.115f, 0.0f, 0.805f, 1.0f);
			avOuter[iK++] = CHVector(0.115f, 0.0f, 0.798f, 1.0f);

			// F1:
			avOuter[iK++] = CHVector(0.1f, 0.0f, 0.79f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.8f, 1.0f);
			avOuter[iK++] = CHVector(0.18f, 0.0f, 0.775f, 1.0f);
			avOuter[iK++] = CHVector(0.17f, 0.0f, 0.75f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.21f, 0.0f, 0.75f, 1.0f);
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.715f, 1.0f);

			// F2:
			avOuter[iK++] = CHVector(0.215f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.26f, 0.0f, 0.69f, 1.0f);
			avOuter[iK++] = CHVector(0.29f, 0.0f, 0.67f, 1.0f);
			avOuter[iK++] = CHVector(0.285f, 0.0f, 0.66f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.3f, 0.0f, 0.66f, 1.0f);
			avOuter[iK++] = CHVector(0.32f, 0.0f, 0.64f, 1.0f);
			avOuter[iK++] = CHVector(0.32f, 0.0f, 0.61f, 1.0f);
			avOuter[iK++] = CHVector(0.3f, 0.0f, 0.603f, 1.0f);

			// F3:
			avOuter[iK++] = CHVector(0.27f, 0.0f, 0.6f, 1.0f);
			avOuter[iK++] = CHVector(0.3f, 0.0f, 0.59f, 1.0f);
			avOuter[iK++] = CHVector(0.33f, 0.0f, 0.58f, 1.0f);
			avOuter[iK++] = CHVector(0.375f, 0.0f, 0.54f, 1.0f);
			avOuter[iK++] = CHVector(0.37f, 0.0f, 0.523f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.39f, 0.0f, 0.52f, 1.0f);
			avOuter[iK++] = CHVector(0.42f, 0.0f, 0.5f, 1.0f);
			avOuter[iK++] = CHVector(0.425f, 0.0f, 0.49f, 1.0f);
			avOuter[iK++] = CHVector(0.4f, 0.0f, 0.475f, 1.0f);


			// F4:
			avOuter[iK++] = CHVector(0.38f, 0.0f, 0.47f, 1.0f);
			avOuter[iK++] = CHVector(0.45f, 0.0f, 0.45f, 1.0f);
			avOuter[iK++] = CHVector(0.47f, 0.0f, 0.425f, 1.0f);
			avOuter[iK++] = CHVector(0.485f, 0.0f, 0.4f, 1.0f);
			avOuter[iK++] = CHVector(0.48f, 0.0f, 0.39f, 1.0f);
			avOuter[iK++] = CHVector(0.475f, 0.0f, 0.377f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.48f, 0.0f, 0.37f, 1.0f);
			avOuter[iK++] = CHVector(0.497f, 0.0f, 0.36f, 1.0f);
			avOuter[iK++] = CHVector(0.5f, 0.0f, 0.34f, 1.0f);
			avOuter[iK++] = CHVector(0.497f, 0.0f, 0.32f, 1.0f);
			avOuter[iK++] = CHVector(0.48f, 0.0f, 0.31f, 1.0f);
			avOuter[iK++] = CHVector(0.47f, 0.0f, 0.305f, 1.0f);

			// F5:
			avOuter[iK++] = CHVector(0.42f, 0.0f, 0.31f, 1.0f);
			avOuter[iK++] = CHVector(0.44f, 0.0f, 0.275f, 1.0f);
			avOuter[iK++] = CHVector(0.45f, 0.0f, 0.274f, 1.0f);
			avOuter[iK++] = CHVector(0.46f, 0.0f, 0.25f, 1.0f);
			avOuter[iK++] = CHVector(0.46f, 0.0f, 0.23f, 1.0f);
			avOuter[iK++] = CHVector(0.44f, 0.0f, 0.225f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.45f, 0.0f, 0.2f, 1.0f);
			avOuter[iK++] = CHVector(0.45f, 0.0f, 0.175f, 1.0f);
			avOuter[iK++] = CHVector(0.41f, 0.0f, 0.16f, 1.0f);
			avOuter[iK++] = CHVector(0.37f, 0.0f, 0.17f, 1.0f);

			// F6:
			avOuter[iK++] = CHVector(0.35f, 0.0f, 0.2f, 1.0f);
			avOuter[iK++] = CHVector(0.335f, 0.0f, 0.18f, 1.0f);
			avOuter[iK++] = CHVector(0.31f, 0.0f, 0.18f, 1.0f);
			avOuter[iK++] = CHVector(0.28f, 0.0f, 0.21f, 1.0f);
			avOuter[iK++] = CHVector(0.265f, 0.0f, 0.23f, 1.0f);
			avOuter[iK++] = CHVector(0.265f, 0.0f, 0.23f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.235f, 1.0f);
			avOuter[iK++] = CHVector(0.23f, 0.0f, 0.225f, 1.0f);
			avOuter[iK++] = CHVector(0.22f, 0.0f, 0.25f, 1.0f);

			// A:
			avOuter[iK++] = CHVector(0.225f, 0.0f, 0.26f, 1.0f);
			avOuter[iK++] = CHVector(0.19f, 0.0f, 0.275f, 1.0f);
			avOuter[iK++] = CHVector(0.165f, 0.0f, 0.35f, 1.0f);
			avOuter[iK++] = CHVector(0.13f, 0.0f, 0.372f, 1.0f);
			avOuter[iK++] = CHVector(0.11f, 0.0f, 0.37f, 1.0f);
			avOuter[iK++] = CHVector(0.11f, 0.0f, 0.36f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.25f, 1.0f);
			avOuter[iK++] = CHVector(0.14f, 0.0f, 0.24f, 1.0f);
			avOuter[iK++] = CHVector(0.17f, 0.0f, 0.22f, 1.0f);
			avOuter[iK++] = CHVector(0.17f, 0.0f, 0.21f, 1.0f);

			// F7:
			avOuter[iK++] = CHVector(0.16f, 0.0f, 0.19f, 1.0f);
			avOuter[iK++] = CHVector(0.175f, 0.0f, 0.175f, 1.0f);
			avOuter[iK++] = CHVector(0.175f, 0.0f, 0.14f, 1.0f);
			avOuter[iK++] = CHVector(0.162f, 0.0f, 0.125f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.165f, 0.0f, 0.11f, 1.0f);
			avOuter[iK++] = CHVector(0.16f, 0.0f, 0.075f, 1.0f);
			avOuter[iK++] = CHVector(0.12f, 0.0f, 0.07f, 1.0f);
			avOuter[iK++] = CHVector(0.08f, 0.0f, 0.08f, 1.0f);
			avOuter[iK++] = CHVector(0.06f, 0.0f, 0.11f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.073f, 0.0f, 0.075f, 1.0f);
			avOuter[iK++] = CHVector(0.073f, 0.0f, 0.05f, 1.0f);
			avOuter[iK++] = CHVector(0.068f, 0.0f, 0.03f, 1.0f);
			avOuter[iK++] = CHVector(0.05f, 0.0f, 0.025f, 1.0f);
			avOuter[iK++] = CHVector(0.03f, 0.0f, 0.005f, 1.0f);


			avOuter[iK++] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

			if (uLoD == 0)
			{
				for (int i = 0; i < iK; i++)
					// for (int i = 0; i < 203; i++)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD == 1)
			{
				for (int i = 0; i < iK; i += 2)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD == 2)
			{
				for (int i = 0; i < iK; i += 4)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD == 3)
			{
				for (int i = 0; i < iK; i += 8)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD == 4)
			{
				for (int i = 0; i < iK; i += 16)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD == 5)
			{
				for (int i = 0; i < iK; i += 32)
					m_zgLeafMid.AddOuter(&avOuter[i]);
			}
			else if (uLoD >= 6)
			{
				m_zgLeafMid.AddOuter(&avOuter[0]);
				m_zgLeafMid.AddOuter(&avOuter[50]);
				m_zgLeafMid.AddOuter(&avOuter[100]);
				m_zgLeafMid.AddOuter(&avOuter[150]);
			}

			m_zgLeafMid.Init(&m_zmLeafMid, true, true, -0.0f, 0.0f, 0.04f, false);
			SetGeoLeaf(&m_zgLeafMid, 1);



		}

		// ----------------------
		// Erzeuge SeitenBl�tter: 
		// ----------------------

		m_zmLeaf.LoadPreset("LeafChelidoniumMajus");


		m_zgLeafLeft.SetMiddle(CHVector(0.0f, 0.07f, 0.5f, 1.0f));
		m_zgLeafRight.SetMiddle(CHVector(0.0f, 0.07f, 0.5f, 1.0f));

		{
			CHVector avOuter[210];
			CHVector avOuterMirror[210];

			int iK = 0;

			//S:
			avOuter[iK++] = CHVector(0.525f, 0.0f, 1.0f, 1.0f);
			avOuter[iK++] = CHVector(0.51f, 0.0f, 0.975f, 1.0f);
			avOuter[iK++] = CHVector(0.515f, 0.0f, 0.9f, 1.0f);
			avOuter[iK++] = CHVector(0.513f, 0.0f, 0.825f, 1.0f);
			avOuter[iK++] = CHVector(0.54f, 0.0f, 0.81f, 1.0f);
			avOuter[iK++] = CHVector(0.55f, 0.0f, 0.80f, 1.0f);

			// R1:
			avOuter[iK++] = CHVector(0.6f, 0.0f, 0.825f, 1.0f);
			avOuter[iK++] = CHVector(0.627f, 0.0f, 0.84f, 1.0f);
			avOuter[iK++] = CHVector(0.65f, 0.0f, 0.83f, 1.0f);
			avOuter[iK++] = CHVector(0.7f, 0.0f, 0.835f, 1.0f);
			avOuter[iK++] = CHVector(0.748f, 0.0f, 0.835f, 1.0f);
			avOuter[iK++] = CHVector(0.74f, 0.0f, 0.82f, 1.0f);

			// R2
			avOuter[iK++] = CHVector(0.72f, 0.0f, 0.8f, 1.0f);
			avOuter[iK++] = CHVector(0.78f, 0.0f, 0.82f, 1.0f);
			avOuter[iK++] = CHVector(0.825f, 0.0f, 0.8f, 1.0f);
			avOuter[iK++] = CHVector(0.826f, 0.0f, 0.79f, 1.0f);
			avOuter[iK++] = CHVector(0.82f, 0.0f, 0.78f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.85f, 0.0f, 0.778f, 1.0f);
			avOuter[iK++] = CHVector(0.875f, 0.0f, 0.77f, 1.0f);
			avOuter[iK++] = CHVector(0.88f, 0.0f, 0.734f, 1.0f);
			avOuter[iK++] = CHVector(0.85f, 0.0f, 0.72f, 1.0f);
			avOuter[iK++] = CHVector(0.83f, 0.0f, 0.71f, 1.0f);

			// R3
			avOuter[iK++] = CHVector(0.81f, 0.0f, 0.714f, 1.0f);
			avOuter[iK++] = CHVector(0.9f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.925f, 0.0f, 0.695f, 1.0f);
			avOuter[iK++] = CHVector(0.93f, 0.0f, 0.68f, 1.0f);
			avOuter[iK++] = CHVector(0.918f, 0.0f, 0.675f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.95f, 0.0f, 0.67f, 1.0f);
			avOuter[iK++] = CHVector(0.99f, 0.0f, 0.63f, 1.0f);
			avOuter[iK++] = CHVector(0.98f, 0.0f, 0.61f, 1.0f);
			avOuter[iK++] = CHVector(0.96f, 0.0f, 0.595f, 1.0f);
			avOuter[iK++] = CHVector(0.93f, 0.0f, 0.589f, 1.0f);
			avOuter[iK++] = CHVector(0.86f, 0.0f, 0.594f, 1.0f);

			// R4
			avOuter[iK++] = CHVector(0.85f, 0.0f, 0.585f, 1.0f);
			avOuter[iK++] = CHVector(0.86f, 0.0f, 0.57811f, 1.0f);
			avOuter[iK++] = CHVector(0.93f, 0.0f, 0.57f, 1.0f);
			avOuter[iK++] = CHVector(0.943f, 0.0f, 0.56f, 1.0f);
			avOuter[iK++] = CHVector(0.94f, 0.0f, 0.55f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.96f, 0.0f, 0.52f, 1.0f);
			avOuter[iK++] = CHVector(0.97f, 0.0f, 0.50f, 1.0f);
			avOuter[iK++] = CHVector(0.97f, 0.0f, 0.48f, 1.0f);
			avOuter[iK++] = CHVector(0.95f, 0.0f, 0.465f, 1.0f);
			avOuter[iK++] = CHVector(0.92f, 0.0f, 0.46f, 1.0f);
			avOuter[iK++] = CHVector(0.88f, 0.0f, 0.47f, 1.0f);

			// R5
			avOuter[iK++] = CHVector(0.88f, 0.0f, 0.46f, 1.0f);
			avOuter[iK++] = CHVector(0.92f, 0.0f, 0.448f, 1.0f);
			avOuter[iK++] = CHVector(0.93f, 0.0f, 0.43f, 1.0f);
			avOuter[iK++] = CHVector(0.93f, 0.0f, 0.42f, 1.0f);
			avOuter[iK++] = CHVector(0.92f, 0.0f, 0.41f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.94f, 0.0f, 0.40f, 1.0f);
			avOuter[iK++] = CHVector(0.943f, 0.0f, 0.35f, 1.0f);
			avOuter[iK++] = CHVector(0.94f, 0.0f, 0.33f, 1.0f);
			avOuter[iK++] = CHVector(0.9f, 0.0f, 0.32f, 1.0f);
			avOuter[iK++] = CHVector(0.875f, 0.0f, 0.325f, 1.0f);
			avOuter[iK++] = CHVector(0.84f, 0.0f, 0.33f, 1.0f);
			avOuter[iK++] = CHVector(0.82f, 0.0f, 0.35f, 1.0f);

			// R6
			avOuter[iK++] = CHVector(0.80f, 0.0f, 0.34f, 1.0f);
			avOuter[iK++] = CHVector(0.81f, 0.0f, 0.33f, 1.0f);
			avOuter[iK++] = CHVector(0.85f, 0.0f, 0.31f, 1.0f);
			avOuter[iK++] = CHVector(0.9f, 0.0f, 0.26f, 1.0f);
			avOuter[iK++] = CHVector(0.9f, 0.0f, 0.245f, 1.0f);
			avOuter[iK++] = CHVector(0.89f, 0.0f, 0.23f, 1.0f);
			avOuter[iK++] = CHVector(0.87f, 0.0f, 0.225f, 1.0f);
			avOuter[iK++] = CHVector(0.85f, 0.0f, 0.268f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.86f, 0.0f, 0.215f, 1.0f);
			avOuter[iK++] = CHVector(0.862f, 0.0f, 0.195f, 1.0f);
			avOuter[iK++] = CHVector(0.86f, 0.0f, 0.15f, 1.0f);
			avOuter[iK++] = CHVector(0.84f, 0.0f, 0.14f, 1.0f);
			avOuter[iK++] = CHVector(0.80f, 0.0f, 0.125f, 1.0f);
			avOuter[iK++] = CHVector(0.75f, 0.0f, 0.135f, 1.0f);
			avOuter[iK++] = CHVector(0.70f, 0.0f, 0.17f, 1.0f);
			avOuter[iK++] = CHVector(0.67f, 0.0f, 0.21f, 1.0f);
			avOuter[iK++] = CHVector(0.65f, 0.0f, 0.225f, 1.0f);

			// R7
			avOuter[iK++] = CHVector(0.64f, 0.0f, 0.23f, 1.0f);
			avOuter[iK++] = CHVector(0.637f, 0.0f, 0.21f, 1.0f);
			avOuter[iK++] = CHVector(0.66f, 0.0f, 0.18f, 1.0f);
			avOuter[iK++] = CHVector(0.675f, 0.0f, 0.15f, 1.0f);
			avOuter[iK++] = CHVector(0.68f, 0.0f, 0.12f, 1.0f);
			avOuter[iK++] = CHVector(0.68f, 0.0f, 0.1f, 1.0f);
			avOuter[iK++] = CHVector(0.67f, 0.0f, 0.06f, 1.0f);
			avOuter[iK++] = CHVector(0.674, 0.0f, 0.05f, 1.0f);
			avOuter[iK++] = CHVector(0.59, 0.0f, 0.075f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.59, 0.0f, 0.04f, 1.0f);
			avOuter[iK++] = CHVector(0.54, 0.0f, 0.01f, 1.0f);
			avOuter[iK++] = CHVector(0.50, 0.0f, 0.00f, 1.0f);
			avOuter[iK++] = CHVector(0.45, 0.0f, 0.02f, 1.0f);
			avOuter[iK++] = CHVector(0.40, 0.0f, 0.05f, 1.0f);
			avOuter[iK++] = CHVector(0.38, 0.0f, 0.07f, 1.0f);
			avOuter[iK++] = CHVector(0.38, 0.0f, 0.08f, 1.0f);

			// L1
			avOuter[iK++] = CHVector(0.4, 0.0f, 0.11f, 1.0f);
			avOuter[iK++] = CHVector(0.39, 0.0f, 0.105f, 1.0f);
			avOuter[iK++] = CHVector(0.38, 0.0f, 0.08f, 1.0f);
			avOuter[iK++] = CHVector(0.35, 0.0f, 0.075f, 1.0f);
			avOuter[iK++] = CHVector(0.26, 0.0f, 0.09f, 1.0f);
			avOuter[iK++] = CHVector(0.26, 0.0f, 0.16f, 1.0f);
			avOuter[iK++] = CHVector(0.275, 0.0f, 0.175f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.26, 0.0f, 0.19f, 1.0f);
			avOuter[iK++] = CHVector(0.26, 0.0f, 0.2f, 1.0f);
			avOuter[iK++] = CHVector(0.3, 0.0f, 0.24f, 1.0f);
			avOuter[iK++] = CHVector(0.35, 0.0f, 0.275f, 1.0f);

			// L2
			avOuter[iK++] = CHVector(0.33f, 0.0f, 0.28f, 1.0f);
			avOuter[iK++] = CHVector(0.29f, 0.0f, 0.241f, 1.0f);
			avOuter[iK++] = CHVector(0.26f, 0.0f, 0.223f, 1.0f);
			avOuter[iK++] = CHVector(0.2f, 0.0f, 0.2f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.19f, 1.0f);
			avOuter[iK++] = CHVector(0.09f, 0.0f, 0.21f, 1.0f);
			avOuter[iK++] = CHVector(0.07f, 0.0f, 0.22f, 1.0f);
			avOuter[iK++] = CHVector(0.07f, 0.0f, 0.25f, 1.0f);
			avOuter[iK++] = CHVector(0.073f, 0.0f, 0.275f, 1.0f);
			avOuter[iK++] = CHVector(0.1f, 0.0f, 0.3f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.09f, 0.0f, 0.324f, 1.0f);
			avOuter[iK++] = CHVector(0.075f, 0.0f, 0.34f, 1.0f);
			avOuter[iK++] = CHVector(0.078f, 0.0f, 0.36f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.4f, 1.0f);
			avOuter[iK++] = CHVector(0.2f, 0.0f, 0.41f, 1.0f);

			// L3 
			avOuter[iK++] = CHVector(0.21f, 0.0f, 0.425f, 1.0f);
			avOuter[iK++] = CHVector(0.19f, 0.0f, 0.427f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.423f, 1.0f);
			avOuter[iK++] = CHVector(0.11f, 0.0f, 0.43f, 1.0f);
			avOuter[iK++] = CHVector(0.09f, 0.0f, 0.45f, 1.0f);
			avOuter[iK++] = CHVector(0.085f, 0.0f, 0.475f, 1.0f);
			avOuter[iK++] = CHVector(0.137f, 0.0f, 0.5f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.13f, 0.0f, 0.525f, 1.0f);
			avOuter[iK++] = CHVector(0.17f, 0.0f, 0.538f, 1.0f);
			avOuter[iK++] = CHVector(0.24f, 0.0f, 0.544f, 1.0f);

			// L4 
			avOuter[iK++] = CHVector(0.24f, 0.0f, 0.554f, 1.0f);
			avOuter[iK++] = CHVector(0.20f, 0.0f, 0.56f, 1.0f);
			avOuter[iK++] = CHVector(0.18f, 0.0f, 0.575f, 1.0f);
			avOuter[iK++] = CHVector(0.175f, 0.0f, 0.6f, 1.0f);
			avOuter[iK++] = CHVector(0.21f, 0.0f, 0.62f, 1.0f);
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.618f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.234f, 0.0f, 0.63f, 1.0f);
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.64f, 1.0f);
			avOuter[iK++] = CHVector(0.28f, 0.0f, 0.64f, 1.0f);

			// L5 
			avOuter[iK++] = CHVector(0.32f, 0.0f, 0.65f, 1.0f);
			avOuter[iK++] = CHVector(0.307f, 0.0f, 0.665f, 1.0f);
			avOuter[iK++] = CHVector(0.31f, 0.0f, 0.674f, 1.0f);
			avOuter[iK++] = CHVector(0.335f, 0.0f, 0.69f, 1.0f);
			avOuter[iK++] = CHVector(0.335f, 0.0f, 0.69f, 1.0f);
			avOuter[iK++] = CHVector(0.35f, 0.0f, 0.687f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.37f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.385f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.42f, 0.0f, 0.69f, 1.0f);
			avOuter[iK++] = CHVector(0.46f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.48f, 0.0f, 0.725f, 1.0f);
			avOuter[iK++] = CHVector(0.47f, 0.0f, 0.75f, 1.0f);
			avOuter[iK++] = CHVector(0.46f, 0.0f, 0.77f, 1.0f);
			// N1 
			avOuter[iK++] = CHVector(0.445f, 0.0f, 0.785f, 1.0f);
			avOuter[iK++] = CHVector(0.43f, 0.0f, 0.785f, 1.0f);
			avOuter[iK++] = CHVector(0.405f, 0.0f, 0.77f, 1.0f);
			avOuter[iK++] = CHVector(0.4f, 0.0f, 0.75f, 1.0f);
			avOuter[iK++] = CHVector(0.35f, 0.0f, 0.72f, 1.0f);
			avOuter[iK++] = CHVector(0.315f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.293f, 0.0f, 0.705f, 1.0f);
			avOuter[iK++] = CHVector(0.293f, 0.0f, 0.715f, 1.0f); //Kerbe
			avOuter[iK++] = CHVector(0.26f, 0.0f, 0.7f, 1.0f);
			avOuter[iK++] = CHVector(0.18f, 0.0f, 0.687f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.69f, 1.0f);
			avOuter[iK++] = CHVector(0.13f, 0.0f, 0.7f, 1.0f);

			// N2 
			avOuter[iK++] = CHVector(0.14f, 0.0f, 0.72f, 1.0f);
			avOuter[iK++] = CHVector(0.11f, 0.0f, 0.716f, 1.0f);
			avOuter[iK++] = CHVector(0.05f, 0.0f, 0.715f, 1.0f);
			avOuter[iK++] = CHVector(0.025f, 0.0f, 0.72f, 1.0f);
			avOuter[iK++] = CHVector(0.0125f, 0.0f, 0.735f, 1.0f);
			avOuter[iK++] = CHVector(0.008f, 0.0f, 0.75f, 1.0f);
			avOuter[iK++] = CHVector(0.18f, 0.0f, 0.77f, 1.0f);
			avOuter[iK++] = CHVector(0.05f, 0.0f, 0.78f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.03f, 0.0f, 0.8f, 1.0f);
			avOuter[iK++] = CHVector(0.035f, 0.0f, 0.825f, 1.0f);
			avOuter[iK++] = CHVector(0.06f, 0.0f, 0.83f, 1.0f);
			avOuter[iK++] = CHVector(0.09f, 0.0f, 0.84f, 1.0f);

			// N3 
			avOuter[iK++] = CHVector(0.14f, 0.0f, 0.84f, 1.0f);
			avOuter[iK++] = CHVector(0.14f, 0.0f, 0.842f, 1.0f);
			avOuter[iK++] = CHVector(0.09f, 0.0f, 0.86f, 1.0f);
			avOuter[iK++] = CHVector(0.075f, 0.0f, 0.87f, 1.0f);
			avOuter[iK++] = CHVector(0.08f, 0.0f, 0.88f, 1.0f);
			avOuter[iK++] = CHVector(0.1f, 0.0f, 0.9f, 1.0f);
			avOuter[iK++] = CHVector(0.12f, 0.0f, 0.91f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.9f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.14f, 0.0f, 0.92f, 1.0f);
			avOuter[iK++] = CHVector(0.15f, 0.0f, 0.925f, 1.0f);
			avOuter[iK++] = CHVector(0.17f, 0.0f, 0.928f, 1.0f);
			avOuter[iK++] = CHVector(0.22f, 0.0f, 0.925f, 1.0f);

			// N4
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.92f, 1.0f);
			avOuter[iK++] = CHVector(0.21f, 0.0f, 0.96f, 1.0f);
			avOuter[iK++] = CHVector(0.20f, 0.0f, 0.97f, 1.0f);
			avOuter[iK++] = CHVector(0.22f, 0.0f, 0.99f, 1.0f);
			avOuter[iK++] = CHVector(0.25f, 0.0f, 0.993f, 1.0f);
			avOuter[iK++] = CHVector(0.3f, 0.0f, 0.975f, 1.0f);
			avOuter[iK++] = CHVector(0.33f, 0.0f, 0.965f, 1.0f); // Kerbe
			avOuter[iK++] = CHVector(0.33f, 0.0f, 0.975f, 1.0f);
			avOuter[iK++] = CHVector(0.34f, 0.0f, 0.99f, 1.0f);
			avOuter[iK++] = CHVector(0.4f, 0.0f, 0.975f, 1.0f);
			avOuter[iK++] = CHVector(0.425f, 0.0f, 0.952f, 1.0f); // Minikerbe
			avOuter[iK++] = CHVector(0.44f, 0.0f, 0.952f, 1.0f);
			avOuter[iK++] = CHVector(0.47f, 0.0f, 0.925f, 1.0f);
			avOuter[iK++] = CHVector(0.475f, 0.0f, 0.91f, 1.0f);
			avOuter[iK++] = CHVector(0.47f, 0.0f, 0.9f, 1.0f);

			// S
			avOuter[iK++] = CHVector(0.495f, 0.0f, 0.9f, 1.0f);
			avOuter[iK++] = CHVector(0.495f, 0.0f, 0.93f, 1.0f);
			avOuter[iK++] = CHVector(0.48f, 0.0f, 0.96f, 1.0f);
			avOuter[iK++] = CHVector(0.46f, 0.0f, 1.00f, 1.0f);

			if (uLoD == 0)
			{
				for (int i = 0; i < iK; i++)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 1)
			{
				for (int i = 0; i < iK; i += 2)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 2)
			{
				for (int i = 0; i < iK; i += 4)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 3)
			{
				for (int i = 0; i < iK; i += 8)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 4)
			{
				for (int i = 0; i < iK; i += 16)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 5)
			{
				for (int i = 0; i < iK; i += 32)
				{
					m_zgLeafLeft.AddOuter(&avOuter[i]);
					avOuterMirror[i] = avOuter[i];
					m_zgLeafRight.AddOuter(&avOuterMirror[i]);
				}
			}
			else if (uLoD == 6)
			{
				m_zgLeafLeft.AddOuter(&avOuter[0]);
				m_zgLeafLeft.AddOuter(&avOuter[50]);
				m_zgLeafLeft.AddOuter(&avOuter[100]);
				m_zgLeafLeft.AddOuter(&avOuter[150]);
				avOuterMirror[0] = avOuter[0];
				avOuterMirror[50] = avOuter[50];
				avOuterMirror[100] = avOuter[100];
				avOuterMirror[150] = avOuter[150];

				m_zgLeafRight.AddOuter(&avOuterMirror[0]);
				m_zgLeafRight.AddOuter(&avOuterMirror[50]);
				m_zgLeafRight.AddOuter(&avOuterMirror[100]);
				m_zgLeafRight.AddOuter(&avOuterMirror[150]);
			}



			m_zgLeafLeft.Init(&m_zmLeaf, true, false, -0.0f, 0.0f, 0.3f, false);
			SetGeoLeaf(&m_zgLeafLeft);

			m_zgLeafRight.Init(&m_zmLeaf, true, false, -0.0f, 0.0f, 0.3f, true);
			SetGeoLeaf(&m_zgLeafRight, 2U);

		}

		SetMaxNeedleBending(QUARTERPI * 0.5f);
		SetMaxNeedleFolding(0.1f);
		SetMaxLeafBending(QUARTERPI * 0.5f);
		SetMaxLeafFolding(0.1f);

		// --------------------
		// Erzeuge Staubblatt: 
		// --------------------

		m_zmBlossom.LoadPreset("LeafBlossom");

		m_zgStamenMain.SetMiddle(CHVector(0.0f, 0.0f, 0.9f, 1.0f));
		if (uLoD == 0)
		{
			CHVector avOuter[8];
			//Stiel:
			avOuter[0] = CHVector(0.00f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.04f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.03f, 0.0f, 0.6f, 1.0f);
			avOuter[3] = CHVector(0.035f, 0.0f, 0.2f, 1.0f);

			//Staubstempel:
			avOuter[4] = CHVector(0.20f, 0.0f, 0.18f, 1.0f);
			avOuter[5] = CHVector(0.20f, 0.0f, 0.02f, 1.0f);
			avOuter[6] = CHVector(0.07f, 0.0f, 0.00f, 1.0f);
			avOuter[7] = CHVector(0.00f, 0.0f, 0.00f, 1.0f);
			for (int i = 0; i < 8; i++)
				m_zgStamenMain.AddOuter(&avOuter[i]);

			SetMaxStamenBending(0.5f);
			SetMaxStamenFolding(0.1f);

			m_zgStamenMain.Init(&m_zmBlossom, true, true, -0.0f, 0.0f, 0.0f);
			SetGeoStamen(&m_zgStamenMain);
		}


		// --------------------
		// Erzeuge Bl�tenblatt: 
		// --------------------


		m_zgBlossomMain.SetMiddle(CHVector(0.0f, 0.03f, 0.5f, 1.0f));
		if (uLoD == 0)
		{
			CHVector avOuter[15];

			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.1f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.15f, 0.0f, 0.95f, 1.0f);

			//Ausbuchtung:
			avOuter[3] = CHVector(0.20f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.25f, 0.0f, 0.85f, 1.0f);
			avOuter[5] = CHVector(0.28f, 0.0f, 0.8f, 1.0f);
			avOuter[6] = CHVector(0.43f, 0.0f, 0.7f, 1.0f);
			avOuter[7] = CHVector(0.45f, 0.0f, 0.6f, 1.0f);
			avOuter[8] = CHVector(0.48f, 0.0f, 0.5f, 1.0f);
			avOuter[9] = CHVector(0.48f, 0.0f, 0.45f, 1.0f);
			avOuter[10] = CHVector(0.45f, 0.0f, 0.3f, 1.0f);
			avOuter[11] = CHVector(0.30f, 0.0f, 0.1f, 1.0f);
			avOuter[12] = CHVector(0.25f, 0.0f, 0.05f, 1.0f);
			avOuter[13] = CHVector(0.15f, 0.0f, 0.02f, 1.0f);
			avOuter[14] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);

			/*
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.90f, 1.0f);

			//Ausbuchtung:
			avOuter[3] = CHVector(0.04f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.15f, 0.0f, 0.85f, 1.0f);
			avOuter[5] = CHVector(0.3f, 0.0f, 0.8f, 1.0f);
			avOuter[6] = CHVector(0.4f, 0.0f, 0.7f, 1.0f);
			avOuter[7] = CHVector(0.45f, 0.0f, 0.6f, 1.0f);
			avOuter[8] = CHVector(0.48f, 0.0f, 0.5f, 1.0f);
			avOuter[9] = CHVector(0.45f, 0.0f, 0.4f, 1.0f);
			avOuter[10] = CHVector(0.38f, 0.0f, 0.3f, 1.0f);
			avOuter[11] = CHVector(0.27f, 0.0f, 0.2f, 1.0f);
			avOuter[12] = CHVector(0.12f, 0.0f, 0.12f, 1.0f);
			avOuter[13] = CHVector(0.02f, 0.0f, 0.05f, 1.0f);
			avOuter[14] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
			*/
			for (int i = 0; i < 15; i++)
				m_zgBlossomMain.AddOuter(&avOuter[i]);
			SetMaxBlossomBending(0.05f);
			SetMaxBlossomFolding(0.01f);
			m_zgBlossomMain.Init(&m_zmBlossom, true, true, 0.0f, 0.0f, 0.02f);
			SetGeoBlossom(&m_zgBlossomMain);
		}
		else
		{
			CHVector avOuter[9];
			//Stiel:
			avOuter[0] = CHVector(0.0f, 0.0f, 1.0f, 1.0f);
			avOuter[1] = CHVector(0.020f, 0.0f, 1.0f, 1.0f);
			avOuter[2] = CHVector(0.015f, 0.0f, 0.90f, 1.0f);

			//Ausbuchtung:
			avOuter[3] = CHVector(0.04f, 0.0f, 0.90f, 1.0f);
			avOuter[4] = CHVector(0.3f, 0.0f, 0.8f, 1.0f);
			avOuter[5] = CHVector(0.45f, 0.0f, 0.6f, 1.0f);
			avOuter[6] = CHVector(0.45f, 0.0f, 0.4f, 1.0f);
			avOuter[7] = CHVector(0.27f, 0.0f, 0.2f, 1.0f);
			avOuter[8] = CHVector(0.0f, 0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 9; i++)
				m_zgBlossomMain.AddOuter(&avOuter[i]);


			m_zgBlossomMain.Init(&m_zmBlossom, true, true);
			SetGeoBlossom(&m_zgBlossomMain);
		}

		/*
			CHMat mScale;
		mScale.ScaleX(0.05f);
		m_zgLeafMain.Transform(mScale);
		*/

		SetMaterialLeaf(&m_zmLeaf);

		m_zmBark.LoadPreset("BarkChelidoniumMajus");
		m_zmBark.SetBumpStrength(20);
		m_zmBark.SetHeightStrength(10);
		SetMaterial(&m_zmBark);

		// SetSwakeRandomFactor(m_fSwakeRandom);
		SetTurtleStartHeight(m_fTurtleStartLength);
		SetTurtleStartRadius(m_fTurtleStartRadius);
		SetDefaultFactorGravitation(0.5f);

		if (uLoD == 1)
		{
			m_iTurtleStartLongitude /= 2;
			m_iTurtleStartLattitude /= 2;
		}
		if (uLoD == 2)
		{
			m_iTurtleStartLongitude /= 4;
			m_iTurtleStartLattitude /= 4;
			if (m_iTurtleStartLongitude < 4)
				m_iTurtleStartLongitude = 4;
		}
		if (uLoD >= 3)
		{
			m_iTurtleStartLongitude /= 6;
			m_iTurtleStartLattitude /= 6;
			if (m_iTurtleStartLongitude < 4)
				m_iTurtleStartLongitude = 4;

			if (uLoD >= 5)
			{
				m_iTurtleStartLongitude = 0;
				m_iTurtleStartLattitude = 0;
			}
			SetTurtleEndLongitude(0);
			SetTurtleEndLattitude(0);

		}
		if (m_iTurtleStartLattitude == 1)
			m_iTurtleStartLattitude = 2;
		if (m_iTurtleStartLattitude == 0 && m_iTurtleStartLongitude > 0)
			m_iTurtleStartLattitude = 2;
		SetTurtleStartLongitude(m_iTurtleStartLongitude);
		SetTurtleStartLattitude(m_iTurtleStartLattitude);

		Interprete(acTurtleOrdersMain);

		// ---------------
		// Erzeuge Wurzel:
		// ---------------

	/*
		if (pzgTemplate->m_pzgRoot && uLoD < 2)
		{
			if (!m_pzgRoot)
				m_pzgRoot = new CGeoLSystem();

			char * acTurtleOrdersRoot = pzgTemplate->m_pzgRoot->m_pacToKill[pzgTemplate->m_pzgRoot->m_iToKill - 1];
			m_pzgRoot->m_random.m_uRand = pzgTemplate->m_pzgRoot->m_random.m_uRand;

			m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
			m_pzgRoot->SetDefaultFactorGravitation(0.1f);

			m_pzgRoot->SetMaterial(&m_zmBark);		// Schrittweise Reduzierung der Segmentl�nge (Default: 1.0)
			m_pzgRoot->SetTurtleStartDir(CHVector(0.0f, -1.0f, 0.0f, 0.0f));
			//		m_pzgRoot->SetTurtleStartPos(CHVector(0.0f, 2.5f, 0.0f, 1.0f));

			m_pzgRoot->SetRootCutHeight(m_fRootCutHeight);
			m_pzgRoot->SetTextureRepeat(-1.0f, 1.0f);
			m_pzgRoot->SetSwakeRandomFactor(m_fSwakeRandom);
			m_pzgRoot->SetTurtleStartHeight(m_fTurtleStartLength);
			m_pzgRoot->SetTurtleStartRadius(m_fTurtleStartRadius);
			m_pzgRoot->SetTurtleStartLongitude(m_iTurtleStartLongitude);
			m_pzgRoot->SetTurtleStartLattitude(m_iTurtleStartLattitude);
			m_pzgRoot->SetDefaultAngles(80.0f, 80.0f, PHI);				// Angabe der Rotationswinkel der Turtle (Default: 10, 10, 10)
			m_pzgRoot->SetDefaultFactorGravitation(0.1f);

			m_pzgRoot->Interprete(acTurtleOrdersRoot);

			AddGeo(m_pzgRoot);
		}
		*/

	}

	float CGeoGanjaPlant::GetOptimalLoDMin(float fAge, unsigned int uLoD)
	{
		float m_fAgeStopped = fAge;
		if (m_fAgeStopped > 1.0f)
			m_fAgeStopped = 1.0f;
		if (m_fAgeStopped < 0.01f)
			m_fAgeStopped = 0.01f;
		if (uLoD == 0)
			return 0.0F;
		return (5.f + m_fAgeStopped * 5.0f) * powf(4.0f, uLoD - 1);
	}

	float CGeoGanjaPlant::GetOptimalLoDMax(float fAge, unsigned int uLoD)
	{
		float m_fAgeStopped = fAge;
		if (m_fAgeStopped > 1.0f)
			m_fAgeStopped = 1.0f;
		if (m_fAgeStopped < 0.01f)
			m_fAgeStopped = 0.01f;
		return (5.f + m_fAgeStopped * 5.0f) * powf(4.0f, uLoD);
	}