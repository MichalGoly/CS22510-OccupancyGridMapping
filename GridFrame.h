#ifndef OCCUPANCYGRID2_GRIDFRAME_H
#define OCCUPANCYGRID2_GRIDFRAME_H

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Grid.h"

class GridFrame {
private:
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;

    Grid* grid;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT* event;

    void initFrame();
    void repaint();

public:
    GridFrame();
    void animate();
};

#endif //OCCUPANCYGRID2_GRIDFRAME_H
