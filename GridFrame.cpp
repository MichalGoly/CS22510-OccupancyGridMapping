#include <iostream>
#include <stdexcept>
#include "GridFrame.h"
#include "converter.h"

using std::vector;
using std::domain_error;

GridFrame::GridFrame() : WINDOW_HEIGHT(500), WINDOW_WIDTH(500), CELL_WIDTH(10) {
    grid = new Grid;
    robot = new Robot;
    initFrame();
    initColors();
}

void GridFrame::animate() {
    double xr, yr, orientation, beta, x, y;

    vector<vector<double>> poses = robot->getPoses();
    vector<vector<double>> ranges = robot->getRanges();
    vector<double> sensorAngles = robot->getSensorAngles();

    for (vector<vector<double>>::size_type i = 0; i < poses.size(); i++) {
        xr = robot->getPoses()[i][0];
        yr = robot->getPoses()[i][1];
        orientation = robot->getPoses()[i][2];
        beta = converter::toRadians(orientation);

        for (vector<double>::size_type j = 0; j < ranges.begin()->size(); j++) {
            if (ranges[i][j] >= 2.5) {
                continue;
            } else {
                x = converter::getX(xr, ranges[i][j],
                                    converter::toRadians(sensorAngles[j]), beta);
                y = converter::getY(yr, ranges[i][j],
                                    converter::toRadians(sensorAngles[j]), beta);
                grid->increaseProbability(converter::toCellIndex(x),
                                          converter::toCellIndex(y));
                grid->clearCellsBetween(converter::toCellIndex(xr),
                                        converter::toCellIndex(yr),
                                        converter::toCellIndex(x),
                                        converter::toCellIndex(y));
            }
        }

        repaint();
        al_init_timeout(&timeout, 1.5);
        bool eventOccured = al_wait_for_event_until(eventQueue, &event, &timeout);
        if (eventOccured && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }

    while (1) {
        bool eventOccured = al_wait_for_event_until(eventQueue, &event, &timeout);
        if (eventOccured && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
}

void GridFrame::initFrame() {
    if (!al_init()) {
        throw domain_error("Allegro5 failed to initialise");
    }

    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_set_window_position(display, 150, 150);
    al_set_window_title(display, "Occupancy Grid");
    al_init_primitives_addon();

    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        throw domain_error("Failed to create the event queue");
    }
    al_register_event_source(eventQueue, al_get_display_event_source(display));
}

void GridFrame::initColors() {
    colors[1] = al_map_rgb(255, 255, 255); // white
    colors[3] = al_map_rgb(207, 207, 207); // light grey
    colors[5] = al_map_rgb(135, 135, 135); // grey
    colors[7] = al_map_rgb(77, 77, 77);    // dark grey
    colors[9] = al_map_rgb(0, 0, 0);       // black
}

void GridFrame::repaint() {
    int x0 = 0;
    int y0 = 0;

    for (int y = grid->getRowsNumber() - 1; y >= 0; y--) {
        for (int x = 0; x < grid->getColsNumber(); x++) {
            al_draw_filled_rectangle(x0 * CELL_WIDTH, y0 * CELL_WIDTH,
                                     x0 * CELL_WIDTH + CELL_WIDTH,
                                     y0 * CELL_WIDTH + CELL_WIDTH,
                                     colors[grid->getRawGrid()[x][y]]);
            x0++;
        }
        x0 = 0;
        y0++;
    }

    al_flip_display();
}
