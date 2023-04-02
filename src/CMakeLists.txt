set(PROJECT_NAME RMRT)
message("-- Building ${PROJECT_NAME}")

set(RMRT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Individual Groups Of Files
set(RMRT_HEADERS
    "${RMRT_INCLUDE_DIR}/RMRT/Vec3.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Ray.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/HittableObject.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/HittableList.h"
    "${RMRT_INCLUDE_DIR}/RMRT/Objects/Sphere.h"
)

set(RMRT_SOURCES 
    "Vec3.cpp"
    "Ray.cpp"
    "Objects/Sphere.cpp"
    "Objects/HittableList.cpp"
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

target_include_directories(${PROJECT_NAME} PUBLIC ${RMRT_INCLUDE_DIR})

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
