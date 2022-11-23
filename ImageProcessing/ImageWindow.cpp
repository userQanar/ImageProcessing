/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImageWindow.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse für die Benutzerschnittstelle (View und Controller)
******************************************************************************/

#include "ImageWindow.h"

#include <iostream>
#include <io.h>
#include <cstring>

#include <opencv2/highgui/highgui.hpp>

using namespace std;


ImageWindow::ImageWindow(Image &img) : image(img)
{
	filter    = 0;
	intensity = 1;
}
ImageWindow::~ImageWindow()
{
}


bool ImageWindow::ImreadDialog(string directory)
{
	vector<string> fileNames;
	size_t num = ListFiles(directory, fileNames);
	for (int i = 0; i < num; i++)
		cout << i + 1 << ": " << fileNames[i] << endl;

	unsigned int nr;
	cout << endl << "Geben Sie die Nummer des zu verarbeitenden Bildes ein: " << endl;
	cin >> nr;
	if (nr<1 || nr>fileNames.size())
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
	string filePath = directory + fileNames[nr - 1];

	image = cv::imread(filePath, CV_LOAD_IMAGE_COLOR);

	// Überprüfe eingelesene Daten
	if (!image.IsValid())
	{
		cout << "Die Datei konnte nicht geoeffnet werden!" << endl;
		return false;
	}
	return true;
}

void ImageWindow::intro() 
{
	cout << endl << "Geben Sie die Nummer des Wunschprogramms ein: ";
	cout << "0.Filtermaske  1.RegionGrowing  2.Fraktalbilder" << endl;
	cin >> mode;
	if (mode < 0 || mode > 2)
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
} 

void ImageWindow::chooseFilters()
{
	cout << endl << "Geben Sie die Nummer des Filters ein: ";
	cout << "0.naked  1.box  2.gauss  3.median " << endl;
	cin >> filter;

	if (filter < 0 || filter > 3)
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
	cout << endl << "Geben Sie die Filterintensitaet  ein: 1, 2, 3, 4, 5 " << endl;
	cin >> intensity;

	if (intensity < 1)
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
}

void ImageWindow::setThreshold()
{
	cout << endl << "Geben Sie den Threshold ein: " << endl;;
	cin >> threshold;
	if (threshold < 0 || threshold > 255)
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
}

void ImageWindow::doItAgain()
{
	cout << endl << "Noch einmal ? 1 Ja  0 Nein " << endl;;
	cin >> again;
	if (again)return;

	if (again != 1) {

		cout << endl << "Menu neustarten oder Exit ? 1 Menu  0 Exit " << endl;;
		cin >> restartMenu;

		if (!restartMenu) exit(0);
		else again = true;
	}
}


void ImageWindow::Imshow(string name)
{
	cv::namedWindow(name, CV_WINDOW_AUTOSIZE);
	cv::Mat &rawImage = image;
	cv::imshow(name, rawImage);
}

size_t ImageWindow::ListFiles(string directory, vector<string> &files)
{
	_finddata_t data;
	string dirJPG = directory + "/*.jpg";
	
	char* cDirJPG = new char[dirJPG.length() + 1];
	strcpy_s(cDirJPG, (dirJPG.length() + 1), dirJPG.c_str());

	intptr_t ft = _findfirst(cDirJPG, &data);
	if (ft != -1)
	{
		int res = 0;
		while (res != -1)
		{
			files.push_back(data.name);
			res = _findnext(ft, &data);
		}
		_findclose(ft);
	}
	return files.size();
}

// Callback für Mausklick
// Hinweis: Der 3. Parameter wird hier zwar nicht verwendet, aber von OpenCV erwartet
void CallbackFunc(int event, int x, int y, int, void *ptr)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		cv::Point *p = (cv::Point*)ptr;
		p->x = x;
		p->y = y;
	}
}

Point ImageWindow::GetSeed()
{
	cv::Point seed;
	seed.x = -1;

	cv::namedWindow("Saatpunkt setzen", CV_WINDOW_AUTOSIZE);
	cv::setMouseCallback("Saatpunkt setzen", CallbackFunc, &seed);
	cv::imshow("Saatpunkt setzen", (cv::Mat&)image);

	while (seed.x == -1)
	{
		cv::waitKey(100);
	}
	cv::destroyWindow("Saatpunkt setzen");

	Point s;
	s.X(seed.x);
	s.Y(seed.y);

	return s;
}

void ImageWindow::WaitKey()
{
	cvWaitKey(0);
}
