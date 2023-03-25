
#include <RMRT/Raytracer.h>

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
	constexpr auto rgb_factor{ 255.999 };
	constexpr auto cWidth{ img_width - 1 };
	constexpr auto cHeight{ img_height - 1 };

	for (auto i{ cHeight }; i >= 0; --i) {
		// Adding a progress indicator
		std::cerr << "\rScanlines Remaining: " << i << ' ' << std::flush;

		for (auto j{ 0 }; j < img_width; ++j) {
			auto r{ static_cast<double>(j) / cWidth };
			auto g{ static_cast<double>(i) / cHeight };

			auto ir{ static_cast<int>(rgb_factor * r) };
			auto ig{ static_cast<int>(rgb_factor * g) };
			auto ib{ static_cast<int>(rgb_factor * b) };

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	// Progress completed
	std::cerr << "\nDone.\n";
}