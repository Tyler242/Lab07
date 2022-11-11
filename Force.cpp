#include <cassert>
#include "Force.h"

Force::Force()
{
	force = 0;
}

void Force::computeForce(const double altitude, const double velocity)
{
	double mach = computeSpeedOfSound(altitude);
	double speed = velocity / mach;
	
	double dragCoef = computeDragCoef(speed);
	
	double airDensity = computeAirDensity(altitude);
	
	double projectileRadius = 154.89 / 1000 / 2;
	double area = projectileRadius * projectileRadius * 3.14159;

	force = 0.5 * dragCoef * airDensity * velocity * velocity * area;
}

double Force::computeSpeedOfSound(const double altitude) {
    assert(altitude <= 40000 && altitude >= 0);

    map<double, double> speedSoundMap{
        {0,340},
        {1000,336},
        {2000,332},
        {3000,328},
        {4000,324},
        {5000,320},
        {6000,316},
        {7000,312},
        {8000,308},
        {9000,303},
        {10000,299},
        {15000,295},
        {20000,295},
        {25000,295},
        {30000,305},
        {40000,324},
    };

    double speedOfSound = MapReader().getMapValue(altitude, speedSoundMap);
    assert(speedOfSound != -1, "Unable to find value");
    assert(speedOfSound > 0, "Value too low");

    return speedOfSound;
}

double Force::computeDragCoef(const double speed) {
    assert(speed <= 5 && speed >= 0.3);

    map<double, double> dragCoefficientMap{
        {0.300, 0.1629},
        {0.500, 0.1659},
        {0.700, 0.2031},
        {0.890, 0.2597},
        {0.920, 0.3010},
        {0.960, 0.3287},
        {0.980, 0.4002},
        {1.000, 0.4258},
        {1.020, 0.4335},
        {1.060, 0.4483},
        {1.240, 0.4064},
        {1.530, 0.3663},
        {1.990, 0.2897},
        {2.870, 0.2297},
        {2.890, 0.2306},
        {5.000, 0.2656}
    };

    double dragCoef = MapReader().getMapValue(speed, dragCoefficientMap);
    assert(dragCoef != -1, "Unable to find value");
    assert(dragCoef > 0, "Value too low");

    return dragCoef;
}

double Force::computeAirDensity(const double altitude) {
    assert(altitude <= 80000 && altitude >= 0);

    map<double, double> airDensityMap{
        //altitude : density
        {0, 1.2250000},
        {1000, 1.1120000},
        {2000, 1.0070000},
        {3000, 0.9093000},
        {4000, 0.8194000},
        {5000, 0.7364000},
        {6000, 0.6601000},
        {7000, 0.5900000},
        {8000, 0.5258000},
        {9000, 0.4671000},
        {10000, 0.4135000},
        {15000, 0.1948000},
        {20000, 0.0889100},
        {25000, 0.0400800},
        {30000, 0.0184100},
        {40000, 0.0039960},
        {50000, 0.0010270},
        {60000, 0.0003097},
        {70000, 0.0000828},
        {80000, 0.0000185}
    };

    double airDensity = MapReader().getMapValue(altitude, airDensityMap);
    assert(airDensity != -1, "Unable to find value");
    assert(airDensity > 0, "Value too low");

    return airDensity;
}
