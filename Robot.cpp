#include "Robot.h"
#include <fstream>
#include <stdexcept>

using std::istream;
using std::string;
using std::ifstream;
using std::domain_error;

const string Robot::POSES_FILE = "includes/poses.txt";
const string Robot::RANGES_FILE = "includes/ranges.txt";

/**
 * Constructs the Robot object which represents a robot crawling the grid
 * in the system. This object is initialised by reading in the poses and
 * ranges data from the txt source files provided, and storing them
 * in 2D vectors internally. Furthermore, a robot have 8 proximity
 * sensors which point at different directions. These directions are
 * represented as angles and stored internally in an appropriate vector.
 *
 * The poses, ranges and sensorAngles vectors are accessible using the
 * getters provided.
 *
 */
Robot::Robot() {
    readInData();
    sensorAngles = {0, 45, 90, 135, 180, 225, 270, 315};
}

/**
 * @return The 2D vector holding the poses read from the source file.
 */
const std::vector<std::vector<double>> &Robot::getPoses() const {
    return poses;
}

/**
 * @return The 2D vector holding the ranges read from the source file.
 */
const std::vector<std::vector<double>> &Robot::getRanges() const {
    return ranges;
}

/**
 * @return The vector of 8 angles of each sensor of the robot.
 */
const std::vector<double> &Robot::getSensorAngles() const {
    return sensorAngles;
}

/*
 * Reads in poses and ranges source files and stores them in the
 * internal 2D vectors of appropriate size.
 *
 * @throws An appropriate domain error if one of the files fails to open
 */
void Robot::readInData() {
    ifstream infile(POSES_FILE);

    if (!infile.good()) {
        throw domain_error("IO error: unable to open the poses.txt file");
    }
    read(infile, poses, 3);
    infile.close();
    infile.clear();

    infile.open(RANGES_FILE);

    if (!infile.good()) {
        throw domain_error("IO error: unable to open the ranges.txt file");
    }
    read(infile, ranges, 8);
    infile.close();
    infile.clear();
}

/**
 * Reads in the data from the specified input stream and stores it
 * in the 2D vector provided. This function works for both the ranges.txt
 * and poses.txt due to the common format of the two files. The only difference
 * is the number of values per line which can be specified by passing the
 * appropriate size argument.
 *
 * @param in The input stream to the file from which the data will be read
 * @param v The 2D vector to store the read data in
 * @param size The amount of values on each line in the input file
 */
void Robot::read(istream &in, std::vector<std::vector<double>> &v,
                 std::vector<double>::size_type size) {
    double number;

    while ((in >> number) != NULL) {
        std::vector<double> line;
        line.push_back(number);

        for (std::vector<double>::size_type i = 0; i < size - 1; i++) {
            in >> number;
            line.push_back(number);
        }
        v.push_back(line);
    }
}
