#include <stdlib.h>
#include <stdexcept>
#include "Grid.h"

using std::vector;
using std::pair;
using std::domain_error;

Grid::Grid() : COLS_NUMBER(50), ROWS_NUMBER(50), DEFAULT_PROBABILITY(5),
               MAX_PROBABILITY(9), MIN_POBABILITY(1) {
    initGrid();
}

const std::vector<std::vector<int>> &Grid::getRawGrid() const {
    return rawGrid;
}

const int Grid::getRowsNumber() const {
    return ROWS_NUMBER;
}

const int Grid::getColsNumber() const {
    return COLS_NUMBER;
}

void Grid::clearCellsBetween(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> indices = getIndices(x1, y1, x2, y2);

    for (vector<pair<int, int>>::const_iterator it = indices.begin();
         it != indices.end(); it++) {
        decreaseProbability(it->first, it->second);
    }
}

// increase probability of not already maximal
void Grid::increaseProbability(int x, int y) {
    if (x < 0 || x >= COLS_NUMBER || y < 0 || y >= ROWS_NUMBER) {
        throw domain_error("Index out of bounds!");
    }

    if (rawGrid[x][y] < MAX_PROBABILITY) {
        rawGrid[x][y] += 2;
    }
}

// reduce probability if not already the least
void Grid::decreaseProbability(int x, int y) {
    if (x < 0 || x >= COLS_NUMBER || y < 0 || y >= ROWS_NUMBER) {
        throw domain_error("Index out of bounds!");
    }

    if (rawGrid[x][y] > MIN_POBABILITY) {
        rawGrid[x][y] -= 2;
    }
}

void Grid::initGrid() {
    for (int i = 0; i < ROWS_NUMBER; i++) {
        vector<int> row;
        for (int j = 0; j < COLS_NUMBER; j++) {
            row.push_back(DEFAULT_PROBABILITY);
        }
        rawGrid.push_back(row);
    }
}

/**
 *  returns all cell indices between (x1, y1) and (x2, y2) in the grid
 *  based on the tutorial here
 *  http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/
 */
std::vector<std::pair<int, int>> Grid::getIndices(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> result;

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
        result.push_back(pair<int, int>(x1, y1));
    }

    return result;
}
