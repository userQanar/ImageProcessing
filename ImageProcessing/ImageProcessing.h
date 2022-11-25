/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageProcessing.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Klasse zur Bildverarbeitung - Template f�r Studierende
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

	// R�ckgabe des bearbeiteten Bildes
	Image &GetResult();

	int n;
	bool local;
	bool quartet;
	void setLocal();
	void setQuartet();
	bool inbounds(Point p, Image im);
	bool homogenous(int[], int th, int n);
	bool notVisited(Image im, Point next[], int i);

	void RegionGrowing(int threshold, Point seed, bool local, bool change);
	void RegionFractal(int th, Point seed);

private:
	Image rawImage;
	Image procImage;
};
