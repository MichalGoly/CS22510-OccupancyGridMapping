## WHAT IS INCLUDED

- README.txt
- CMakeLists.txt      (CMake build script)
- converter.cpp       (source code file)
- converter.h         (source code file)
- Grid.cpp            (source code file)
- Grid.h              (source code file)
- GridFrame.cpp       (source code file)
- GridFrame.h         (source code file)
- main.cpp            (source code file)
- Robot.cpp           (source code file)
- Robot.h             (source code file)
- includes/           (directory for the source files)
      |
      +- poses.txt    (source file with positions of the robot)
      +- ranges.txt   (source file with range readings from robot's sensors)
- report.pdf          (the document which describes what I have done)
- build/              (build directory)
- output.pdf          (animation of robot mapping the area)
- screencast.          (building the program and running the code)

## INSTALLATION 

0. This program has been built on the following system using the C++11 standard 
and CLion IDE 1.2.4 (built on the 25th of December 2015):

   Distributor ID:   LinuxMint
   Description:   Linux Mint 17.3 Rosa
   Release: 17.3
   Codename:   rosa

Furthermore, the following flags were used with the g++ 
compiler (g++ version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.1)):

   -std=c++11 -W -Wall -Wextra -pedantic

1. First of all you need to install the allegro5 library using the tutorial 
available [here](https://wiki.allegro.cc/index.php?title=Install_Allegro5_From_Git/Linux/Debian).

2. Now you need to open your terminal and open the build/ directory:

   cd {OCCUPANCY_GRID_INSTALLATION_PATH}/build

3. Finally, install the program by typing:
   
   make
   
## CREDITS

[Allegro5 library](http://liballeg.org/)
[Drawing line using Bresenham algorithm tutorial](http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/)
