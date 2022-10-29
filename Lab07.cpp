/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POSITION
#include <map>
#include <vector>
#include <cmath>
using namespace std;

#define PI       3.14159

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(0.0),
      angle(0.0)
   {
      // Set the horizontal position of the howitzer. This should be random.
      ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer);

      // This is to make the bullet travel across the screen. Notice how there are 
      // 20 pixels, each with a different age. This gives the appearance
      // of a trail that fades off in the distance.
      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX((double)i * 2.0);
         projectilePath[i].setPixelsY(ptUpperRight.getPixelsY() / 1.5);
      }
   }

   Ground ground;                 // the ground
   Position  projectilePath[20];  // path of the projectile
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   double angle;                  // angle of the howitzer 
   double time;                   // amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //

   // move a large amount
   if (pUI->isRight())
      pDemo->angle += 0.05;
   if (pUI->isLeft())
      pDemo->angle -= 0.05;

   // move by a little
   if (pUI->isUp())
      pDemo->angle += (pDemo->angle >= 0 ? -0.003 : 0.003);
   if (pUI->isDown())
      pDemo->angle += (pDemo->angle >= 0 ? 0.003 : -0.003);

   // fire that gun
   if (pUI->isSpace())
      pDemo->time = 0.0;

   //
   // perform all the game logic
   //

   // advance time by half a second.
   pDemo->time += 0.5;

   // move the projectile across the screen
   for (int i = 0; i < 20; i++)
   {
      // this bullet is moving left at 1 pixel per frame
      double x = pDemo->projectilePath[i].getPixelsX();
      x -= 1.0;
      if (x < 0)
         x = pDemo->ptUpperRight.getPixelsX();
      pDemo->projectilePath[i].setPixelsX(x);
   }

   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->ptHowitzer, pDemo->angle, pDemo->time);

   // draw the projectile
   for (int i = 0; i < 20; i++)
      gout.drawProjectile(pDemo->projectilePath[i], 0.5 * (double)i);

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout << "Time since the bullet was fired: "
        << pDemo->time << "s\n";
}

