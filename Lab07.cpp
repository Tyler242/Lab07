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
using namespace std;

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
vector<double> airDensityVector{
    0,
    1000,
    2000,
    3000,
    4000,
    5000,
    6000,
    7000,
    8000,
    9000,
    10000,
    15000,
    20000,
    25000,
    30000,
    40000,
    50000,
    60000,
    70000,
    80000
};

double computeAirResistance() {
    return 0;
}

double linearInterpolation(double d0, double r0, double d1, double r1, double d) {
    // (r - r0)/(d - d0) = (r1 - r0)/(d1 - d0)
    // r - r0 = ((r1 - r0)*(d - d0))/(d1 - d0)
    // r = ((r1 - r0)*(d - d0))/(d1 - d0) + r0
    return ((r1 - r0)*(d - d0))/(d1 - d0) + r0;
}
double computeAirDensity(double altitude) {
    assert(!(altitude > 80000));
    double upperAlt;
    double lowerAlt;
    int lengthAirDensity = airDensityVector.size();
    bool found = false;
    int index = 0;

    if (altitude < 1000 && altitude > 0) {
        upperAlt = 1000;
        lowerAlt = 1000;
    }
    else if (altitude >= 1000 && altitude < 10000) {
        int intermediateVal = altitude / 1000;
        lowerAlt = intermediateVal * 1000;
        upperAlt = lowerAlt + 1000;
    }
    else if (altitude >= 10000 && altitude < 30000) {
        if (altitude >= 10000 && altitude < 15000) {
            lowerAlt = 10000;
            upperAlt = 15000;
        }
        else if (altitude >= 15000 && altitude < 20000) {
            lowerAlt = 15000;
            upperAlt = 20000;
        }
        else if (altitude >= 20000 && altitude < 25000) {
            lowerAlt = 20000;
            upperAlt = 25000;
        }
        else {
            lowerAlt = 25000;
            upperAlt = 30000;
        }
    }
    cout << lowerAlt << endl;
    cout << upperAlt << endl;
    return 0;


    //while (index < lengthAirDensity && !found) {
    //    if (altitude == airDensityVector[index]) {
    //        lowerAlt = airDensityVector[index];
    //        upperAlt = airDensityVector[index];
    //        found = true;
    //    }
    //    else if (altitude > airDensityVector[index]
    //        && altitude < airDensityVector[index + 1]) {
    //        lowerAlt = airDensityVector[index];
    //        upperAlt = airDensityVector[index + 1];
    //        found = true;
    //    }
    //    else
    //        index++;
    //}
    //assert(upperAlt <= 80000 && upperAlt >= 1000);
    //assert(lowerAlt <= 70000 && lowerAlt >= 0);

    //return linearInterpolation(
    //    lowerAlt,
    //    airDensityMap[lowerAlt],
    //    upperAlt,
    //    airDensityMap[upperAlt],
    //    altitude
    //);
}


double convertMeterSecToMach(double speed, double altitude) {
    return 0;
}

double computeDragCoefficient() {
    return 0;
}

double computeAreaCircle(double radius) {
    return (radius * radius * 3.14159);
}

double computeAcceleration(double force, double mass) {
    return force / mass;
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
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);
    
    //double angle;
    //cout << "What is the angle of the howitzer where 0 is up? ";
    //cin >> angle;
    //cout << computeAirDensity(angle) << endl;


   return 0;
}
