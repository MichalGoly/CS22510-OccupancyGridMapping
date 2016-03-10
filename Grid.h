#ifndef OCCUPANCYGRID2_GRID_H
#define OCCUPANCYGRID2_GRID_H

#include <vector>

class Grid {
private:
    const int GRID_COLS;
    const int GRID_ROWS;

    std::vector<std::vector<int>> rawGrid;

    void initGrid();
    std::vector<std::pair<int, int>> getIndicies(int x0, int y0, int x, int y);

public:
    Grid();
    const std::vector<std::vector<int>> &getRawGrid() const;
    void clearCellsBetween(int x1, int y1, int x2, int y2);
    void increaseProbability(int cellX, int cellY);
    void decreaseProbability(int cellX, int cellY);
};

#endif //OCCUPANCYGRID2_GRID_H
