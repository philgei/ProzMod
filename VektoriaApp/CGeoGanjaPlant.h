#pragma once
#include "Vektoria\Root.h"
#include "Util.h"
class CGeoGanjaPlant : public CGeoBio
{
public:
	CGeoGanjaPlant();
	~CGeoGanjaPlant();

	void Iterate(float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0f);

	///<summary> Sollte nach "Iterate"- und allen "Init"-Methodenaufrufen final aufgerufen werden, <para></para>
	/// um das L-System wieder zu zerst�ren und den Speicher freizugeben. </summary> 
	void DeIterate();

	///<summary> Erzeugt die Baumgeometrie f�r eine ausgew�hlte Level of Detail-Stufe. <para></para>
	/// Achtung! Vor "Init" muss die Methode "Iterate" aufgerufen werden.  </summary> 
	///<param name="pzgTemplate"> Pointer zu einer Vorlage-Birke, bei der schon Iterate aufgerufen wurde, <para></para>
	/// um das L-System zu erzeugen. </param>
	///<param name="uLoD"> Level of Detail-Stufe <para></para>
	/// 0 => h�chstpolygonale Stufe, <para></para>
	/// 1 => zweith�chstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
	/// 2 => dritth�chstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
	/// 3 => etc.</param>
	void Init(CGeoGanjaPlant* pzgTemplate);
};

