/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Image.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	16.10.2019
Beschreibung:		Klasse zur Representation und zur Bearbeitung von Bildern
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

#include <string>


/******************************************************************************
Beispiel zur Nutzung der Klasse "Image"

--> Einlesen eines Testbildes:
Image picture;
picture.Imread("testbild.jpg");

--> Pixel an der Stelle (5 / 3) auf den Wert 7 setzen:
picture.Set(5, 3, 7);

--> Wert des Pixels an Stelle (5 / 7) zurückgeben:
int value = picture.At(5, 7);
******************************************************************************/
class Image
{
public:
	// Konstruktoren
	Image();
	Image(cv::Mat src);
	Image(unsigned int rows, unsigned int cols);
	// Destruktor 
	~Image();

	// Lesen eines Bildes im JPEG-Format
	void Imread(std::string filename);

	// Setzen des Wertes des Pixels an der Stelle (x / y)
	void Set(unsigned int x, unsigned int y, int value);
	
	// Überlagern eines Bildes mit einem Maskenbild
	Image Imfusion(Image background, double alpha = 0.5);

	// Rückgabe des Grauwertes des Pixels an der Stelle (x / y)
	int At(unsigned int x, unsigned int y);
	
	// Rückgabe der Zahl der Zeilen eines Bildes vom Typ Image
	unsigned int Rows();
	
	// Rückgabe der Zahl der Spalten eines Bildes vom Typ Image
	unsigned int Cols();

	// Automatischer cast des Basis-OpenCV-Bildes
	operator cv::Mat &();

	// Zuweisung eines OpenCV-Bildes
	Image &operator=(const cv::Mat &src);

	// Validiert Daten
	bool IsValid();

	// Rückgabe des Bildes im OpenCV-Datenformat
	cv::Mat GetRawImage();

private:
	cv::Mat rawImage;
	cv::Mat procImage;
};
