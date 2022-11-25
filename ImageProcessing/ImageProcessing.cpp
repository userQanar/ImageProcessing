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

void ImageProcessing::setLocal()
{
	cout << endl << "Lokal oder Global ? 1. Lokal 0. Global : " << endl;;
	cin >> local;
}

void ImageProcessing::setQuartet() 
{
	cout << endl << "4er Nachbarschaft Eingabe 1, 8er Nachbarschaft Eingabe 0" << endl; // die hängen in der schwebe 
	cin >> quartet;
}

bool ImageProcessing::inbounds(Point p, Image im) 
{
	if (p.X() != 1 && p.X() < (im.Rows() - 1) && p.Y() != 1 && p.Y() < (im.Cols() - 1)) return true;
	return false;
}

bool ImageProcessing::homogenous(int o[], int th, int n) 
{
	if (n == 4) 
	{
		if (o[0] <= th && o[1] <= th && o[2] <= th && o[3] <= th) return true;
		return false;
	}
	else if (n == 8) 
	{
		if (o[0] <= th && o[1] <= th && o[2] <= th && o[3] <= th
			&& o[4] <= th && o[5] <= th && o[6] <= th && o[7] <= th) return true;
		return false;
	}
}

bool ImageProcessing::notVisited(Image im, Point next[], int i)
{
	if (im.At(next[i].X(), next[i].Y()) == 0) return true;
	return false;
}

void ImageProcessing::RegionGrowing(int threshold, Point seed, bool local, bool quartet) {// local -> build input 1-8 neighbours 0-3 outliner

	stack<Point>stack;
	Point currentSeed;
	Point next[8];
	int offset[8];
	const vector<int> x = { 0, 0, -1, +1, -1, +1, -1, +1 };
	const vector<int> y = { -1, +1, 0, 0, +1, +1, -1, -1 };

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255);
	stack.push(seed);

	while (!stack.empty()) 
	{
		currentSeed = stack.top();
		stack.pop();

		if (quartet) n = 4; else n = 8;
		
		for (int i = 0; i < n; i++)
		{
			next[i].X(currentSeed.X() + x[i]);
			next[i].Y(currentSeed.Y() + y[i]);
		}

		for (int i = 0; i < n; i++) {

			offset[i] = abs(rawImage.At(seed.X(), seed.Y()) - rawImage.At(next[i].X(), next[i].Y()));
		}

		for (int i = 0; i < n; i++) {

			if (inbounds(next[i], mask))
			{
				if (local)
				{
					if (homogenous(offset, threshold, n))
					{
						mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2* offset[i]));

						if (notVisited(mask, next, i )) 
						{
							stack.push(next[i]);
							mask.Set(next[i].X(), next[i].Y(), 1);
						}
					}
				}
				else//global
				{
					if (homogenous(offset, threshold, n))
					{						
						mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * offset[i]));

					}
					if (notVisited(mask, next, i)) 
					{						
						stack.push(next[i]);
						mask.Set(next[i].X(), next[i].Y(), 1);
					}
				}
			}
		}
	}
	procImage = mask;
}

void ImageProcessing::RegionFractal(int threshold, Point seed) {

	stack<Point>stack;
	Point currentSeed;
	Point next[4];
	int offset[4];
	const vector<int> x = { 0, 0, -1, +1, -1, +1, -1, +1 };
	const vector<int> y = { -1, +1, 0, 0, +1, +1, -1, -1 };

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255);
	stack.push(seed);

	while (!stack.empty()) 
	{
		currentSeed = stack.top();
		stack.pop();
		const auto rawAt = rawImage.At(currentSeed.Y(), currentSeed.X());

		for (int i = 0; i < 4; i++)
		{
			next[i].X(currentSeed.X() + x[i]);
			next[i].Y(currentSeed.Y() + y[i]);
		}

		for (int i = 0; i < 4; i++) 
		{ 
			offset[i] = abs(rawAt - rawImage.At(next[i].X(), next[i].Y()));
			//if (offset[i] < 40 && offset[i] > 10) check[i] - 10;
		}

		for (int i = 0; i < 4; i++) 
		{
			if (homogenous(offset, threshold, 4))
			{
				mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (3 * offset[i]));
			}
			if (inbounds(next[i], mask))
			{
				if (notVisited(mask, next, i))
				{
					stack.push(next[i]);
					mask.Set(next[i].X(), next[i].Y(), 1);
				}
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