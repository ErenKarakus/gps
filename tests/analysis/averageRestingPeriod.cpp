#include <boost/test/unit_test.hpp>

#include "types.h"
#include "waypoints.h"
#include "analysis-track.h"
#include "gridworld-track.h"

using namespace GPS;


/* The Track::averageRestingPeriod() function provides the mean duration of the resting periods within the track.
 *
 * (A resting period is the sum of all adjacent rests.)
 * Throws a std::domain_error if the track contains no resting periods.
 * Throws a std::domain_error if the time elapsed between any two adjacent points during a
 * resting period is negative (but negative time while travelling will not trigger an exception).
 */

BOOST_AUTO_TEST_SUITE( Track_averageRestingPeriod )

const metres gridUnit = 1000;
const GridWorld::Model gwNearEquator {Earth::Pontianak,gridUnit,gridUnit,gridUnit};


/*
 * Typical
 */
BOOST_AUTO_TEST_CASE( AverageRestingPeriodOnlyRests )
{
    const std::vector<TrackPoint> trackPoints= GridWorld::Track("A1B2C3D4E", gwNearEquator).toTrackPoints();
    const metres restingRange = gridUnit;

    const Analysis::Track track{trackPoints, restingRange};

    std::chrono::seconds actualTime = track.travellingTime();
    std::chrono::seconds expectedOutcome (0);

    BOOST_CHECK_EQUAL(expectedOutcome.count(), actualTime.count());
}

BOOST_AUTO_TEST_CASE( AverageRestingPeriodNoRests )
{
    const std::vector<TrackPoint> trackPoints = GridWorld::Track("A1B2C3D4E", gwNearEquator).toTrackPoints();
    const metres restingRange = gridUnit;

    const Analysis::Track track {trackPoints, restingRange};

    std::chrono::seconds actualTime = track.travellingTime();
    const std::chrono::seconds expectedOutcome (12);

    BOOST_CHECK_EQUAL( expectedOutcome.count(), actualTime.count() );
}

/*
 * Edge
 */
BOOST_AUTO_TEST_CASE(SmallestAverageRestingPeriod)
{
    const std::vector<TrackPoint> trackPoints= GridWorld::Track("A", gwNearEquator).toTrackPoints();
    const metres restingRange = gridUnit;

    const Analysis::Track track{trackPoints, restingRange};
    std::chrono::seconds averageRestingPeriod = track.averageRestingPeriod();
    std::chrono::seconds expectedOutcome = std::chrono::seconds(0);


    BOOST_CHECK_EQUAL(averageRestingPeriod.count(),expectedOutcome.count());
}

/*
 *  Error Cases
 */
BOOST_AUTO_TEST_CASE( EmptyTrack )
{
    const std::vector<TrackPoint> trackPoints = GridWorld::Track("",gwNearEquator).toTrackPoints();
    const metres restingRange = gridUnit;
    const Analysis::Track track{trackPoints, restingRange};

    BOOST_CHECK_THROW(track.averageRestingPeriod().count(),std::domain_error);
}

BOOST_AUTO_TEST_CASE( ZeroTrack )
{
    const std::vector<TrackPoint> trackPoints = GridWorld::Track("A0B2C3D4E", gwNearEquator).toTrackPoints();
    const metres restingRange = 0;

    const Analysis::Track track{trackPoints, restingRange};

    BOOST_CHECK_THROW(track.averageRestingPeriod(), std::domain_error);
}

BOOST_AUTO_TEST_CASE( NegativeTrack )
{
    const std::vector<TrackPoint> trackPoints = GridWorld::Track("A-1B2C3D4E", gwNearEquator).toTrackPoints();
    const metres restingRange = 0;

    const Analysis::Track track{trackPoints, restingRange};

    BOOST_CHECK_THROW(track.averageRestingPeriod(), std::domain_error);
}

BOOST_AUTO_TEST_SUITE_END()
