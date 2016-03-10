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
     * TODO comment
     */
    double getX(const double &xr, const double &r, const double &alpha,
                const double &beta) {
        return xr + r * cos(alpha + beta);
    }

    /**
     * TODO comment
     */
    double getY(const double &yr, const double &r, const double &alpha,
                const double &beta) {
        return yr + r * sin(alpha + beta);
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
