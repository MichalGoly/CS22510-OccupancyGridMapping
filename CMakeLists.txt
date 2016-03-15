cmake_minimum_required(VERSION 3.3)
project(OccupancyGrid2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -pedantic")

set(SOURCE_FILES main.cpp converter.cpp converter.h Robot.cpp Robot.h GridFrame.cpp GridFrame.h Grid.cpp Grid.h)
add_executable(OccupancyGrid2 ${SOURCE_FILES})

INCLUDE_DIRECTORIES(allegro/5.0.11/include)

LINK_DIRECTORIES(allegro/5.0.11/lib)

TARGET_LINK_LIBRARIES(OccupancyGrid2  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)