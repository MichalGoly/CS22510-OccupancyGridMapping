#include <iostream>
#include <stdexcept>
#include "GridFrame.h"

using std::vector;
using std::domain_error;

GridFrame::GridFrame() : WINDOW_HEIGHT(500), WINDOW_WIDTH(500) {
    initFrame();
    grid = new Grid;
}

void GridFrame::animate() {

}

void GridFrame::initFrame() {
    if (!al_init()) {
        throw domain_error("Allegro5 failed to initialise");
    }

    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_set_window_position(display, 150, 150);
    al_set_window_title(display, "Occupancy Grid");
}

void GridFrame::repaint() {

}
