#ifndef OCCUPANCYGRID2_ROBOT_H
#define OCCUPANCYGRID2_ROBOT_H

#include <string>
#include <vector>
#include <iostream>

class Robot {
private:
    static const std::string POSES_FILE;
    static const std::string RANGES_FILE;

    std::vector<std::vector<double>> poses;
    std::vector<std::vector<double>> ranges;
    std::vector<double> sensorAngles;

    void readInData();
    void read(std::istream &in, std::vector<std::vector<double>> &v,
              std::vector<double>::size_type size);

public:
    Robot();
    const std::vector<std::vector<double>> &getPoses() const;
    const std::vector<std::vector<double>> &getRanges() const;
    const std::vector<double> &getSensorAngles() const;
};

#endif //OCCUPANCYGRID2_ROBOT_H
