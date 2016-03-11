#include "Robot.h"
#include <fstream>

using std::istream;
using std::vector;
using std::string;
using std::ifstream;

const string Robot::POSES_FILE = "includes/poses.txt";
const string Robot::RANGES_FILE = "includes/ranges.txt";

Robot::Robot() {
    readInData();
    sensorAngles = {0, 45, 90, 135, 180, 225, 270, 315};
}

const std::vector<std::vector<double>> &Robot::getPoses() const {
    return poses;
}

const std::vector<std::vector<double>> &Robot::getRanges() const {
    return ranges;
}

const std::vector<double> &Robot::getSensorAngles() const {
    return sensorAngles;
}

/*
 * read in poses and ranges and store them in the internal 2D vectors
 */
void Robot::readInData() {
    ifstream infile(POSES_FILE);
    read(infile, poses, 3);
    infile.close();
    infile.clear();

    infile.open(RANGES_FILE);
    read(infile, ranges, 8);
    infile.close();
    infile.clear();
}

/**
 * Reads in file into the 2D vector
 */
void Robot::read(istream &in, vector<vector<double>> &v,
                 vector<double>::size_type size) {
    double number;

    while ((in >> number) != NULL) {
        vector<double> line;
        line.push_back(number);

        for (vector<double>::size_type i = 0; i < size - 1; i++) {
            in >> number;
            line.push_back(number);
        }
        v.push_back(line);
    }
}
