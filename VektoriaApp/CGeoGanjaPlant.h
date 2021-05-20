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
	void Init(CGeoGanjaPlant* pzgTemplate, unsigned int uLoD = 0);

	///<summary> Gibt den Entfernungswert in Units (=Metern) f�r die optimale Distanz der minimalen LoD-Stufe aus. <para></para>
	/// Optimal, hei�t hier, dass bei einem 4K-Monitor das Switchen optisch nicht mehr wahrgenommen wird, da es weniger als 4 Pixel betrift.<para></para>
	/// Will man eine h�here Frame-Rate, auf Kosten des LoD-Poppings, kann z.B. durch einen Faktor > 1 geteilt werden. </summary> 
	///<param name="fAge"> Alter des Gra�es in Jahren (Je �lter, desto gr��er und komplexer). </param>
	///<param name="uLoD"> Level of Detail-Stufe <para></para>
	/// 0 => h�chstpolygonale Stufe, <para></para>
	/// 1 => zweith�chstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
	/// 2 => dritth�chstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
	/// 3 => etc.</param>
	float GetOptimalLoDMin(float fAge, unsigned int uLoD);

	///<summary> Gibt den Entfernungswert in Units (=Metern) f�r die optimale Distanz der minimalen LoD-Stufe aus. <para></para>
	/// Optimal, hei�t hier, dass bei einem 4K-Monitor das Switchen optisch nicht mehr wahrgenommen wird, da es weniger als 4 Pixel betrift.<para></para>
	/// Will man eine h�here Frame-Rate, auf Kosten des LoD-Poppings, kann z.B. durch einen Faktor > 1 geteilt werden. </summary> 
	///<param name="fAge"> Alter des Gra�es in Jahren (Je �lter, desto gr��er und komplexer). </param>
	///<param name="uLoD"> Level of Detail-Stufe <para></para>
	/// 0 => h�chstpolygonale Stufe, <para></para>
	/// 1 => zweith�chstpolygonale Stufe, ca. ein Viertel Polys weniger als Stufe 0).,<para></para>
	/// 2 => dritth�chstpolygonale Stufe, ca. ein Sechszehntel Polys weniger als Stufe 0).<para></para>
	/// 3 => etc.</param>
	float GetOptimalLoDMax(float fAge, unsigned int uLoD);

	///<summary> Haupt-Bl�tenblatt-Geometrie </summary>
	CGeoLeaf m_zgStamenMain;

	///<summary> Haupt-Bl�tenblatt-Geometrie </summary>
	CGeoLeaf m_zgBlossomMain;

	///<summary> Geometrievorlage der linken Bl�tter</summary>
	CGeoLeaf m_zgLeafLeft;

	///<summary> Geometrievorlage der mittleren Bl�tter </summary>
	CGeoLeaf m_zgLeafMid;

	///<summary> Geometrievorlage der rechten Bl�tter </summary>
	CGeoLeaf m_zgLeafRight;

	///<summary> Haupt-Frucht-Geometrie </summary>
	CGeoTriangleTable m_zgFruitMain;

	///<summary> Material des mittleren Blattes </summary>
	CMaterial m_zmLeafMid;
};

