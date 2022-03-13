#include <stdexcept>

#include "earth.h"
#include "geometry.h"

#include "analysis-route.h"

namespace GPS::Analysis
{

///////////////////////////////////////////////////////////////////////////////

Route::Route(std::vector<RoutePoint> routePoints)
    : routePoints{routePoints}
{}

///////////////////////////////////////////////////////////////////////////////

unsigned int Route::numPoints() const
{
    // Stub definition, needs implementing
    return 0;
}

metres Route::totalLength() const
{
    if (routePoints.empty()) throw std::domain_error("Cannot compute the length of an empty route.");

    metres lengthSoFar = 0;

    for (unsigned int current = 0, next = 1; next < routePoints.size() ; ++current, ++next)
    {
        metres horizontalDifference = Position::horizontalDistanceBetween(routePoints[current].position, routePoints[next].position);
        metres verticalDifference = routePoints[next].position.elevation() - routePoints[current].position.elevation();
        lengthSoFar += pythagoras(horizontalDifference,verticalDifference);
    }

    return lengthSoFar;
}

metres Route::netLength() const
{
    // Stub definition, needs implementing
    return 0;
}

metres Route::totalHeightGain() const
{
    // Stub definition, needs implementing
    return 0;
}

metres Route::netHeightGain() const
{
    // Stub definition, needs implementing
    return 0;
}

degrees Route::maxGradient() const
{
    // Stub definition, needs implementing
    return 0;
}

degrees Route::minGradient() const
{
    // Stub definition, needs implementing
    return 0;
}

degrees Route::steepestGradient() const
{
    // Stub definition, needs implementing
    return 0;
}

RoutePoint Route::highestPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::lowestPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::mostNorthelyPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::mostSoutherlyPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::mostEasterlyPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::mostWesterlyPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::mostEquatorialPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::leastEquatorialPoint() const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::nearestPointTo(Position) const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

RoutePoint Route::farthestPointFrom(Position) const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

unsigned int Route::numPointsNear(Position, metres) const
{
    // Stub definition, needs implementing
    return 0;
}

unsigned int Route::timesVisited(std::string) const
{
    // Stub definition, needs implementing
    return 0;
}

Position Route::findPosition(std::string) const
{
    // Stub definition, needs implementing
    return Earth::CliftonCampus;
}

RoutePoint Route::operator[](unsigned int) const
{
    // Stub definition, needs implementing
    return RoutePoint{ Earth::CliftonCampus, "Clifton Campus" };
}

///////////////////////////////////////////////////////////////////////////////

}
