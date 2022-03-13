#include <cassert>
#include <stdexcept>

#include "geometry.h"

#include "analysis-track.h"

using std::chrono::seconds;
using std::chrono::duration_cast;

namespace GPS::Analysis
{

///////////////////////////////////////////////////////////////////////////////

Track::Track(std::vector<TrackPoint> trackPoints, metres restingRange)
    : Route{trackPointsToRoutePoints(trackPoints)},
      timeStamps{trackPointsToTimeStamps(trackPoints)},
      restingRange{restingRange}
{
    assert (routePoints.size() == timeStamps.size());
}

///////////////////////////////////////////////////////////////////////////////

void Track::setRestingRange(metres newRestingRange)
{
    restingRange = newRestingRange;
}

///////////////////////////////////////////////////////////////////////////////

seconds Track::totalTime() const
{
    if (timeStamps.empty()) throw std::domain_error("Cannot compute the duration time of an empty track.");

    if (timeStamps.back() < timeStamps.front()) throw std::domain_error("Track takes negative time duration overall.");

    return duration_cast<seconds>(timeStamps.back() - timeStamps.front());
}

seconds Track::restingTime() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

seconds Track::travellingTime() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

seconds Track::longestRestingPeriod() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

std::chrono::seconds Track::longestTravellingPeriod() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

seconds Track::averageRestingPeriod() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

seconds Track::averageTravellingPeriod() const
{
    // Stub definition, needs implementing
    return seconds::zero();
}

speed Track::maxSpeed() const
{
    // Stub definition, needs implementing
    return 0;
}

speed Track::averageSpeed() const
{
    // Stub definition, needs implementing
    return 0;
}

speed Track::averageTravellingSpeed() const
{
    // Stub definition, needs implementing
    return 0;
}

speed Track::maxRateOfAscent() const
{
    // Stub definition, needs implementing
    return 0;
}

speed Track::maxRateOfDescent() const
{
    // Stub definition, needs implementing
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

std::vector<RoutePoint> Track::trackPointsToRoutePoints(std::vector<TrackPoint> trackPoints)
{
    std::vector<RoutePoint> routePoints;
    routePoints.reserve(trackPoints.size());

    for (const TrackPoint& trackPoint : trackPoints)
    {
        routePoints.push_back({trackPoint.position,trackPoint.name});
    }

    return routePoints;
}

std::vector<Track::TimeStamp> Track::trackPointsToTimeStamps(std::vector<TrackPoint> trackPoints)
{
    std::vector<TimeStamp> timeStamps;
    timeStamps.reserve(trackPoints.size());

    for (const TrackPoint& trackPoint : trackPoints)
    {
        timeStamps.push_back(tmToTimeStamp(trackPoint.dateTime));
    }

    return timeStamps;
}

bool Track::withinRestingRange(RoutePoint pt1, RoutePoint pt2) const
{
    metres horizontalDifference = Position::horizontalDistanceBetween(pt1.position,pt2.position);
    metres verticalDifference = pt2.position.elevation() - pt1.position.elevation();
    metres distance = pythagoras(horizontalDifference,verticalDifference);
    return (distance < restingRange);
}

Track::TimeStamp Track::tmToTimeStamp(std::tm dateTime)
{
    return std::chrono::system_clock::from_time_t(std::mktime(&dateTime));
}

///////////////////////////////////////////////////////////////////////////////

}
