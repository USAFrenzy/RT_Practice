#pragma once

#include <RMRT/Camera/Camera.h>
#include <RMRT/Objects/HittableList.h>

// Multi-threading support
#include<algorithm>
#include<execution>
#include <vector>
#include <array>

#include <string>
#include <fstream>

namespace rmrt {
	// I don't know if the tutorial does this yet, but I wanted to abstract away a lot of the photo rendering 
	// stuff into it's own class --> will be moving the free functions here as well I believe
	class Image
	{
	public:
		Image(std::string_view fileName, float aspectRatio, int width);
		~Image();

		void SetDimensions(int width, int height = 0);
		int ImageWidth();
		int ImageHeight();
		void WriteHeaderPPM();
		void SetRaySampleCount(int numberOfSamples);
		void SetDiffuseRayCount(int numberOfRays);
		void ScaleVecViaClamp(Vec3& vec, float min, float max);
		Color RaySamples(const Camera& camera, const HittableList& world, int horizontalPixel, int verticalPixel);
		int RaySampleCount();
		int DiffuseRayCount();
		void WriteColor(const rmrt::Color& pixelColor);
		void TraceImage(const Camera& camera, const HittableList& world);

	private:
		std::string m_name;
		float m_aspectRatio;
		int m_width;
		int m_height;
		int m_maxDiffuseRays;
		int m_samplesPerPixel;
		std::vector<int> m_samplesIter;
		std::ofstream m_file;
		//std::string fileTempBuff{};
		std::array<char, 16> m_buffer{};
		float m_scale;
	};

}