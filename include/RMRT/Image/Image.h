#pragma once

#include <RMRT/Camera/Camera.h>
#include <RMRT/Objects/HittableList.h>

// Multi-threading support
#include<algorithm>
#include<execution>
#include <vector>

#include <string>
#include <fstream>

namespace rmrt {
	// I don't know if the tutorial does this yet, but I wanted to abstract away a lot of the photo rendering 
	// stuff into it's own class --> will be moving the free functions here as well I believe
	class Image
	{
	public:
		Image(std::string fileName, double aspectRatio, int width);
		~Image();

		void SetDimensions(int width, int height = 0);
		int ImageWidth();
		int ImageHeight();
		void WriteHeaderPPM();
		void SetRaySampleCount(int numberOfSamples);
		void SetDiffuseRayCount(int numberOfRays);
		Color RaySamples(const Camera& camera, const HittableList& world, int horizontalPixel, int verticalPixel);
		void WriteColor(const rmrt::Color& pixelColor);
		void TraceImage(const Camera& camera, const HittableList& world);

	private:
		std::string m_name;
		double m_aspectRatio;
		int m_width;
		int m_height;
		int m_maxDiffuseRays;
		int m_samplesPerPixel;
		std::vector<int> m_samplesIter;
		std::ofstream file;
		std::string fileTempBuff{};
	};

}