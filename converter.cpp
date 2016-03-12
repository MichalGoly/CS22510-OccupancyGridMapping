#include "converter.h"

namespace converter {

    /**
     * Converts the specified number of degrees to radians.
     *
     * @param degrees The amount of degrees to convert
     * @return The converted amount of degrees in radians
     */
    double toRadians(const double &degrees) {
        return degrees * M_PI / 180;
    }

    /**
     * Calculates the absolute X coordinate of the obstacle based on the
     * horizontal position of the robot (xr), the range from the given
     * robot sensor to the obstacle, and the sum of alpha (angle of the sensor)
     * and beta (orientation of the robot itself) in radians.
     *
     * @param xr The horizontal position of the robot in metres
     * @param range The distance between the robot and the obstacle
     * @param alpha The angle of one of the 8 sensors in radians
     * @param beta The orientation of the robot in radians
     * @return The absolute X coordinate of the obstacle
     */
    double getX(const double &xr, const double &range, const double &alpha,
                const double &beta) {
        return xr + range * cos(alpha + beta);
    }

    /**
     * Calculates the absolute Y coordinate of the obstacle based on the
     * vertical position of the robot (yr), the range from the given
     * robot sensor to the obstacle, and the sum of alpha (angle of the sensor)
     * and beta (orientation of the robot itself) in radians.
     *
     * @param yr The vertical position of the robot in metres
     * @param range The distance between the robot and the obstacle
     * @param alpha The angle of one of the 8 sensors in radians
     * @param beta The orientation of the robot in radians
     * @return The absolute Y coordinate of the obstacle
     */
    double getY(const double &yr, const double &range, const double &alpha,
                const double &beta) {
        return yr + range * sin(alpha + beta);
    }

    /**
     * Converts the specified position (in meters) into the corresponding
     * index in the grid. This functions works with both x and y coordinates
     * and takes into the account the 0.1m offset when calculating the
     * required index.
     *
     * @param position The vertical or horizontal position of an obstacle in meters
     * @return The index in the 50x50 grid corresponding to the provided position
     */
    int toCellIndex(const double &position) {
        double offset = 0.1;
        double cellWidth = 0.2;
        return (int) ((position + offset) / cellWidth);
    }

}
