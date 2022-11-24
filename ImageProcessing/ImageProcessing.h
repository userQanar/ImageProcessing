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

	bool local;
	bool quartet;
	void setLocal();
	void setQuartet();

	void RegionGrowing(int threshold, Point seed, bool local, bool change);
	void RegionFractal(int th, Point seed);

private:
	Image rawImage;
	Image procImage;
};