double Position::metersFromPixels = 40.0;

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
map<double, double> altSpeedSoundMap{
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
map<double, double> altGravity{
    {0,9.807},
    {1000,9.804},
    {2000,9.801},
    {3000,9.797},
    {4000,9.794},
    {5000,9.791},
    {6000,9.788},
    {7000,9.785},
    {8000,9.782},
    {9000,9.779},
    {10000,9.776},
    {15000,9.761},
    {20000,9.745},
    {25000,9.730}
};


double linearInterpolation(double d0, double r0, double d1, double r1, double d) {
    // (r - r0)/(d - d0) = (r1 - r0)/(d1 - d0)
    // r - r0 = ((r1 - r0)*(d - d0))/(d1 - d0)
    // r = ((r1 - r0)*(d - d0))/(d1 - d0) + r0
    return ((r1 - r0)*(d - d0))/(d1 - d0) + r0;
}

void findUpperLowerBound(double value, double& upper, double& lower, double max, double min) {
    if (value < 1000 && value >= min) {
        upper = 1000;
        lower = min;
    }
    else if (value >= 1000 && value < 10000) {
        int intermediateVal = value / 1000;
        lower = intermediateVal * 1000;
        upper = lower + 1000;
    }
    else if (value >= 10000 && value < 30000) {
        if (value >= 10000 && value < 15000) {
            lower = 10000;
            upper = 15000;
        }
        else if (value >= 15000 && value < 20000) {
            lower = 15000;
            upper = 20000;
        }
        else if (value >= 20000 && value < 25000) {
            lower = 20000;
            upper = 25000;
        }
        else {
            if (max > 25000) {
                lower = 25000;
                upper = 30000;
            }
            else {
                lower = 20000;
                upper = 25000;
            }
        }
    }
    else if (value >= 30000 && value <= max) {
        if (value == max) {
            lower = max - (max == 25000 ? 5000 : 10000);
            upper = max;
        }
        else {
            int intermediateVal = value / 10000;
            lower = intermediateVal * 10000;
            upper = lower + 10000;
        }
    }
}

/********************************************************
 * COMPUTE AIR DENSITY
 * Computes the air density based on an altitude
 ********************************************************/
double computeAirDensity(double altitude) {
    assert(!(altitude > 25000));
    double upperAlt;
    double lowerAlt;

    findUpperLowerBound(altitude, upperAlt, lowerAlt, 80000, 0);

    //cout << lowerAlt << endl;
    //cout << upperAlt << endl;

    assert(upperAlt <= 80000 && upperAlt >= 1000);
    assert(lowerAlt <= 70000 && lowerAlt >= 0);

    return linearInterpolation(
        lowerAlt,
        airDensityMap[lowerAlt],
        upperAlt,
        airDensityMap[upperAlt],
        altitude
    );
}

/********************************************************
 * COMPUTE SPEED OF SOUND
 * Computes the speed of sound based on an altitude
 ********************************************************/
double computeSpeedOfSound(double altitude) {
    assert(altitude <= 25000);
    double upperAlt;
    double lowerAlt;

    findUpperLowerBound(altitude, upperAlt, lowerAlt, 40000, 0);

    //cout << lowerAlt << endl;
    //cout << upperAlt << endl;
    
    assert(upperAlt <= 40000 && upperAlt >= 1000);
    assert(lowerAlt <= 30000 && lowerAlt >= 0);

    return linearInterpolation(
        lowerAlt,
        altSpeedSoundMap[lowerAlt],
        upperAlt,
        altSpeedSoundMap[upperAlt],
        altitude
        );
}

/********************************************************
 * COMPUTE GRAVITY
 * Computes the gravity based on an altitude
 ********************************************************/
double computeGravity(double altitude) {
    assert(altitude <= 25000);
    double upperAlt;
    double lowerAlt;

    findUpperLowerBound(altitude, upperAlt, lowerAlt, 25000, 0);

    //cout << lowerAlt << endl;
    //cout << upperAlt << endl;
    
    assert(upperAlt <= 25000 && upperAlt >= 1000);
    assert(lowerAlt <= 20000 && lowerAlt >= 0);

    return linearInterpolation(
        lowerAlt,
        altGravity[lowerAlt],
        upperAlt,
        altGravity[upperAlt],
        altitude
    );
}

/********************************************************
 * DEGREES TO RADIANS
 * Computes the drag coefficient based off of mach
 ********************************************************/
double degreesToRadians(const double degrees) {
    double radians;
    radians = (degrees / 360) * (2 * PI);

    return radians;
}


/********************************************************
 * COMPUTE DRAG COEFFICIENT
 * Computes the drag coefficient based off of mach
 ********************************************************/
double computeDragCoefficient( double mach) {
    assert(!(mach > 5.00));

    // mach, dragCoefficient
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

    double dragCoefficient = -1;
    if (mach < 0.300) {
        dragCoefficient = dragCoefficientMap[0.300];
        return dragCoefficient;
    }


    //Loop through machs in dragCoefficientMap until dragCoefficient is set
    for (auto it = dragCoefficientMap.begin(); it != dragCoefficientMap.end() && dragCoefficient == -1; it++)
    {
        if (mach == it->first) {
            dragCoefficient = it->second;
            return dragCoefficient;
        }
        else if (mach < it->first) {
            double d1 = it->first;
            double r1 = it->second;

            // last element
            it--;
            double d0 = it->first;
            double r0 = it->second;

            dragCoefficient = linearInterpolation(d0, r0, d1, r1, mach);
            return dragCoefficient;
        }
        assert(it->first <= 5);
    };

    return dragCoefficient;
}

double computeAreaCircle(double radius) {
    return (radius * radius * PI);
}

double computeDragForce(double altitude, double v) {
    try {
        double mach = computeSpeedOfSound(altitude);

        double c = computeDragCoefficient(v / mach);
        double p = computeAirDensity(altitude);
        double a = computeAreaCircle(154.89 / 2000);
        return 0.5 * c * p * (v * v) * a;
    } 
    catch (exception ex) {
        cout << "error" << endl;
    }
}

double computeAcceleration(double force, double mass) {
    return force / mass;
}

double getAcceleration(double altitude, double v) {
    double dragForce = computeDragForce(altitude, v);

    return computeAcceleration(dragForce, 46.7);
}

double computeDyComponent(double v, double angle) {
    return v * cos(angle);
}

double computeDxComponent(double v, double angle) {
    return v * sin(angle);
}

double angleFromComponents(double dx, double dy) {
    return atan2(dy, dx);
}

double getTotalComponent(double dx, double dy) {
    return sqrt((dx * dx) + (dy * dy));
}

double computeVComponent(double v, double a, double t) {
    return v + a * t;
}

double computePosition(double v, double a, double t) {
    return (v * t) + (0.5 * a * t * t);
}
/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   //Position ptUpperRight;
   //ptUpperRight.setPixelsX(700.0);
   //ptUpperRight.setPixelsY(500.0);
   //Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   //Interface ui(0, NULL,
   //   "Demo",   /* name on the window */
   //   ptUpperRight);

   //// Initialize the demo
   //Demo demo(ptUpperRight);

   //// set everything into action
   //ui.run(callBack, &demo);
    
    // Get angle from user
    double angle;
    cout << "What is the angle of the howitzer where 0 is up? ";
    cin >> angle;
    angle = degreesToRadians(angle);

    // Init variables
    Position position = Position();
    double distance = -1;
    double hangTime = 0;
    double t = 0.01;

    double v = 827;
    double ddx;
    double ddy;
    double dy = computeDyComponent(v, angle);
    double dx = computeDxComponent(v, angle);
    double prX;
    double prY;
    do {
        try {
            // get acceleration
            assert(position.getMetersY() <= 25000);
            double dragAccel = getAcceleration(position.getMetersY(), v);

            ddx = -computeDxComponent(dragAccel, angle);
            ddy = -computeDyComponent(dragAccel, angle) - computeGravity(position.getMetersY());
            // get->update position
            prX = position.getMetersX();
            prY = position.getMetersY();
            position.addMetersX(computePosition(dx, ddx, t));
            position.addMetersY(computePosition(dy, ddy, t));
            // get->update velocity
            dx = computeVComponent(dx, ddx, t);
            dy = computeVComponent(dy, ddy, t);
            v = getTotalComponent(dx, dy);
            // update the angle (direction of projectile)
            hangTime += 0.01;
        }
        catch (exception ex) {
            cout << "error in main loop" << endl;
        }
    }
    while (position.getMetersY() > 0);

    if (position.getMetersY() != 0)
        distance = linearInterpolation(prY, prX, position.getMetersY(), position.getMetersX(), 0);
    else
        distance = position.getMetersX();

   cout << "Distance:      " << distance << "m       Hang Time:      " << hangTime << endl;
   return 0;
}
