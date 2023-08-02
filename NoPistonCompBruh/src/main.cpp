/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LT                   motor         10              
// LD                   motor         11              
// RT                   motor         12              
// RD                   motor         13              
// Conv                 motor         14              
// Bar                  motor         15              
// CF                   motor         16              
// CB                   motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "automations.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  prime();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  prime();
  autonR();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  setDrivetrainStopping(coast);
  Conv.setStopping(brake);
  CF.setStopping(hold);
  CB.setStopping(hold);
  Bar.setStopping(hold);
  bool switched = true; //true if on match, otherwise false
  if (switched){
      CF.spin(reverse);
      CB.spin(reverse);
  }
  while (1) {
    double a1, a2;
    bool BD, BU, lock, CFU, CFD, CBU, CBD, CI, CO;
    a1 = Controller1.Axis1.value()/1.28;
    a2 = Controller1.Axis3.value()/1.28;
    BD = Controller1.ButtonL2.pressing();
    BU = Controller1.ButtonL1.pressing();
    CFU = Controller1.ButtonR1.pressing();
    CFD = Controller1.ButtonR2.pressing();
    CBU = Controller1.ButtonDown.pressing(); //NEED TO TEST
    CBD = Controller1.ButtonLeft.pressing();
    //CI = Controller1.ButtonUp.pressing();
    bool oldCI= false; //NEED TO TEST
    CI = false;
    if (Controller1.ButtonUp.pressing()){ //toggles trackI
      if (oldCI == false){
        CI = !CI;
      }
      oldCI = true;
    }
    else{
      oldCI = false;
    }
    CO = Controller1.ButtonRight.pressing();
    lock = Controller1.ButtonY.pressing();





    if (a1 != 0 and a2 != 0){
      spinDriveMotors(a2,a1);
    }
    else{
      stopDrive();
    }


    if(lock){
      setDrivetrainStopping(hold);
    }


    if(BD){
      Bar.spin(reverse,100,pct);
    }
    else if(BU){
      Bar.spin(fwd,100,pct);
    }
    else{
      Bar.stop();
    }


    if (CI){
      Conv.spin(fwd,100,pct);
    }
    if (CO){
      Conv.spin(reverse,100,pct);
    }
    else{
      Conv.stop();
    }


    if (CFU){
      CF.spin(fwd,100,pct);
    }
    else if (CFD){
      CF.spin(reverse,100,pct);
    }
    else if(Controller1.ButtonB.pressing()){
      //setFD();
    }
    else{
      CF.stop();
    }


    if (CBU){
      CB.spin(fwd,100,pct);
    }
    else if (CBD){
      CB.spin(reverse,100,pct);
    }
    else{
      CB.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
