#pragma once

#include <RMRT/Camera/Camera.h>
#include <RMRT/Objects/HittableList.h>

// Multi-threading support
#include <algorithm>
#include <array>
#include <execution>
#include <vector>

#include <fstream>
#include <string>

namespace rmrt {

	namespace img_helper {
		constexpr int BUFF_SIZE = 16;
	}

	class Image
	{
		struct ProgressTracker
		{
			double m_hours { 0 };
			double m_minutes { 0 };
			double m_seconds { 0 };
			void EstimateTimeLeft(int currentScanLine, int totalScanLines, const std::chrono::steady_clock::time_point& startTime);
			std::string TimeLeftStr(int currentScanLine, int totalScanLines, const std::chrono::steady_clock::time_point& startTime);
			void PrintProgress(int totalScanLines, int totalWidth, int pixelX, int pixelY, const std::chrono::steady_clock::time_point& startTime);
		};

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
		void WriteColor(const rmrt::Color& pixelColor, int horizontalPixel, int verticalPixel);
		void TraceImage(const Camera& camera, const HittableList& world);
		void PrintImageToFile();

	  private:
		void ResizeImageMatrix();

	  private:
		std::string m_name;
		float m_aspectRatio;
		int m_width;
		int m_height;
		int m_maxDiffuseRays;
		int m_samplesPerPixel;
		std::vector<int> m_samplesIter;
		std::ofstream m_file;
		std::array<char, img_helper::BUFF_SIZE> m_buffer {};
		float m_scale;
		ProgressTracker m_tracker;
		std::vector<std::vector<std::string>> m_imgMatrix;
	};

}    // namespace rmrt