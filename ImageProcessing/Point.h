/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Point.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	09.12.2019
Beschreibung:		Klasse zum Umgang mit Bildpunkten ("Pixeln")
******************************************************************************/

#pragma once

// Deaktivierung ausgewählter Warnungen für Codeanalyse innerhalb OpenCv-Code
// vgl. https://docs.microsoft.com/de-de/cpp/preprocessor/warning?view=vs-2019
#pragma warning(push)
#pragma warning(disable: 6011 6201 6294 6297 6385 26439 26451  26495)
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#pragma warning(pop)


/******************************************************************************
Beispiel zur Nutzung der Klasse "Point"

--> Punkt "pixel" mit den Koordinaten (5 / 3) anlegen:
Point pixel;
pixel.X(5);
pixel.Y(3);

--> X- und Y-Koordinaten des Punktes "pixel" zurückgeben:
unsigned int x = pixel.X();
unsigned int y = pixel.Y();
******************************************************************************/
class Point
{
public:
	Point();
	~Point();

	// Setzen der x-Koordinate
	void X(unsigned int xCoordinate);
	
	// Setzen der y-Koordinate
	void Y(unsigned int yCoordinate);
	
	// Rückgabe der x-Koordinate
	unsigned int X();

	// Rückgabe der y-Koordinate
	unsigned int Y();

private:
	cv::Point point;
};
