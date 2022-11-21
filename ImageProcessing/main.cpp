/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				main.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	26.08.2019
Beschreibung:		Hauptprogramm zu Versuch 2 - Template für Studierende
******************************************************************************/

#include <string>
#include <iostream>

#include "Image.h"
#include "ImagePreProcessing.h"
#include "ImageWindow.h"


#define VORBEREITUNG

int main()
{
	// Einlesen und Anzeigen eines Testbildes
	Image rawImage;
	ImageWindow testImageWindow(rawImage);
	std::string directory = "./Images/";
	testImageWindow.ImreadDialog(directory);
	testImageWindow.chooseFilters();
	//testImageWindow.Imshow("Raw Image");
		
	// Konvertierung in Grauwertbild
	Image grayImage;
	ImageWindow grayImageWindow(grayImage);
	ImagePreProcessing gray(rawImage);
	grayImage = gray.Convert2Gray();
	grayImageWindow.Imshow("Gray Image");


	
#ifdef VORBEREITUNG
	// Vorbereitungsaufgaben

	//0 naked, 1 Box, 2 Gauss, 3 Median
	int chooseFilter = testImageWindow.filter;

	// filterIntensity (2n)-1 
	int x = testImageWindow.intensity;

	ImagePreProcessing  sobel(grayImage);
	Image sobelImage =  sobel.SobelFilter(chooseFilter, x);
	ImageWindow sobelImageWindow(sobelImage);
	sobelImageWindow.Imshow("Sobelfilter Image");

	ImagePreProcessing filter(grayImage);

	if (chooseFilter == 1) {
		Image boxImage = filter.BoxFilter(x);
		ImageWindow boxImageWindow(boxImage);
		boxImageWindow.Imshow("Boxfilter Image");
	}

	if (chooseFilter == 2) {
		Image gaussImage = filter.GaussFilter(x);
		ImageWindow gaussImageWindow(gaussImage);
		gaussImageWindow.Imshow("Gaußfilter Image");
	}

	if (chooseFilter == 3) {
		Image medianImage = filter.MedianFilter(x);
		ImageWindow medianImageWindow(medianImage);
		medianImageWindow.Imshow("Medanfilter Image");
	}

#else
	// Laboraufgaben
	

#endif // VORBEREITUNG (zu #define VORBEREITUNG zugehöriges #endif)

	// Auf Tastendruck warten, bevor alle geöffneten Grafikfenster wieder geschlossen werden
	ImageWindow::WaitKey();

	return 0;
}
