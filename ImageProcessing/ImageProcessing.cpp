/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageProcessing.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zur Bildverarbeitung - Template für Studierende
******************************************************************************/

#include "ImageProcessing.h"


#include "ImagePreProcessing.h"

using namespace std;


ImageProcessing::ImageProcessing(const Image src)
{
	rawImage = src;
	Image sink(rawImage.Rows(), rawImage.Cols());
	procImage = sink;
}

ImageProcessing::~ImageProcessing()
{
}

Image &ImageProcessing::GetResult()
{
	return procImage;
}
