set(PROJECT_NAME RMRT)
message("-- Building ${PROJECT_NAME}")

set(RMRT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Individual Groups Of Files
set(RMRT_HEADERS
    "${RMRT_INCLUDE_DIR}/RMRT/RMRT.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Vec3.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Ray.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/HittableObject.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/HittableList.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/Sphere.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Camera/Camera.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Image/Image.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Materials/Material.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Materials/Metal.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Materials/Lambertian.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Materials/Dielectric.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Bounds/AABB.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Bounds/BVH.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Textures/Texture.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Textures/CheckerTexture.h"
)

set(RMRT_SOURCES 
    "RMRT.cpp"
    "Vec3.cpp"
    "Ray.cpp"
    "Objects/Sphere.cpp"
    "Objects/HittableList.cpp"
    "Camera/Camera.cpp"
    "Materials/Metal.cpp"
    "Materials/Lambertian.cpp"
    "Materials/Dielectric.cpp"
    "Image/Image.cpp"
    "Bounds/AABB.cpp"
    "Bounds/BVH.cpp"
    "Textures/Texture.cpp"
    "Textures/CheckerTexture.cpp"
)

source_group(
    TREE "${RMRT_INCLUDE_DIR}/RMRT"
    PREFIX "Header Files"
    FILES ${RMRT_HEADERS}
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    PREFIX "Source Files"
    FILES ${RMRT_SOURCES}
)

set(RMRT_ALL_FILES ${RMRT_SOURCES} ${RMRT_HEADERS})

add_library(${PROJECT_NAME} ${RMRT_ALL_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${RMRT_INCLUDE_DIR} ${VENDOR_INCLUDE_DIR})

set(STANDARD 20)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES CXX_STANDARD ${STANDARD}
               CMAKE_ARCHIVE_OUTPUT_DIRECTORY_<CONFIG> ${CMAKE_SOURCE_DIR}/lib
               CMAKE_LIBRARY_OUTPUT_DIRECTORY_<CONFIG> ${CMAKE_SOURCE_DIR}/lib
               CMAKE_RUNTIME_OUTPUT_DIRECTORY_<CONFIG> ${CMAKE_SOURCE_DIR}/bin
               OUTPUT_NAME "rmrt"
               DEBUG_POSTFIX "_d"
)

message("-- ${PROJECT_NAME} Has Finished Being Built")
