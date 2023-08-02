/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jkohh                                            */
/*    Created:      Wed Sep 29 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontDrive       motor         1               
// LeftRearDrive        motor         20              
// RightFrontDrive      motor         8               
// RightRearDrive       motor         19              
// Forklift             motor         7               
// ClampF               motor         5               
// Bar                  motor         12              
// ClampB               motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "automations.h"
using namespace vex;


//wheels move stuff
int main() {
  vexcodeInit();
  setDrivetrainStopping();
  double vert, hori, hori2, vert2;
  bool ForkliftUp, ForkliftDown, BarUp, BarDown, clampUpF, clampDownF, clampUpB, clampDownB, lock;
  void(0);
  prog();
  while (true){
    hori = Controller1.Axis4.value();
    vert = Controller1.Axis3.value();
    hori2 = -1*Controller1.Axis1.value();
    vert2 = Controller1.Axis2.value();
    ForkliftUp = Controller1.ButtonL2.pressing();
    ForkliftDown = Controller1.ButtonL1.pressing();
    BarUp = Controller1.ButtonR1.pressing();
    BarDown = Controller1.ButtonR2.pressing();
    clampUpF = Controller1.ButtonY.pressing();
    clampDownF = Controller1.ButtonX.pressing();
    clampUpB = Controller1.ButtonA.pressing();
    clampDownB = Controller1.ButtonB.pressing();
    lock = Controller1.ButtonRight.pressing();
    if (vert != 0 or hori != 0){
      spinDriveMotors(vert, hori);
    }
    else if (vert2 != 0 or hori2 != 0){
      spinDriveMotorsI(vert2, hori2);
    }
    else if (Controller1.ButtonUp.pressing()){
      RightFrontDrive.spin(vex::directionType::rev , 100 , velocityUnits::pct);
    }
    else if (Controller1.ButtonDown.pressing()){
      RightRearDrive.spin(vex::directionType::rev , 100 , velocityUnits::pct);
    }
    else{
      LeftFrontDrive.stop();
      LeftRearDrive.stop();
      RightFrontDrive.stop();
      RightRearDrive.stop();
    }

    if (ForkliftUp){
      Forklift.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
    }
    else if (ForkliftDown){
      Forklift.spin(vex::directionType::rev , 100 , velocityUnits::pct);
    }
    else{
      Forklift.stop();
    }
    if (BarUp){
      Bar.spin(vex::directionType::fwd , 100, velocityUnits::pct);
    }
    else if (BarDown){
      Bar.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
    }
    else{
      Bar.stop();
    }
    if (clampUpF){
      ClampF.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
    }
    else if (clampDownF){
      ClampF.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
    }
    else{
      ClampF.stop();
    }
    if (clampUpB){
      ClampB.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
    }
    else if (clampDownB){
      ClampB.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
    }
    else{
      ClampB.stop();
    }
    if (Controller1.ButtonLeft.pressing()){
      pForkliftUp();
    }
    if (lock){
      LeftRearDrive.setStopping(hold);
      LeftFrontDrive.setStopping(hold);
      RightRearDrive.setStopping(hold);
      RightFrontDrive.setStopping(hold);
    }
    else{
      LeftRearDrive.setStopping(coast);
      LeftFrontDrive.setStopping(coast);
      RightRearDrive.setStopping(coast);
      RightFrontDrive.setStopping(coast); 
    }
  }
}
