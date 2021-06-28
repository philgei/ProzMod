//Die Maße des Boots lassen sich in alle Dimensionen anpassen.
//Ausßerdem ist es möglich, die "Rundung" des Boots vorne einzustellen
//Ich habe außerdem keine möglichkeit gefunden, in Vektoria ein Modell zu Spiegeln.
//Desshalb hab das Boot mehrere geometrien, welche im code gespiegelt werden und die Normalen geflipped werden
//Wenn ich noch dazu komme, werde ich im auch noch eine anpassbare Wandstärke geben, allerdings muss ich jetzt erst mal mein Seminararbeit machen :) 
//Genauso wie Sitzflächen



//Hiermit erlaube ich die Verwendung meines Codes für nichtkommerzielle Projekte, insbesondre für
//zukünftige studentische Projektarbeiten oder im Rahmen der akademischen Lehre bzw.Forschung.
//Mein Name muss bei Verwendung nicht als Urheber genannt werden
//
//Philipp Geirhos
#include "CCustomBezierBoat.h"

CCustomBezierBoat::CCustomBezierBoat(float lenght, float width, float height, float bugRoundness)
{
	//Das Boot besteht aus 4 Parts
	stepWidth = lenght / 4.f;
	//Der Schwung am Bug soll schön smooth sein
	bugSchuwng = (stepWidth - (stepWidth * (1 - bugRoundness))) / 4.0f;
	//Breite
	halfWidth = width / 2.0f;
	//Höhe
	m_height = height;
}

CCustomBezierBoat::~CCustomBezierBoat()
{
}

void CCustomBezierBoat::Init()
{
	//Holz-Material
	CMaterial* pzm = new CMaterial();
	pzm->LoadPreset("WoodPlanksBankirai");
	//Geometrie mit Bezier Patches erzeugen (MIrrow Modifier an der X Achse)
	setBaseGeoWithWithMirrow(false, m_GeoRight, pzm);
	setBaseGeoWithWithMirrow(true, m_GeoLeft, pzm);
	//Geometrie initialisieren
	m_GeoRight.Init();
	m_GeoLeft.Init();


	AddGeo(&m_GeoRight);
	AddGeo(&m_GeoLeft);
}

void CCustomBezierBoat::setBaseGeoWithWithMirrow(bool mirrow, CGeoBezierTable& geo, CMaterial* mat)
{
	CHVector aav[4][4];
	//Bug_______________________________________________________________
	float mirrowX = mirrow == true ? -1.0f : 1.0f;

	aav[0][3] = CHVector(mirrowX * 0, 0.0f, (stepWidth * 1), 1.0f);
	aav[1][3] = CHVector(mirrowX * 0, -m_height * 0.56f, (stepWidth * 1) + bugSchuwng * 2, 1.0f);
	aav[2][3] = CHVector(mirrowX * 0, -m_height, (stepWidth * 1) + bugSchuwng * 3, 1.0f);
	aav[3][3] = CHVector(mirrowX * 0, -m_height, (stepWidth * 1) + bugSchuwng * 4, 1.0f);
	//Mittlerer Teil_________________________________________________________________
	size_t  arrayCounter = 2;
	for (size_t i = 2; i <= 4; i++)
	{
		aav[0][arrayCounter] = CHVector(mirrowX * halfWidth, 0.0f, stepWidth * i, 1.0f);
		aav[1][arrayCounter] = CHVector(mirrowX * halfWidth, -m_height * 0.56f, stepWidth * i, 1.0f);
		aav[2][arrayCounter] = CHVector(mirrowX * halfWidth * 0.56f, -m_height, stepWidth * i, 1.0f);
		aav[3][arrayCounter] = CHVector(mirrowX * 0.0f, -m_height, stepWidth * i, 1.0f);
		arrayCounter--;
	}
	geo.AddPatch(aav, 20, 20);


	//Heck_____________________________________________________________________
	aav[0][0] = CHVector(mirrowX * 0.0f, 0.0f, stepWidth * 4);
	aav[1][0] = CHVector(mirrowX * 0.0f, -m_height * 0.56f, stepWidth * 4);
	aav[2][0] = CHVector(mirrowX * 0.0f, -m_height, stepWidth * 4);
	aav[3][0] = CHVector(mirrowX * 0.0f, -m_height, stepWidth * 4);

	arrayCounter = 2;
	for (size_t i = 1; i <= 3; i++)
	{
		aav[0][i] = CHVector(mirrowX * halfWidth, 0.0f, stepWidth * 4);
		aav[1][i] = CHVector(mirrowX * halfWidth, -m_height * 0.56f, stepWidth * 4);
		aav[2][i] = CHVector(mirrowX * halfWidth * 0.56f, -m_height, stepWidth * 4);
		aav[3][i] = CHVector(mirrowX * 0.0f, -m_height, stepWidth * 4);
	}

	geo.AddPatch(aav, 20, 20);


////Sitz
//
//	aav[0][0] = CHVector(-1.5f, 0, 2.4);
//	aav[1][0] = CHVector(-1.5f, 0, 2.4f);
//	aav[2][0] = CHVector(-0.84f, 0, 2.4f);
//	aav[3][0] = CHVector(0.0f, 0, 2.4f);
//
//	aav[0][1] = CHVector(-1.75f, 0, 1.875f);
//	aav[1][1] = CHVector(-1.75f, 0, 1.875f);
//	aav[2][1] = CHVector(-0.98f, 0, 1.875f);
//	aav[3][1] = CHVector(0.0f, 0, 1.875f);
//
//	aav[0][2] = CHVector(-2.0f, 0, 1.35f);
//	aav[1][2] = CHVector(-2.0f, 0, 1.35f);
//	aav[2][2] = CHVector(-1.12f, 0, 1.35f);
//	aav[3][2] = CHVector(0.0f, 0, 1.35f);
//
//	aav[0][3] = CHVector(-2.0f, 0, 0.9f);
//	aav[1][3] = CHVector(-2.0f, 0, 0.9f);
//	aav[2][3] = CHVector(-1.12f, 0, 0.9f);
//	aav[3][3] = CHVector(0.0f, 0, 0.9f);

	//geo.AddPatch(aav, 20, 20);
	geo.SetMaterial(mat);

	//Wenn die aufgebaute Geso gespielelt wurde, dann müssen noch ihre Normals gefliped werden
	if (mirrow) geo.Flip();
}
