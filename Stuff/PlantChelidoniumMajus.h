#pragma once
#include "Vektoria\Root.h"
#include "GeoBioChelidoniumMajus.h"

//----------------------------------------------------------------------------
// CGeoBioChelidoniumMajus 
// 
// Erklärung: Klasse, um prozedural realistische Schöllkraut-Placements 
//	      mit optimalen LODs und Untergeometrien zu erzeugen
// Autor    : Prof. Dr. Tobias Breiner
// Ort      : Pfungstadt
// Zeit     : seit Nov. 2019 (mit seitdem ständigen Verbesserungs-Updates) 
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

		///<summary> Erzeugt das L-System für die Pflanzengeometrie. <para></para>
		/// Achtung Nr. 1! Nach "Iterate" müssen eine oder mehere "Init"-Methoden verschiedener Objektinstanzen aufgerufen werden, um die Geometrie zu erzeugen. 
		/// Achtung Nr. 2! Nach allen "Init"-Methodenaufrufen sollte "Deiterate" aufgerufen werden, um das L-System wieder zu zerstören und den Speicher freizugeben. </summary> 
		///<param name="iRandomSeed"> Anfang der Pseudozufallsreihenfolge für den Aufbau des Baumes <para></para>
		/// (bei gleichem iRandomSeed wird der gleiche Baum erzeugt) </param>
		///<param name="fAge"> Alter der Pflanze in Jahren (Je älter, desto größer und komplexer). </param>
		///<param name="frTimeOfYear"> Fraktionale Jahreszeit (Frühlingstagundnachtgleiche = 0.0f .. Sommersonnenwende  = 0.25f ... Herbsttagundnachtgleiche = 0.5f ... Wintersonnenwende = 0.75f) <para></para>
		/// Wichtig für Farbe und Aussehen der Blätter. </param>
		///<param name="fRootCutHeight"> Unter dieser Höhe werden die Wurzeln nicht mehr erzeugt. <para></para>
		/// Bei "0.0f" wird die Erzeugung der Wurzel ganz ausgelassen (default). </param>
		///<param name="frQuality"> Je höher dieser Wert, desto besser die Qualität des Baumes, aber desto schlechter die Framerate. <para></para>
		/// Tipp: Ab 0.5f bei 4K-Monitor für das Auge kaum noch Unterschiede zu erkennen, daher darunter bleiben! <para>< / para>
		/// (0.0f = Grottenschlecht, 0.5f = normal (default), 1.0f = beste Qualität, aber nur für Hochleistungsgrafikkarten geeignet)</param>
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

