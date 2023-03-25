set(PROJECT_NAME Raytracer_Sandbox)

message("-- Building ${PROJECT_NAME}")

set(SANDBOX_SOURCE_FILES "sandbox.cpp")
add_executable(${PROJECT_NAME} ${SANDBOX_SOURCE_FILES})

set(STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD ${STANDARD})

target_include_directories(${PROJECT_NAME} PUBLIC ${RMRT_INCLUDE_DIR})

target_link_libraries(
    ${PROJECT_NAME}
    ${RMRT}
)