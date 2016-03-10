#include "Grid.h"

using std::vector;
using std::pair;

Grid::Grid() : GRID_COLS(50), GRID_ROWS(50) {

}

const std::vector<std::vector<int>> &Grid::getRawGrid() const {
    return rawGrid;
}

void Grid::clearCellsBetween(int x1, int y1, int x2, int y2) {

}

void Grid::increaseProbability(int cellX, int cellY) {

}

void Grid::decreaseProbability(int cellX, int cellY) {

}

void Grid::initGrid() {
    for (int i = 0; i < GRID_COLS; i++) {
        vector<int> row;
        for (int j = 0; j < GRID_ROWS; j++) {
            row.push_back(5);
        }
        rawGrid.push_back(row);
    }
}

//TODO implement
std::vector<std::pair<int, int>> Grid::getIndicies(int x0, int y0, int x, int y) {
    return std::vector<pair<int, int>>();
}
