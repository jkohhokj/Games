using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftFrontDrive;
extern motor LeftRearDrive;
extern motor RightFrontDrive;
extern motor RightRearDrive;
extern motor Forklift;
extern motor ClampF;
extern motor Bar;
extern motor ClampB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );