#include "CGeoGanjaPlant.h"

	CGeoGanjaPlant::CGeoGanjaPlant()
	{
	}


	CGeoGanjaPlant::~CGeoGanjaPlant()
	{
	}

	void CGeoGanjaPlant::Iterate(float fAge, float frTimeOfYear, float fRootCutHeight)
	{

		//Fragen: warum m_fTurtleStartLength und dann noch SetTurtleStartHeight(1)???
		m_fAgeStopped = fAge;


		m_iIterations = fAge;
		m_iTurtleStartLongitude = 15;
		m_iTurtleStartLattitude = 23;


		SetDefaultAngles(HALFPI/2, HALFPI/2, HALFPI/2);
		SetDefaultFactorGravitation(0.1f);
		SetDefaultFactorSide(0.01f);
		SetTurtleStartHeight(1);
		SetTurtleStartRadius(0.04);
		//------------------------
		// Erzeuge Stamm und Geäst:
		//------------------------

		// A: Anfang
		// X: Stängel 
		// Z: Zweig mit Blättern
		// B: Blütenverzweigung
		// Y: Blüte

		// Soll Blüten (Y) ausbilden, wenn Stägelra6dius unter einem mm:

		SetAxiom("A");

		AddRule("A=/(l0.9)(r0.95)+f[<Z][>Z]A");
		AddRule("Z=(l0.01)(r0.3)f(l50)X");
		AddRule("X=!f(l0.5)X");

		//	AddRule("A=f(<70)fZ");

			// AddRule("20:A=[(<20)f][(>23)f][(^53)f]");
			/*
			AddRule("20:A=(l0.1)(^12)f(l10)f°(v10)X");
			AddRule("20:A=(l0.1)(^10)f(l10)f[°(<30)fX][°(>23)fX][°°(^53)fX]");
			AddRule("30:A=(l0.1)(v12)f(l10)f[°(<23)fX](+10)[°(<30)fX][°(>23)fX][°(>53)fX][°(v7)fX]");
			AddRule("30:A=(l0.1)(^15)f(l10)f[°(<20)fX][°(>23)fX][°°(v53)fX](+5)[°°(^63)fX][°(<12)fX]");
			*/
		
		//AddRule("A=(r0.7)f[(r0.05)<Z][(r0.05)>Z]+A");
		//AddRule("Z={l>0.05, (l0.7)fZ}");
		//AddRule("Z=(<50)(r0.5)(l0.01)f(l100)(r0.5)f");
		//AddRule("50:Z=(r0.2)(>50)f(r5.0)");
		//AddRule("50:A=(l0.1)f(l10)f[°(<90)f(>80)X][°(>90)f(<80)fX][°(^90)f(v80)fX]");
		//AddRule("50:A=(l0.1)f(l10)f[°(<90)f(>80)X][°(>90)f(<80)fX][°(^90)f(v80)fX][°(v20)f(^4)fX]");

		//AddRule("20:X={r>0.01,°(^14)[(^70)(r0.5)Z]+(r0.8)(l0.9)fX}{r<0.010,fB}");
		//AddRule("20:X={r>0.01,°(<5)[(^72)(r0.6)Z]+(r0.9)(l0.85)fX}{r<0.010,fB}");
		//AddRule("30:X={r>0.01,°(v12)[(^73)(r0.7)Z]+[(^30)(r0.8)(l0.9)fX][(v40)°(l0.9)fX]}{r<0.010,fB}");
		//AddRule("30:X={r>0.01,°(>22)[(^87)(r0.5)Z]+(r0.9)(l0.9)fX}{r<0.010,B}");

		//AddRule("50:B=°(l0.8)(r0.7)[(^60)fY][(v72)fY][(>72)fY][(<72)fY][(<5)fY]");
		//AddRule("50:B=°(l0.85)(r0.8)[(^60)fY](+120)[(^62)fY](+120)[(^42)fY]");


		//// Der Zweig:
		//AddRule("50:Z=&f(l0.8)[(<70)(r80)(l2)&2l][(>70)(r80)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r100)(l2.5)1l");
		//AddRule("50:Z=&f(l0.8)[(<70)(r80)(l2)&2l][(>70)(r80)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r0.7)(l0.8)f[(<70)(r82)(l2)&2l][(>67)(r73)(l2)&0l](r100)(l2.5)1l");

		//// Die Blüte:
		//AddRule("Y=(r10.0)(l0.5)[<b][^b][>b][vb](l0.6)[(<20.2)c][(^18.4)c][(>20.4)c][(v22.4)c](+40.0)[(<10.2)c][(^11.4)c][(>14.4)c][(v12.4)c]");

		CGeoLSystem::Iterate(m_iIterations, m_acAxiom);
	}

	void CGeoGanjaPlant::DeIterate()
	{
		((CGeoLSystem*)this)->DeIterate();
		if (m_pzgRoot)
			m_pzgRoot->DeIterate();
	}


	void CGeoGanjaPlant::Init(CGeoGanjaPlant* pzgTemplate)
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

		m_zmBark.LoadPreset("BarkChelidoniumMajus");
		m_zmBark.SetBumpStrength(20);
		m_zmBark.SetHeightStrength(10);
		SetMaterial(&m_zmBark);


		Interprete(acTurtleOrdersMain);

	}