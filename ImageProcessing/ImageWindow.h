/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageWindow.h
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte �nderung:	03.09.2018
Beschreibung:		Klasse f�r die Benutzerschnittstelle (View und Controller)
******************************************************************************/

#pragma once

#include <string>
#include <vector>

#include "Image.h"
#include "Point.h"


/******************************************************************************
Beispiel zur Nutzung der Klasse "ImageWindow"

--> Einlesen Darstellen eines Testbildes �ber Dialog:
Image picture;
ImageWindow pictureWindow(picture);
pictureWindow.ImreadDialog("./foo/bar/");
pictureWindow.Imshow("Testbild");
******************************************************************************/
class ImageWindow
{
public:
	ImageWindow(Image &image);
	~ImageWindow();

	// Lesen eines Bildes im JPEG-Format mit Dialog
	// Parameter: Verzeichnis, R�ckgabewert ist "wahr" bei Erfolg
	bool ImreadDialog(std::string directory);

	int filter;
	int intensity;
	int mode;

	bool again = true;
	bool restartMenu = false;

	void intro();
	void chooseFilters();
	void doItAgain();
	
	// Anzeigen des Fensters mit Bild vom Typ Image
	// Parameter "name": Beschriftung des Fensters
	void Imshow(std::string name);

	// Setzen eines Punktes mit der Maus im letzten aktiven Fenster
	Point GetSeed();

	// Auf Tastendruck warten, anschlie�end alle ge�ffneten Grafikfenster wieder schlie�en
	static void WaitKey();

private:
	// Speichert Referenz auf das Bild
	Image &image;
	
	// Listet die Namen aller JPEG-Dateien (*.jpg) des Verzeichnisses "directory" auf und gibt deren Anzahl zur�ck
	size_t ListFiles(std::string directory, std::vector<std::string> &fileNames);
};
