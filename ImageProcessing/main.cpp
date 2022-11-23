/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				main.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Student:			Robin Hill
Letzte Änderung:	23.11.2022
Beschreibung:		Hauptprogramm zu Versuch 2 - Template für Studierende
******************************************************************************/

#include <string>
#include <iostream>
#include <stack>

#include "Image.h"
#include "ImageProcessing.h"
#include "ImagePreProcessing.h"
#include "ImageWindow.h"

int main()
{
	// Einlesen und Anzeigen eines Testbildes
	Image rawImage;
	ImageWindow testImageWindow(rawImage);
	std::string directory = "./Images/";
	testImageWindow.ImreadDialog(directory);
	//testImageWindow.Imshow("Raw Image");
		
	// Konvertierung in Grauwertbild
	Image grayImage;
	ImageWindow grayImageWindow(grayImage);
	ImagePreProcessing gray(rawImage);
	grayImage = gray.Convert2Gray();
	//grayImageWindow.Imshow("Gray Image");


	//0.Filtermaske  1.RegionGrowing  2.Fraktalbilder
	grayImageWindow.intro();


while (grayImageWindow.again) {

//*************************Filtermaske********************************/  
	if(grayImageWindow.restartMenu){
		grayImageWindow.intro();
	}

	int mode = grayImageWindow.mode;

	if (mode == 0) {

		grayImageWindow.chooseFilters();

		//0 naked, 1 Box, 2 Gauss, 3 Median
		int chooseFilter = grayImageWindow.filter;

		// filterIntensity (2n)-1 
		int magnitude = grayImageWindow.intensity;

		ImagePreProcessing  sobel(grayImage);
		Image sobelImage = sobel.SobelFilter(chooseFilter, magnitude);
		ImageWindow sobelImageWindow(sobelImage);
		sobelImageWindow.Imshow("Sobelfilter Image");

		ImagePreProcessing filter(grayImage);
		grayImageWindow.Imshow("Gray Image");

		if (chooseFilter == 1) {
			Image boxImage = filter.BoxFilter(magnitude);
			ImageWindow boxImageWindow(boxImage);
			boxImageWindow.Imshow("Boxfilter Image");
		}

		if (chooseFilter == 2) {
			Image gaussImage = filter.GaussFilter(magnitude);
			ImageWindow gaussImageWindow(gaussImage);
			gaussImageWindow.Imshow("Gaußfilter Image");
		}

		if (chooseFilter == 3) {
			Image medianImage = filter.MedianFilter(magnitude);
			ImageWindow medianImageWindow(medianImage);
			medianImageWindow.Imshow("Medanfilter Image");
		}
	}
//*************************RegionGrowing********************************/  

	else if (mode == 1) {

		ImageProcessing processing(grayImage);

		processing.setLocal();
		grayImageWindow.setThreshold();
		bool local = processing.local;
		int threshold = grayImageWindow.threshold;

		Point seed = grayImageWindow.GetSeed();

		processing.RegionGrowing(threshold, seed, local);
		Image segImage;
		ImageWindow segImageWindow(segImage);

		segImage = processing.GetResult();
		segImage = segImage.Imfusion(grayImage, 0.5);
		segImageWindow.Imshow("Segmented Image");

	}
//*************************Fraktalbilder********************************/  

	else if (mode == 2) {

		grayImageWindow.setThreshold();
		int threshold = grayImageWindow.threshold;

		Point seed;
		seed.X(5); seed.Y(5);//Doesnt matter same result

		ImageProcessing proeccesing(grayImage);

		proeccesing.RegionFractal(threshold, seed);
		Image segImage;
		ImageWindow segImageWindow(segImage);
		segImage = proeccesing.GetResult();
		segImageWindow.Imshow("Segmented Image");

	}
	ImageWindow::WaitKey();
	grayImageWindow.doItAgain();
}
	return 0;
}
