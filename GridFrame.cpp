#include <iostream>
#include <stdexcept>
#include "GridFrame.h"
#include "converter.h"

using std::domain_error;

/*
 * Creates the GridFrame object which is responsible for GUI of the program using
 * the allegro5 library. GridFrame is also responsible for initialisation of
 * both the Grid and Robot objects which will be later used to create an animation
 * of a robot crawling through the area and creating an occupancy grid.
 *
 * GridFrame is created with the default height and width of 500 and the cell width
 * of 10 to accommodate for the 50x50 grid in the system.
 */
GridFrame::GridFrame() : WINDOW_WIDTH(500), WINDOW_HEIGHT(500), CELL_WIDTH(10) {
    grid = new Grid;
    robot = new Robot;
    initFrame();
    initColors();
}

/**
 * Destructs the GridFrame object by releasing the occupied memory back to
 * the operating system. Grid and Robot objects created using the 'new' keyword
 * in the constructor will be destroyed, and both the ALLEGRO_DISPLAY and
 * ALLEGRO_EVENT_QUEUE objects will also be destroyed using appropriate
 * functions provided by the allegro5 library.
 */
GridFrame::~GridFrame() {
    delete(grid);
    delete(robot);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);
}

/**
 * Creates an animation of the robot crawling through the grid and mapping it
 * using poses and ranges data provided. Initially the whole grid will be
 * grey which corresponds to the default probability of given cell being
 * occupied. Each time robot changes position, the screen will be repainted
 * to show the result of previous reading. User can either wait and watch
 * the whole animation up to the final frame being displayed, after which
 * he will be able to further examine the final occupancy grid. Thanks to
 * the event listeners, it is possible to close the GUI window at any time
 * during the animation.
 */
void GridFrame::animate() {
    // create placeholders for the position of the robot, its orientation,
    // its orientation in radians (beta) and X and Y coordinates of an obstacle
    double xr, yr, orientation, beta, x, y;

    // retrieve all the positions, ranges read by the sensors and sensor angles
    std::vector<std::vector<double>> poses = robot->getPoses();
    std::vector<std::vector<double>> ranges = robot->getRanges();
    std::vector<double> sensorAngles = robot->getSensorAngles();

    for (std::vector<std::vector<double>>::size_type i = 0; i < poses.size(); i++) {
        xr = robot->getPoses()[i][0];
        yr = robot->getPoses()[i][1];
        orientation = robot->getPoses()[i][2];
        beta = converter::toRadians(orientation);

        for (std::vector<double>::size_type j = 0; j < ranges.begin()->size(); j++) {
            // ignore readings of 2.5 and above as they are actually infinity
            if (ranges[i][j] >= 2.5) {
                continue;
            } else {
                // for each range calculate the coordinates of an obstacle (in metres)
                x = converter::getX(xr, ranges[i][j],
                                    converter::toRadians(sensorAngles[j]), beta);
                y = converter::getY(yr, ranges[i][j],
                                    converter::toRadians(sensorAngles[j]), beta);

                // increase the probability of this cell being occupied
                grid->increaseProbability(converter::toCellIndex(x),
                                          converter::toCellIndex(y));

                // decrease the probability of all the cells between the robot
                // and the current obstacle
                grid->clearCellsBetween(converter::toCellIndex(xr),
                                        converter::toCellIndex(yr),
                                        converter::toCellIndex(x),
                                        converter::toCellIndex(y));
            }
        }

        repaint();

        // wait for 1.5s between each refresh of the screen and listen to
        // the event being fired if user clicks the 'x' exit button.
        al_init_timeout(&timeout, 1.5);
        bool eventOccurred = al_wait_for_event_until(eventQueue, &event, &timeout);
        if (eventOccurred && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // close the window and exit the program
            return;
        }
    }

    // After the animation finishes and the resulting occupancy grid is presented
    // wait for the user to click the 'x' exit button to close the program.
    while (1) {
        bool eventOccurred = al_wait_for_event_until(eventQueue, &event, &timeout);
        if (eventOccurred && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
}

/**
 * Initialises the GUI components provided by allegro5 library. An
 * appropriate display and event queue will be created to support the
 * animation later on in the program.
 *
 * @throws An appropriate domain error if initialisation of allegro5 fails
 */
void GridFrame::initFrame() {
    if (!al_init()) {
        throw domain_error("Allegro5 failed to initialise");
    }

    // create the allegro5 display, set its size, position and title
    display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!display) {
        throw domain_error("Allegro5 failed to create the display");
    }
    al_set_window_position(display, 150, 150);
    al_set_window_title(display, "Occupancy Grid");

    // enable drawing 2D graphics
    al_init_primitives_addon();

    // event queue will contain events generated by the user later on
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        throw domain_error("Allegro5 failed to create the event queue");
    }
    al_register_event_source(eventQueue, al_get_display_event_source(display));
}

/**
 * Initialises the colors associative container (map), by filling it with
 * ALLEGEO_COLOR objects corresponding to probability values in the
 * raw grid. The default probability is 5, 1 (white) means it is highly
 * unlikely this cell is occupied, 9 (black) means it is almost certain
 * given cell is occupied by an obstacle.
 */
void GridFrame::initColors() {
    colors[1] = al_map_rgb(255, 255, 255); // white
    colors[3] = al_map_rgb(207, 207, 207); // light grey
    colors[5] = al_map_rgb(135, 135, 135); // grey
    colors[7] = al_map_rgb(77, 77, 77);    // dark grey
    colors[9] = al_map_rgb(0, 0, 0);       // black
}

/**
 * Repaints the GUI by iterating through the raw 2D grid of probability
 * values and drawing a rectangle with a corresponding colour in
 * appropriate positions.
 */
void GridFrame::repaint() {
    // these two values correspond to the top left corner of a cell being painted
    int x0 = 0;
    int y0 = 0;

    // x and y correspond to indices in the raw grid of values. y starts from the
    // highest value and is being decremented with each iteration, because
    // (0,0) coordinate in the raw grid is in the bottom left corner, whereas
    // we start painting from the top left corner (x0, y0)
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

    // makes the ALLEGEO_DISPLAY to refresh itself to show the changes
    al_flip_display();
}
