/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImagePreProcessing.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	16.10.2019
Beschreibung:		Klasse zur elementaren Bildverarbeitung und -konvertierung
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

#include <vector>

#include "Image.h"


/******************************************************************************
Beispiel zur Nutzung der Klasse "ImagePreProcessing"

--> Grauwertkonvertierung eines Bildes "picture" vom Typ Image:
ImagePreProcessing gray(picture);
Image grayImage = gray.Convert2Gray();

--> Mittelwertfilterung eines Bildes "picture" vom Typ Image mit einer Filtermaske der Kantenlänge 3:
ImagePreProcessing filter(picture);
Image filteredImage = filter.BoxFilter(3);
******************************************************************************/
class ImagePreProcessing
{
public:
	// Konstruktor
	ImagePreProcessing(Image src);
	// Destruktor 
	~ImagePreProcessing();

	// Konvertieren eines RGB-Bildes vom Typ Image in ein Graustufenbild
	Image Convert2Gray();

	// Schwellwertfilterung eines Bildes vom Typ Image
	// Werte >= val1 werden zu val2 gesetzt
	Image Threshold(int val1, int val2);

	// Rückgabe der Histogrammverteilung eines Bildes vom Typ Image 
	std::vector<float> GetHistogram(int histSize);

	// Mittelwertfilterung eines Bildes vom Typ Image
	// ksize: Kantenlänge der Filtermaske
	Image BoxFilter(unsigned char ksize);

	// Gauss-Filterung eines Bildes vom Typ Image
	// ksize: Kantenlänge der Filtermaske
	Image GaussFilter(unsigned char ksize);

	// Medianfilterung eines Bildes vom Typ Image
	// ksize: Kantenlänge der Filtermaske
	Image MedianFilter(unsigned char ksize);

	Image SobelFilter(int chooseFilter, unsigned char ksize);

private:
	cv::Mat rawImage;
	cv::Mat procImage;
	cv::Mat dx;
	cv::Mat dy;
};
