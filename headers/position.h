#ifndef GPS_POSITION_H
#define GPS_POSITION_H

#include <string>

#include "types.h"

namespace GPS
{
  class Position
  {
    public:

      /* Construct a Position from degrees latitude, degrees longitude, and elevation in metres.
       *
       * Throws a std::invalid_argument exception for invalid latitude and longitude values.
       */
      Position(degrees lat, degrees lon, metres ele);


      /* Construct a Position from strings containing a DDM (degrees and decimal minutes)
       * representation of latitude and longitude, with 'N'/'S' and 'E'/'W' characters to
       * indicate bearing (positive or negative), and elevation in metres.
       *
       * Throws a std::invalid_argument exception for invalid latitude and longitude values.
       */
      Position(std::string ddmLatStr, char latBearing,
               std::string ddmLonStr, char lonBearing,
               std::string eleStr);

      degrees latitude() const;
      degrees longitude() const;
      metres  elevation() const;

      /* Computes an approximation of the horizontal distance between two Positions on the
       * Earth's surface. Does NOT take into account elevation.
       */
      static metres horizontalDistanceBetween(Position, Position);

    private:
      degrees lat;
      degrees lon;
      metres  ele;
  };

  /* Convert a DDM (degrees and decimal minutes) string representation of an angle to a
   * numeric DD (decimal degrees) value.
   */
  degrees ddmTodd(std::string);
}

#endif
