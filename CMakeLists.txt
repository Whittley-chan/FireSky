cmake_minimum_required(VERSION 3.15)
project(Firesky)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src             
)

# SDL3 library path
link_directories(${CMAKE_SOURCE_DIR}/SDL/lib/x64)

# Source files (.cpp)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# Header files
file(GLOB_RECURSE HEADER_FILES
    ${PROJECT_SOURCE_DIR}/include/*.h
    ${PROJECT_SOURCE_DIR}/src/*.h
)

install(DIRECTORY resources DESTINATION .)

# Add executable
add_executable(FireSky ${SOURCE_FILES} ${HEADER_FILES})

# Link with SDL3
target_link_libraries(FireSky SDL3 SDL3_image SDL3_ttf SDL3_test)

# Output folder
set_target_properties(FireSky PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    LINK_FLAGS "/MANIFEST:NO"
)