#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftFrontDrive = motor(PORT1, ratio18_1, false);
motor LeftRearDrive = motor(PORT20, ratio18_1, false);
motor RightFrontDrive = motor(PORT8, ratio18_1, false);
motor RightRearDrive = motor(PORT19, ratio18_1, false);
motor Forklift = motor(PORT7, ratio18_1, true);
motor ClampF = motor(PORT5, ratio36_1, false);
motor Bar = motor(PORT12, ratio36_1, true);
motor ClampB = motor(PORT9, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}