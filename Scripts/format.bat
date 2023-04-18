@echo off

echo -- Formatting Files...
cd ../
		clang-format -i -style=file include/RMRT/*.h
		clang-format -i -style=file include/RMRT/Bounds/*.h
		clang-format -i -style=file include/RMRT/Camera/*.h
		clang-format -i -style=file include/RMRT/Image/*.h
		clang-format -i -style=file include/RMRT/Image/*.h
		clang-format -i -style=file include/RMRT/Materials/*.h
		clang-format -i -style=file include/RMRT/Objects/*.h
		clang-format -i -style=file include/RMRT/Textures/*.h

		clang-format -i -style=file src/*.cpp
		clang-format -i -style=file src/Bounds/*.cpp
		clang-format -i -style=file src/Camera/*.cpp
		clang-format -i -style=file src/Image/*.cpp
		clang-format -i -style=file src/Materials/*.cpp
		clang-format -i -style=file src/Objects/*.cpp
		clang-format -i -style=file src/Textures/*.cpp

		clang-format -i -style=file Raytracer_Sandbox/*.cpp
cd Scripts
echo -- Formatting Finished