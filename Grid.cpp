#include <stdlib.h>
#include <stdexcept>
#include "Grid.h"

using std::domain_error;

/**
 * Constructs the Grid object which represents the 50x50 grid in the system.
 * Internally, grid is represented as a 2D vector of integers. Each number
 * corresponds to the probability of each cell being occupied by an
 * obstacle. The initial value of each cell can be either decreased or
 * increased by the member functions provided, up to the point of
 * a minimal or maximal probability, 1 and 9 respectively.
 *
 * Constant data members are initialised using the member initializer list
 * technique to improve the performance of the program.
 */
Grid::Grid() : COLS_NUMBER(50), ROWS_NUMBER(50), DEFAULT_PROBABILITY(5),
               MAX_PROBABILITY(9), MIN_PROBABILITY(1) {
    initGrid();
}

/**
 * @return The raw 2D vector which represents the grid in the system
 */
const std::vector<std::vector<int>> &Grid::getRawGrid() const {
    return rawGrid;
}

/**
 * @return The amount of rows in the grid
 */
int Grid::getRowsNumber() const {
    return ROWS_NUMBER;
}

/**
 * @return The amount of columns in the grid
 */
int Grid::getColsNumber() const {
    return COLS_NUMBER;
}

/**
 * Decreases the probability of all the cells being occupied between the two
 * points provided. Typically (x1,y1) are the coordinates of the robot and
 * (x2,y2) are the coordinates of the obstacle.
 *
 * @param x1 The x index of the first cell
 * @param y1 The y index of the first cell
 * @param x2 The x index of the second cell
 * @param y2 The y index of the second cell
 */
void Grid::clearCellsBetween(int x1, int y1, int x2, int y2) {
    std::vector<std::pair<int, int>> indices = getIndices(x1, y1, x2, y2);

    for (std::vector<std::pair<int, int>>::const_iterator it = indices.begin();
         it != indices.end(); it++) {
        decreaseProbability(it->first, it->second);
    }
}

/**
 * Increases the probability of the cell being occupied in the grid with given x
 * and y indices. Probability of the cell will be increased by 2, only if
 * the probability is not already set to the highest possible value of 9.
 *
 * @param x The x index of the cell which will have its probability increased
 * @param y The y index of the cell which will have its probability increased
 * @throws The index out of bounds domain error will be thrown if one of the
 * indices will indicate a cell outside of the 50x50 grid
 */
void Grid::increaseProbability(int x, int y) {
    if (x < 0 || x >= COLS_NUMBER || y < 0 || y >= ROWS_NUMBER) {
        throw domain_error("Index out of bounds!");
    }

    if (rawGrid[x][y] < MAX_PROBABILITY) {
        rawGrid[x][y] += 2;
    }
}

/**
 * Reduces the probability of the cell being occupied in the grid with given x
 * and y indices. Probability of the cell will be decreased by 2, only if
 * the probability is not already set to the lowest possible value of 1.
 *
 * @param x The x index of the cell which will have its probability decreased
 * @param y The y index of the cell which will have its probability decreased
 * @throws The index out of bounds domain error will be thrown if one of the
 * indices will indicate a cell outside of the 50x50 grid
 */
void Grid::decreaseProbability(int x, int y) {
    if (x < 0 || x >= COLS_NUMBER || y < 0 || y >= ROWS_NUMBER) {
        throw domain_error("Index out of bounds!");
    }

    if (rawGrid[x][y] > MIN_PROBABILITY) {
        rawGrid[x][y] -= 2;
    }
}

/**
 * Initialises the grid by filling the 2D vector with default probability
 * values. The resulting grid will be of size 50x50.
 */
void Grid::initGrid() {
    for (int i = 0; i < ROWS_NUMBER; i++) {
        std::vector<int> row;
        for (int j = 0; j < COLS_NUMBER; j++) {
            row.push_back(DEFAULT_PROBABILITY);
        }
        rawGrid.push_back(row);
    }
}

/**
 *  Calculates and returns all the cell indices between the two points (x1, y1)
 *  and (x2, y2) in the grid.
 *
 *  Based on the tutorial here:
 *  http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
 *
 *  @param x1 The x index of the first point
 *  @param y1 The y index of the first point
 *  @param x2 The x index of the second point
 *  @param y2 The y index of the second point
 *  @return The vector of all the indices between the two points provided
 */
std::vector<std::pair<int, int>> Grid::getIndices(int x1, int y1,
                                                  int x2, int y2) {
    std::vector<std::pair<int, int>> result;

    int width = x2 - x1;
    int height = y2 - y1;
    int dx0 = 0;
    int dy0 = 0;
    int dx = 0;
    int dy = 0;

    if (width < 0) {
        dx0 = -1;
    } else if (width > 0) {
        dx0 = 1;
    }

    if (height < 0) {
        dy0 = -1;
    } else if (height > 0) {
        dy0 = 1;
    }

    if (width < 0) {
        dx = -1;
    } else if (width > 0) {
        dx = 1;
    }

    int longest = abs(width);
    int shortest = abs(height);

    if (longest <= shortest) {
        longest = abs(height);
        shortest = abs(width);

        if (height < 0) {
            dy = -1;
        } else if (height > 0) {
            dy = 1;
        }
        dx = 0;
    }
    int numerator = longest >> 1;

    for (int i = 0; i < longest - 1; i++) {
        numerator += shortest;

        if (numerator >= longest) {
            numerator -= longest;
            x1 += dx0;
            y1 += dy0;
        } else {
            x1 += dx;
            y1 += dy;
        }
        result.push_back(std::pair<int, int>(x1, y1));
    }

    return result;
}
