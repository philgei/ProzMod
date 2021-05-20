#pragma once
#include "Vektoria\Root.h"
#include "GeoBioChelidoniumMajus.h"

//----------------------------------------------------------------------------
// CGeoBioChelidoniumMajus 
// 
// Erkl�rung: Klasse, um prozedural realistische Sch�llkraut-Placements 
//	      mit optimalen LODs und Untergeometrien zu erzeugen
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Zeit     : seit Nov. 2019 (mit seitdem st�ndigen Verbesserungs-Updates) 
// Copyright: Tobias Breiner und die panokratischen U-Topienauten
//----------------------------------------------------------------------------

#define PLANTCHELIDONIUMMAJUS_LODS 5


using namespace Vektoria

	class CPlantChelidoniumMajus : public CPlacement
	{
	public:
		///<summary> Konstruktor </summary> 
		CPlantChelidoniumMajus();
	
		///<summary> Destruktor </summary> 
		~CPlantChelidoniumMajus();

		///<summary> Erzeugt das L-System f�r die Pflanzengeometrie. <para></para>
		/// Achtung Nr. 1! Nach "Iterate" m�ssen eine oder mehere "Init"-Methoden verschiedener Objektinstanzen aufgerufen werden, um die Geometrie zu erzeugen. 
		/// Achtung Nr. 2! Nach allen "Init"-Methodenaufrufen sollte "Deiterate" aufgerufen werden, um das L-System wieder zu zerst�ren und den Speicher freizugeben. </summary> 
		///<param name="iRandomSeed"> Anfang der Pseudozufallsreihenfolge f�r den Aufbau des Baumes <para></para>
		/// (bei gleichem iRandomSeed wird der gleiche Baum erzeugt) </param>
		///<param name="fAge"> Alter der Pflanze in Jahren (Je �lter, desto gr��er und komplexer). </param>
		///<param name="frTimeOfYear"> Fraktionale Jahreszeit (Fr�hlingstagundnachtgleiche = 0.0f .. Sommersonnenwende  = 0.25f ... Herbsttagundnachtgleiche = 0.5f ... Wintersonnenwende = 0.75f) <para></para>
		/// Wichtig f�r Farbe und Aussehen der Bl�tter. </param>
		///<param name="fRootCutHeight"> Unter dieser H�he werden die Wurzeln nicht mehr erzeugt. <para></para>
		/// Bei "0.0f" wird die Erzeugung der Wurzel ganz ausgelassen (default). </param>
		///<param name="frQuality"> Je h�her dieser Wert, desto besser die Qualit�t des Baumes, aber desto schlechter die Framerate. <para></para>
		/// Tipp: Ab 0.5f bei 4K-Monitor f�r das Auge kaum noch Unterschiede zu erkennen, daher darunter bleiben! <para>< / para>
		/// (0.0f = Grottenschlecht, 0.5f = normal (default), 1.0f = beste Qualit�t, aber nur f�r Hochleistungsgrafikkarten geeignet)</param>
		void Init(int iRandomSeed, float fAge, float frTimeOfYear = 0.25f, float fRootCutHeight = 0.0, float frQuality = 0.5f);

		///<summary> Finalisierung </summary> 
		void Fini();

		///<summary> Array mit den LoD-Unterplacements </summary> 
		CPlacement m_azpLoD[PLANTCHELIDONIUMMAJUS_LODS];

		///<summary> Array mit den LoD-Untergeometrien </summary> 
		CGeoBioChelidoniumMajus m_azgLoD[PLANTCHELIDONIUMMAJUS_LODS];

	protected: 

		///<summary> Erzeugungsstatus </summary> 
		EStatusConstruction m_eStatusConstruction = eStatusConstruction_Start;
	};

