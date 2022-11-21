/******************************************************************************
Labor Medizinische Informatik
Studiengang Medizintechnik
Hochschule Pforzheim
*******************************************************************************
Datei:				Image.cpp
Autoren:			Sascha Seifert, Max Barchet, Joachim Storz
Letzte Änderung:	03.09.2018
Beschreibung:		Klasse zur Representation und zur Bearbeitung von Bildern
******************************************************************************/

#include "Image.h"

using namespace std;


Image::Image()
{
	rawImage  = cv::Mat::zeros(1, 1, CV_8UC1);
	procImage = cv::Mat::zeros(1, 1, CV_8UC1);
}

Image::Image(unsigned int rows, unsigned int cols)
{
	rawImage  = cv::Mat::zeros(rows, cols, CV_8UC1);
	procImage = cv::Mat::zeros(rows, cols, CV_8UC1);
}

Image::Image(cv::Mat src)
{
	rawImage  = src;
	procImage = cv::Mat::zeros(rawImage.rows, rawImage.cols, CV_8UC1);
}

Image::~Image()
{
}


void Image::Imread(string filename)
{
	rawImage = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
}

void Image::Set(unsigned int x, unsigned int y, int value)
{
	rawImage.at<uchar>(y, x) = uchar(value);
}

Image Image::Imfusion(Image background, double alpha)
{
	cv::Mat resImage;
	cv::Mat backImage = background.GetRawImage();
	cv::addWeighted(backImage, alpha, rawImage, (1 - alpha), 0.0, resImage);
	return resImage;
}

int Image::At(unsigned int x, unsigned int y)
{
	return rawImage.at<uchar>(y, x);
}

unsigned int Image::Rows()
{
	return rawImage.rows;
}

unsigned int Image::Cols()
{
	return rawImage.cols;
}

bool Image::IsValid()
{
	return rawImage.data != nullptr;
}

Image &Image::operator=(const cv::Mat &src)
{
	rawImage = src;
	return *this;
}

Image::operator cv::Mat&()
{
	return rawImage;
}

cv::Mat Image::GetRawImage()
{
	return rawImage;
}
