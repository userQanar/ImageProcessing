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


class ImageProcessing
{
public:
	// Konstruktor
	ImageProcessing(const Image src);
	// Destruktor
	~ImageProcessing();

	// R�ckgabe des bearbeiteten Bildes
	Image &GetResult();

private:
	Image rawImage;
	Image procImage;
};