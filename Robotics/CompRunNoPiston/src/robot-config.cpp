#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LT = motor(PORT10, ratio18_1, false);
motor LD = motor(PORT11, ratio18_1, true);
motor RT = motor(PORT12, ratio18_1, true);
motor RD = motor(PORT13, ratio18_1, false);
motor Conv = motor(PORT14, ratio18_1, false);
motor Bar = motor(PORT15, ratio18_1, false);
motor CF = motor(PORT16, ratio18_1, false);
motor CB = motor(PORT17, ratio18_1, false);

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