
#include <RMRT/Vec3.h>

#include <iostream>

int main()
{

	// Image
	constexpr int img_width{ 256 };
	constexpr int img_height{ 256 };

	// Render
	std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

	// Extracting the variables from within the loop that the original author  had being initialized in the loop each iteration
	constexpr auto b{ 0.25 };
	constexpr auto cWidth{ img_width - 1 };
	constexpr auto cHeight{ img_height - 1 };

	for (auto i{ cHeight }; i >= 0; --i) {
		// Adding a progress indicator
		std::cerr << "\rScanlines Remaining: " << i << ' ' << std::flush;

		for (auto j{ 0 }; j < img_width; ++j) {
			rmrt::color pixelColor {static_cast<double>(j)/cWidth, static_cast<double>(i)/cHeight, b};
			rmrt::write_color(std::cout, pixelColor);
		}
	}
	// Progress completed
	std::cerr << "\nDone.\n";
}