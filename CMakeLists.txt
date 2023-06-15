cmake_minimum_required(VERSION 3.5)

project(dmusic)

set(CMAKE_CXX_STANDARD 17)

# Find all source files in the source directory
# file(GLOB_RECURSE SOURCES "source/*.cpp")
set(DIRECTMUSIC_SOURCES
source/band.cpp
source/directmusic.cpp
source/dlscollection.cpp
source/hydra.cpp
source/info.cpp
source/mixer.cpp
source/music.cpp
source/pattern.cpp
source/patternlist.cpp
source/reference.cpp
source/riff.cpp
source/segment.cpp
source/soundfont.cpp
source/style.cpp
source/track.cpp
source/wave.cpp
source/logger.cpp
)

file(GLOB_RECURSE DIRECTMUSIC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_library(dmusic STATIC)

target_sources(dmusic PRIVATE ${DIRECTMUSIC_SOURCES})
target_include_directories(dmusic PUBLIC include)
set_target_properties(dmusic PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)