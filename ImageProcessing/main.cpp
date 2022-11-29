/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				main.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Student:			Robin Hill
Letzte Änderung:	28.11.2022
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
	Image grayImageSave;
	grayImageSave = grayImage;
	//grayImageWindow.Imshow("Gray Image");


	//0.Filtermaske  1.RegionGrowing  2.Fraktalbilder
	grayImageWindow.intro();

	while  (grayImageWindow.again) {

		if (grayImageWindow.restartMenu)
		{
			grayImageWindow.intro();
			grayImageWindow.restartMenu == false;
		}

		int mode = grayImageWindow.mode;

//*************************Filtermaske********************************/  

		if (mode == 0) {

			grayImageWindow.chooseFilters();

			//0 naked, 1 Box, 2 Gauss, 3 Median
			int yourFilter = grayImageWindow.filter;

			// filterIntensity (2n)-1 
			int magnitude = grayImageWindow.intensity;

			ImagePreProcessing filter(grayImage);
			grayImageWindow.Imshow("Gray Image");

			Image boxImage; Image gaussImage; Image medianImage;

			if (yourFilter == 0) {

				ImagePreProcessing sobel(grayImage);
				Image sobelImage = sobel.SobelFilter(yourFilter, magnitude);
				ImageWindow sobelImageWindow(sobelImage);
				sobelImageWindow.Imshow("Sobelfilter Image");

				ImageWindow::WaitKey();
				grayImage = filter.wantToSave(grayImage, grayImageSave);
				if (filter.save) {
					mode = grayImageWindow.intro();
					continue;
				}
			}
			else if (yourFilter == 1) {

				Image boxImage = filter.BoxFilter(magnitude);
				ImageWindow boxImageWindow(boxImage);
				boxImageWindow.Imshow("Boxfilter Image");

				ImageWindow::WaitKey();
				grayImage = filter.wantToSave(grayImage, boxImage);
				if (filter.save) {
					mode = grayImageWindow.intro();
					continue;
				}
			}
			else if (yourFilter == 2) {

				Image gaussImage = filter.GaussFilter(magnitude);
				ImageWindow gaussImageWindow(gaussImage);
				gaussImageWindow.Imshow("Gaußfilter Image");

				ImageWindow::WaitKey();
				grayImage = filter.wantToSave(grayImage, gaussImage);
				if (filter.save) {
					mode = grayImageWindow.intro();
					continue;
				}
			}
			else if (yourFilter == 3) {

				Image medianImage = filter.MedianFilter(magnitude);
				ImageWindow medianImageWindow(medianImage);
				medianImageWindow.Imshow("Medanfilter Image");

				ImageWindow::WaitKey();
				grayImage = filter.wantToSave(grayImage, medianImage);
				if (filter.save) {
					mode = grayImageWindow.intro();				
					continue;
				}
			}
		}
//*************************RegionGrowing********************************/  

		else if (mode == 1) {

			ImageProcessing processing(grayImage);
			bool local    = processing.setLocal();
			bool quartet  = processing.setQuartet();
			int outliner  = processing.setOutliner();
			int threshold = processing.setThreshold();
			Point seed = grayImageWindow.GetSeed();

			processing.RegionGrowing(threshold, seed, local, quartet, outliner);
			
			Image segImage;
			ImageWindow segImageWindow(segImage);
			segImage = processing.GetResult();
			segImage = segImage.Imfusion(grayImage, 0.5);
			segImageWindow.Imshow("Segmented Image");

		}
//*************************Fraktalbilder********************************/  

		else if (mode == 2) {

			ImageProcessing processing(grayImage);
			int threshold = processing.setThreshold();
			Point seed; seed.X(5); seed.Y(5);//global

			processing.RegionFractal(threshold, seed);

			Image segImage;
			ImageWindow segImageWindow(segImage);
			segImage = processing.GetResult();
			segImageWindow.Imshow("Segmented Image");

		}
		ImageWindow::WaitKey();
		grayImageWindow.doItAgain();
	}
	return 0;
}
