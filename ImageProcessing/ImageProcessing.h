/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageProcessing.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zur Bildverarbeitung - Template für Studierende
******************************************************************************/

#pragma once

#include "Image.h"
#include "Point.h"

class ImageProcessing
{
public:
	// Konstruktor
	ImageProcessing(const Image src);
	// Destruktor
	~ImageProcessing();

	// Rückgabe des bearbeiteten Bildes
	Image &GetResult();

	int n;
	int outliner = 0;
	bool local;
	bool quartet;
	int threshold;
	bool setLocal();
	bool setQuartet();
	int setOutliner();
	int setThreshold();

	bool inbounds(Point p, Image im);
	bool homogenous(int[], int th, int n, int outliner);
	bool notVisited(Point p, Image im);

	void RegionGrowing(int threshold, Point seed, bool local, bool quartet, int outliner);
	void RegionFractal(int th, Point seed);

private:
	Image rawImage;
	Image procImage;
};
