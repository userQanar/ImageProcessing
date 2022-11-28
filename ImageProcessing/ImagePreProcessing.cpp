/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				ImagePreProcessing.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zur elementaren Bildverarbeitung und -konvertierung
******************************************************************************/

#include "ImagePreProcessing.h"
#include <iostream>
using namespace std;


ImagePreProcessing::ImagePreProcessing(Image src)
{
	rawImage = src.GetRawImage();
	procImage = cv::Mat::zeros(rawImage.rows, rawImage.cols, CV_8UC1);
	dx = procImage;//cv::Mat::zeros(rawImage.rows, rawImage.cols, CV_16SC1);//
	dy = procImage;//cv::Mat::zeros(rawImage.rows, rawImage.cols, CV_16SC1);//
}

ImagePreProcessing::~ImagePreProcessing()
{
}


Image ImagePreProcessing::Convert2Gray()
{
	cv::cvtColor(rawImage, procImage, CV_RGB2GRAY);
	Image sincClass(procImage);
	return sincClass;
}

Image ImagePreProcessing::Threshold(int val1, int val2)
{
	cv::threshold(rawImage, procImage, val1, val2, CV_THRESH_BINARY);
	Image newImage(procImage);
	return newImage;
}

vector<float> ImagePreProcessing::GetHistogram(int histSize)
{

	float range[] = { 0, (float)histSize - 1 };
	const float *ranges[] = { range };

	cv::MatND hist;
	cv::calcHist(&rawImage, 1, 0, cv::Mat(), hist, 1, &histSize, ranges, true, false);

	vector<float> histBins;
	for (int i = 0; i < histSize; i++)
	{
		histBins.push_back(hist.at<float>(i));
	}

	return histBins;
}

Image ImagePreProcessing::BoxFilter(unsigned char ksize)
{
	if (ksize <= 1)ksize = 1;
	else ksize = (ksize * 2) - 1;

	cv::blur(rawImage, procImage, cv::Size(ksize, ksize));
	Image processedImage(procImage);
	return processedImage;
}

Image ImagePreProcessing::GaussFilter(unsigned char ksize)
{
	if (ksize <= 1)ksize = 1;
	else ksize = (ksize * 2) - 1;

	cv::GaussianBlur(rawImage, procImage, cv::Size(ksize, ksize), 0.0, 0.0);
	Image processedImage(procImage);
	return processedImage;
}

Image ImagePreProcessing::MedianFilter(unsigned char ksize)
{
	if (ksize <= 1)ksize = 1;
	else ksize = (ksize * 2) - 1;

	cv::medianBlur(rawImage, procImage, ksize);
	Image processedImage(procImage);
	return processedImage;
}

Image ImagePreProcessing::SobelFilter(int chooseFilter, unsigned char ksize) {

	if (ksize <= 1)ksize = 1;
	else ksize = (ksize * 2) - 1;

		if (chooseFilter == 0){// ksize of Sobel kernel must be 3.
			cv::Sobel(rawImage, dx, CV_8UC1, 1, 0, 3);
			cv::Sobel(rawImage, dy, CV_8UC1, 0, 1, 3);
		}

		else if (chooseFilter == 1) {
			cv::blur(rawImage, procImage, cv::Size(ksize, ksize));
			cv::Sobel(procImage, dx, CV_8UC1, 1, 0, 3);
			cv::Sobel(procImage, dy, CV_8UC1, 0, 1, 3);
		}
		else if (chooseFilter == 2) {
			cv::GaussianBlur(rawImage, procImage, cv::Size(ksize, ksize), 0.0, 0.0);
			cv::Sobel(procImage, dx, CV_8UC1, 1, 0, 3);
			cv::Sobel(procImage, dy, CV_8UC1, 0, 1, 3);
		}
		else if (chooseFilter == 3) {
			cv::medianBlur(rawImage, procImage, ksize);
			cv::Sobel(procImage, dx, CV_8UC1, 1, 0, 3);
			cv::Sobel(procImage, dy, CV_8UC1, 0, 1, 3);
		}
	
	Image processedImage(procImage);
	processedImage.Imfusion(dx, 0.5);
	processedImage.Imfusion(dy, 0.5);

	return processedImage;
}

Image ImagePreProcessing::wantToSave(Image gray, Image processed)
{
	cout << endl << "Graubild ersetzen ?" << endl;
	cin >> save;

	if (save) return processed;
	return gray;
}