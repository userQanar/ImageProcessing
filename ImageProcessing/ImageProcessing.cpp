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
#include <stack>
#include <iostream>

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

Image& ImageProcessing::GetResult()
{
	return procImage;
}

bool ImageProcessing::setLocal()
{
	cout << endl << "Lokal oder Global ? 1. Lokal 0. Global : " << endl;;
	cin >> local;
	return local;
}

bool ImageProcessing::setQuartet() 
{
	cout << endl << "1 Eingeben zu 4er Nachbarschaft , 0 Eingeben zu 8er Nachbarschaft" << endl;
	cin >> quartet;
	return quartet;
}

int ImageProcessing::setOutliner() 
{
	cout << endl << "Anzahl Ausreisser eingeben 0-3" << endl;
	cin >> outliner;
	return outliner;
}

int ImageProcessing::setThreshold()
{
	cout << endl << "Geben Sie den Threshold ein: " << endl;;
	cin >> threshold;
	if (threshold < 0 || threshold > 255)
	{
		cout << "Ungueltige Eingabe!" << endl;
		exit(0);
	}
	return threshold;
}

bool ImageProcessing::inbounds(Point p, Image im) 
{
	if (p.X() != 1 && p.X() < (im.Rows() - 1) && p.Y() != 1 && p.Y() < (im.Cols() - 1)) return true;
		return false;
}

bool ImageProcessing::homogenous(int o[], int th, int n, int outliner)
{
	int count = 0;

		for (int i = 0; i < n; i++) {
			if (o[i] <= th) ++count;
		}
		if (count >= (n - outliner)) return true;
			return false;
}

bool ImageProcessing::notVisited(Point p, Image im)
{
	if (im.At(p.X(), p.Y()) == 0) return true;
		return false;
}

void ImageProcessing::RegionGrowing(int threshold, Point seed, bool local, bool quartet, int outliner) 
{
	stack<Point>stack;
	Point currentSeed;
	Point next[8];
	int offset[8];
	if (quartet) n = 4; else n = 8;
	const vector<int> x = { 0, 0, -1, +1, -1, +1, -1, +1 };
	const vector<int> y = { -1, +1, 0, 0, +1, +1, -1, -1 };

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255);
	stack.push(seed);

	while (!stack.empty()) {

		currentSeed = stack.top();
		stack.pop();

		for (int i = 0; i < n; i++)	{
			next[i].X(currentSeed.X() + x[i]);
			next[i].Y(currentSeed.Y() + y[i]);
		}

		for (int i = 0; i < n; i++) {
			offset[i] = abs(rawImage.At(seed.X(), seed.Y()) - rawImage.At(next[i].X(), next[i].Y()));
		}

		for (int i = 0; i < n; i++) {			
					
			if (local) {

				if (homogenous(offset, threshold, n, outliner)) {
					mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2* offset[i]));

					if (inbounds(next[i], mask) && notVisited(next[i], mask)) {
						stack.push(next[i]);
						mask.Set(next[i].X(), next[i].Y(), 1);
					}
				}
			}
			else {//global	

				if (homogenous(offset, threshold, n, outliner))										
					mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * offset[i]));
			
				if (inbounds(next[i], mask) && notVisited(next[i], mask)) {
					stack.push(next[i]);
					mask.Set(next[i].X(), next[i].Y(), 1);
				}
			}		
		}
	}
	procImage = mask;
}

void ImageProcessing::RegionFractal(int threshold, Point seed) 
{
	stack<Point>stack;
	Point currentSeed;
	Point next[4];
	int offset[4];
	const vector<int> x = { 0, 0, -1, +1, -1, +1, -1, +1 };
	const vector<int> y = { -1, +1, 0, 0, +1, +1, -1, -1 };

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255);
	stack.push(seed);

	while (!stack.empty()) {

		currentSeed = stack.top();
		stack.pop();
		const auto rawAt = rawImage.At(currentSeed.Y(), currentSeed.X());

		for (int i = 0; i < 4; i++)	{
			next[i].X(currentSeed.X() + x[i]);
			next[i].Y(currentSeed.Y() + y[i]);
		}

		for (int i = 0; i < 4; i++) { 
			offset[i] = abs(rawAt - rawImage.At(next[i].X(), next[i].Y()));
			//if (offset[i] < 40 && offset[i] > 10) check[i] - 10;
		}

		for (int i = 0; i < 4; i++) {
			
			if (homogenous(offset, threshold, 4, outliner)) 
				mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (3 * offset[i]));	

			if (!inbounds(next[i], mask)) 
				continue;

			if (notVisited(next[i], mask)) {
				stack.push(next[i]);
				mask.Set(next[i].X(), next[i].Y(), 1);
			}		
		}
	}
	procImage = mask;
}
/* savegame
		for (int i = 0; i < 4; i++)
		{
		    //int test1 = rawAt; int test2 = rawImage.At(next[i].X(), next[i].Y());
			check[i] = abs(rawAt - rawImage.At(next[i].X(), next[i].Y()));
			//std::cout << check[i] << ", ";
					//if (check[i] < 40 && check[i] > 10) check[i] - 10;
		}
			//std::cout << endl;
*/