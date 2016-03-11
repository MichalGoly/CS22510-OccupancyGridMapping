#ifndef OCCUPANCYGRID2_GRID_H
#define OCCUPANCYGRID2_GRID_H

#include <vector>

class Grid {
private:
    const int GRID_COLS;
    const int GRID_ROWS;
    const int DEFAULT_PROBABILITY;
    const int MAX_PROBABILITY;
    const int MIN_POBABILITY;

    std::vector<std::vector<int>> rawGrid;

    void initGrid();
    std::vector<std::pair<int, int>> getIndices(int x1, int y1, int x2, int y2);

public:
    Grid();
    const std::vector<std::vector<int>> &getRawGrid() const;
    void clearCellsBetween(int x1, int y1, int x2, int y2);
    void increaseProbability(int x, int y);
    void decreaseProbability(int x, int y);
};

#endif //OCCUPANCYGRID2_GRID_H
