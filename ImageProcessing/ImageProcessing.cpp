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

void ImageProcessing::setLocal() {

	cout << endl << "Lokal oder Global ? 1. Lokal 0. Global : " << endl;;
	cin >> local;
}

void ImageProcessing::setQuartet() {
	cout << endl << "4er oder 8er Nachbarschaft ? Eingabe 1 zu 4er / Eingabe 0 zu 8er" << endl;
	cin >> quartet;
}

void ImageProcessing::RegionGrowing(int th, Point seed, bool local, bool quartet) {

	stack<Point>stack;
	Point currentSeed;
	Point next[8];

	Image mask(rawImage.Rows(), rawImage.Cols());
	mask.Set(seed.X(), seed.Y(), 255);
	stack.push(seed);
	int check[8];
	int n;


	while (!stack.empty()) {

		currentSeed = stack.top();
		stack.pop();

		vector<int> x = { 0, 0, -1, +1, -1, +1, -1, +1 };
		vector<int> y = { -1, +1, 0, 0, +1, +1, -1, -1 };

		if (quartet) n = 4;
		else n = 8;

		for (int i = 0; i < n; i++)
		{
			next[i].X(currentSeed.X() + x[i]);
			next[i].Y(currentSeed.Y() + y[i]);
		}

		for (int i = 0; i < n; i++) {

			check[i] = abs(rawImage.At(seed.X(), seed.Y()) - rawImage.At(next[i].X(), next[i].Y()));
		}

		for (int i = 0; i < n; i++) {

			if (next[i].X() != 1 && next[i].X() < (mask.Rows() - 1) && next[i].Y() != 1 && next[i].Y() < (mask.Cols() - 1)) {
		    //inbounds

				if (quartet) {

					if (local) {
						if ((check[0] <= th && check[1] <= th) && (check[2] <= th && check[3] <= th)) {
					    //all homogenous
							mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2* check[i]));

							if (mask.At(next[i].X(), next[i].Y()) == 0) {
							//not visited
								stack.push(next[i]);
								mask.Set(next[i].X(), next[i].Y(), 1);
							}
						}
					}
					else {//global

						if ((check[0] <= th && check[1] <= th) && (check[2] <= th && check[3] <= th)) {
						//all homogenous
							mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * check[i]));


						}
						if (mask.At(next[i].X(), next[i].Y()) == 0) {
						//not visited
							stack.push(next[i]);
							mask.Set(next[i].X(), next[i].Y(), 1);
						}
					}
				}

				else if (!quartet)//octet
				{
					if (local) {
						if ((check[0] <= th && check[1] <= th) && (check[2] <= th && check[3] <= th
							&& check[4] <= th && check[5] <= th) && (check[6] <= th && check[7] <= th)) {
							//all homogenous
							mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * check[i]));

							if (mask.At(next[i].X(), next[i].Y()) == 0) {
							//not visited
								stack.push(next[i]);
								mask.Set(next[i].X(), next[i].Y(), 1);
							}
						}
					}
					else {//global

						if ((check[0] <= th && check[1] <= th) && (check[2] <= th && check[3] <= th
							&& check[4] <= th && check[5] <= th) && (check[6] <= th && check[7] <= th)) {
							//all homogenous
							mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * check[i]));


						}
						if (mask.At(next[i].X(), next[i].Y()) == 0) {
						//not visited
							stack.push(next[i]);
							mask.Set(next[i].X(), next[i].Y(), 1);
						}
					}
				}
			}
		}
	}
	procImage = mask;
}


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


		for (int i = 0; i < 4; i++) { // fractal interpreter

//			int test1 = rawAt; int test2 = rawImage.At(next[i].X(), next[i].Y());
			check[i] = abs(rawAt - rawImage.At(next[i].X(), next[i].Y()));
			//			std::cout << check[i] << ", ";
		}
		//		std::cout << endl;

		for (int i = 0; i < 4; i++) {

			if (check[0] <= th && check[1] <= th && check[2] <= th && check[3] <= th) {

				mask.Set(currentSeed.X(), currentSeed.Y(), 255 - (2 * check[i]));
			}
			if (next[i].X() > 1 && next[i].X() < lastCol-1 && next[i].Y() > 1 && next[i].Y() < lastRow-1) {

				if (mask.At(next[i].X(), next[i].Y()) == 0) {

					stack.push(next[i]);
					mask.Set(next[i].X(), next[i].Y(), 1);
				}
			}
		}
	}
	procImage = mask;
}
