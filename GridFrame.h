#ifndef OCCUPANCYGRID2_GRIDFRAME_H
#define OCCUPANCYGRID2_GRIDFRAME_H

#include <vector>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Grid.h"
#include "Robot.h"

class GridFrame {
private:
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int CELL_WIDTH;

    Grid* grid;
    Robot* robot;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT* event;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    std::map<int, ALLEGRO_COLOR> colors;

    void initFrame();
    void initColors();
    void repaint();

public:
    GridFrame();
    void animate();
};

#endif //OCCUPANCYGRID2_GRIDFRAME_H
