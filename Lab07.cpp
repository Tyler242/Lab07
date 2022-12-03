/*************************************************************
 * 1. Name:
 *      Caleb Rasmussen & Tyler Shellman
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      Biggest issue was probably the ground. The 
 *      getElevationMeters description is somewhat misleading.
 * 5. How long did it take for you to complete the assignment?
 *      Too long. Probably around 12 hours.
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POSITION
//#include "TestForce.h"
//#include "TestVelocity.h"
//#include "TestAcceleration.h"
#include "Simulator.h"
using namespace std;

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
   Simulator* simulator = (Simulator*)p;

   simulator->input(pUI);

   simulator->draw();
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
#include "TestForce.h"
#include "TestForce.h"
#include "TestVelocity.h"
#include "Velocity.h"
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
      "Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulator simulator(ptUpperRight);

   // set everything into action
   ui.run(callBack, &simulator);
    
    //TestForce testForce = TestForce();
    //testForce.run();
    //TestVelocity testVelocity = TestVelocity();
    //testVelocity.run();
    //TestAcceleration testAccel = TestAcceleration();
    //testAccel.run();
}
