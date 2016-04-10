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
      +- poses.txt    (source file with positions of the robot, this has been hard-coded in the program as "includes/poses.txt")
      +- ranges.txt   (source file with range readings from robot's sensors, this has been hard-coded in the program as "includes/ranges.txt")
- animation.pdf       (an animation of the robot mapping the area)

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

2. Now you need to open your terminal and open the root directory of the project. I will refer 
to it as {PROJECT_DIR} from now on. 

3. Within the project directory create a new folder called build, and open it by typing:

   $ mkdir build
   $ cd build

4. Now run CMake by typing the following in your terminal:

   $ ccmake -DCMAKE_INSTALL_PREFIX=/usr ..

Once you have run this command, press 'c' on your keyboard. Now you will then have to press 'enter'
and specify the CMAKE_BUILD_TYPE using one of the options. You can type in 'Release' and press
'enter' again. Now press 'c', followed by 'g'.

5. Compile the project by typing the following command in your terminal:
   
   $ make

6. Finally, you have to move the {PROJECT_DIR}/includes folder into the previously
created build folder by running:
   
   $ mv {PROJECT_DIR}}/includes/ {PROJECT_DIR}}/build/

7. Congratulations! You have managed to install the OccupandyGrid project and you can
run it by typing the following command within the {PROJECT_DIR}/build/ directory.

   $ ./OccupancyGrid2
   
## CREDITS

[Allegro5 library](http://liballeg.org/)
[Drawing line using Bresenham algorithm tutorial](http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/)
