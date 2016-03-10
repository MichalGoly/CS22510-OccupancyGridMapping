#ifndef OCCUPANCYGRID2_ROBOT_H
#define OCCUPANCYGRID2_ROBOT_H

#include <string>
#include <vector>
#include <iostream>

class Robot {
private:
    const std::string POSES_FILE;
    const std::string RANGES_FILE;

    std::vector<std::vector<double>> poses;
    std::vector<std::vector<double>> ranges;
    std::vector<std::vector<double>> sensorAngles;

    void read(std::istream &in, std::vector<std::vector<double>> &v,
              std::vector<double>::size_type size);

public:
    Robot();
};

#endif //OCCUPANCYGRID2_ROBOT_H
