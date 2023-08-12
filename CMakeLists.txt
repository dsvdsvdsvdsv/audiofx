cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_FLAGS "-O2")
project(audiofx)
set(FX_DIR fx)
set(SOURCES
    ${FX_DIR}/Compressor/Compressor.cpp
    ${FX_DIR}/Delay/Delay.cpp
)
add_executable(${PROJECT_NAME} fx/test.cpp ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE fx/Delay fx/Compressor fx/CommonIncludes AudioFile)