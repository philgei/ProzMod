#include "CTropicalIsland.h"

CTropicalIsland::CTropicalIsland()
{
}

CTropicalIsland::~CTropicalIsland()
{
}

void CTropicalIsland::init()
{



	//Materials_____________________________________________________
	m_materialWater.LoadPreset("Water");
	m_materialSand.LoadPreset("Sand");
	m_materialGras.LoadPreset("RockMossy");
	m_materialSteine.LoadPreset("Concrete");


	//Cuts_______________________________________________________

		//Meeresspiegel
	{
		m_cutUnderSea.SetHeightLimits(-F_MAX, 0.0f);
		//m_cutUnderSea.SetFlattenLowerOn();
		//m_cutUnderSea.SetFlattenUpperOn();
		//m_cutUnderSea.SetFlattenSmartOn();
	}

	//Sand
	{

		m_cutStrand.SetHeightLimits(0.0f, 5.0f);
		//m_cutStrand.SetFlattenLowerOn();
		//m_cutStrand.SetFlattenUpperOn();
		//m_cutStrand.SetFlattenSmartOn();

	}
	//Gras
	{

		m_cutGrasslands.SetHeightLimits(5.0f, 30.0f);
		//m_cutGrasslands.SetFlattenLowerOn();
		//m_cutGrasslands.SetFlattenUpperOn();
		//m_cutGrasslands.SetFlattenSmartOn();

	}
	//Steine
	{

		m_cutRocks.SetHeightLimits(30.0f, F_MAX);
		//m_cutRocks.SetFlattenLowerOn();
		//m_cutRocks.SetFlattenUpperOn();
		//m_cutRocks.SetFlattenSmartOn();

	}

	//Schnitte ausführen

	//strand
	m_TerrainStrand.AddCut(&m_cutUnderSea);
	m_TerrainStrand.AddCut(&m_cutGrasslands);
	m_TerrainStrand.AddCut(&m_cutRocks);

	//gras
	m_TerrainGras.AddCut(&m_cutUnderSea);
	m_TerrainGras.AddCut(&m_cutStrand);
	m_TerrainGras.AddCut(&m_cutRocks);

	//steine
	m_TerrainSteine.AddCut(&m_cutUnderSea);
	m_TerrainSteine.AddCut(&m_cutStrand);
	m_TerrainSteine.AddCut(&m_cutGrasslands);



//Perlin_____________________________________________________________

	CPerlin* perlinBase = new CPerlin(
		1337, // Zufallsseed
		3.0f, // Amplitude
		12, // Oktaven
		0.5f, // Persistenz
		5.0f, // Frequenz
		0.0f, // X-Verschiebung
		0.0f, // Y-Verschiebung
		ePerlinInterpol_Standard, // Interpolationsart 
		false); // Repetivität

//Blobs____________________________________________________________
	CBlob* blobElevator = new CBlob(
		0.5f, 0.5f,// Mittelpunkt des Blobs (u und v)
		0.51f, 0.51f,// Radius des Blobs (u und v)
		-0.1f,// Höhe des Blobs
		eBlobShapeGround_Rect,
		eBlobShapeSide_All,
		nullptr);

	CBlob* blobLandMass = new CBlob(
		0.5f, 0.5f, // Mittelpunkt des Blobs (u und v)
		0.5f, 0.5f, // Radius des Blobs (u und v)
		50.0f, // Höhe des Blobs
		eBlobShapeGround_Radial, // Grundflächentopologie
		eBlobShapeSide_Dome, // Höhenverlaufstopologie
		perlinBase); // Optinaler Pointer auf eine 
		// Perlin-Noise-Instanz (kommt später)

	CBlob* blobHill = new CBlob(
		0.3f, 0.6f, // Mittelpunkt des Blobs (u und v)
		0.2f, 0.3f, // Radius des Blobs (u und v)
		150.0f, // Höhe des Blobs
		eBlobShapeGround_Radial, // Grundflächentopologie
		eBlobShapeSide_Hill, // Höhenverlaufstopologie
		nullptr); // Optinaler Pointer auf eine 
		// Perlin-Noise-Instanz (kommt später) 

	//Blobs hinzufügen
	m_TerrainOri.AddBlob(blobElevator);
	m_TerrainOri.AddBlob(blobLandMass);
	m_TerrainOri.AddBlob(blobHill);




// Terrains erzeugen_______________________________________

	m_TerrainOri.CreateField(
		2000, 2000, // Ein Quadratkilometer Terrain
		1000, 1000, // 2000 auf 2000 Vertices
		0.0f, 0.0f, // Die UV-Textur beginnt bei (0,0) …
		50.0f, 50.0f);// … und geht bis (1,1)


	m_TerrainStrand.InitFromOther(m_TerrainOri, &m_materialSand);
	m_TerrainGras.InitFromOther(m_TerrainOri, &m_materialGras);
	m_TerrainSteine.InitFromOther(m_TerrainOri, &m_materialSteine);


	m_TerrainWater.Init(
		70000, 70000, // Das Meer ist groß (70 *70 qm)
		&m_materialWater, // Ein bewegtes Wassermaterial mit Wellen
		10, 10, // Brauchen nur wenige Polygone (hier 100)
		0.0f, 0.0f, // Eine UV-Verschiebung brauchen wir nicht
		900.0f, // Aber die Textur soll sich 500 Mal … 
		900.0f); // …in jeder Richtung wiederholen


//Geos anhängen_________________________________________________


	AddGeo(&m_TerrainWater);
	AddGeo(&m_TerrainStrand);
	AddGeo(&m_TerrainGras);
	AddGeo(&m_TerrainSteine);


//Kollisionscontainer_________________________________________
	m_gsTerrain.Add(&m_TerrainStrand);
}