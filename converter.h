#ifndef OCCUPANCYGRID_CONVERTER_H
#define OCCUPANCYGRID_CONVERTER_H

#include <math.h>

namespace converter {
    double toRadians(const double &degrees);

    double getX(const double &xr, const double &range, const double &alpha,
                const double &beta);

    double getY(const double &yr, const double &range, const double &alpha,
                const double &beta);

    int toCellIndex(const double &position);
}

#endif //OCCUPANCYGRID_CONVERTER_H
