#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftT = motor(PORT10, ratio18_1, false);
motor LeftM = motor(PORT11, ratio18_1, false);
motor LeftD = motor(PORT7, ratio18_1, false);
motor RightT = motor(PORT21, ratio18_1, false);
motor RightM = motor(PORT4, ratio18_1, false);
motor RightD = motor(PORT1, ratio18_1, false);
digital_out Clamp1 = digital_out(Brain.ThreeWirePort.A);
digital_out Clamp2 = digital_out(Brain.ThreeWirePort.D);
digital_out pto = digital_out(Brain.ThreeWirePort.C);
motor RightE = motor(PORT20, ratio18_1, false);
motor LeftE = motor(PORT18, ratio18_1, false);
digital_out Clamp3 = digital_out(Brain.ThreeWirePort.B);

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