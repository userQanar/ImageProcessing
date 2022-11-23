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
//#include <iostream>

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

Image &ImageProcessing::GetResult()
{
	return procImage;
}

void ImageProcessing::RegionGrowing(int th, Point seed) {

	stack<Point>stack;
	Point currentSeed;
	Point next[4];

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(),255);
	stack.push(seed);
	int check[4];

	while (!stack.empty()) {
		
		currentSeed = stack.top();
		stack.pop();

		next[0].X(currentSeed.X());
		next[0].Y(currentSeed.Y() - 1);
		  
		next[1].X(currentSeed.X());
		next[1].Y(currentSeed.Y() + 1);
		  
		next[2].X(currentSeed.X() - 1);
		next[2].Y(currentSeed.Y());
		  
		next[3].X(currentSeed.X() + 1);
		next[3].Y(currentSeed.Y());

		for (int i = 0; i < 4; i++) {

			check[i] = abs(rawImage.At(seed.X(), seed.Y()) - rawImage.At(next[i].X(), next[i].Y()));
		}

		for (int i = 0; i < 4; i++) {

			if (next[i].X() != 1 && next[i].X() < (mask.Rows() - 1) && next[i].Y() != 1 && next[i].Y() < (mask.Cols() - 1)) {
		  //inbounds

				if ((check[0] <= th && check[1] <= th) && (check[2] <= th && check[3] <= th)) {
			  //all homogenous
					mask.Set(currentSeed.X(), currentSeed.Y(), 255);
					
					if (mask.At(next[i].X(), next[i].Y()) == 0) {
				  //not visited
						stack.push(next[i]);
						mask.Set(next[i].X(), next[i].Y(), 1);
					}
				}
			}
		}
	}
	procImage = mask;
}

/*
void ImageProcessing::RegionFractal(int th, Point seed) {

	stack<Point>stack;
	Point currentSeed;
	Point next[4];

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255); //visited
	stack.push(seed);
	int check[4];
	const auto lastRow = mask.Rows() - 1;
	const auto lastCol = mask.Cols() - 1;

	while (!stack.empty()) {

		currentSeed = stack.top();
		stack.pop();
		const auto rawAt = rawImage.At(currentSeed.Y(), currentSeed.X());

		next[0].X(currentSeed.X());
		next[0].Y(currentSeed.Y() - 1);

		next[1].X(currentSeed.X());
		next[1].Y(currentSeed.Y() + 1);

		next[2].X(currentSeed.X() - 1);
		next[2].Y(currentSeed.Y());

		next[3].X(currentSeed.X() + 1);
		next[3].Y(currentSeed.Y());


		for (int i = 0; i < 4; i++) {

//			int test1 = rawAt; int test2 = rawImage.At(next[i].X(), next[i].Y());
			check[i] = abs(rawAt - rawImage.At(next[i].X(), next[i].Y()));
//			std::cout << check[i] << ", ";
		}
//		std::cout << endl;

		for (int i = 0; i < 4; i++) {

			if (check[0] <= th && check[1] <= th && check[2] <= th && check[3] <= th) {
				// all homogenous
				mask.Set(currentSeed.X(), currentSeed.Y(), 255);
			}
			if (next[i].X() != 1 && next[i].X() < lastCol && next[i].Y() != 1 && next[i].Y() < lastRow) {
				// inbounds				
				if (mask.At(next[i].X(), next[i].Y()) == 0) {
					// not visited
					stack.push(next[i]);
					mask.Set(next[i].X(), next[i].Y(), 1);
				}
			}// set visited
		}
	}
	procImage = mask;
}
*/