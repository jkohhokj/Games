#include "vex.h"
#include <stdlib.h>
using namespace vex;

void spinDriveMotors (double a3, double a1){ //controls drivetrainmovement.
  LeftFrontDrive.spin(vex::directionType::fwd , (a3 + a1) , velocityUnits::pct);
  LeftRearDrive.spin(vex::directionType::fwd , (a3 + a1) , velocityUnits::pct);
  RightFrontDrive.spin(vex::directionType::fwd , (a1 - a3) , velocityUnits::pct);
  RightRearDrive.spin(vex::directionType::fwd , (a1 - a3) , velocityUnits::pct);
}
void spinDriveMotorsI (double a3, double a1){ //controls drivetrainmovement.
  LeftFrontDrive.spin(vex::directionType::rev , (a3 + a1) , velocityUnits::pct);
  LeftRearDrive.spin(vex::directionType::rev , (a3 + a1) , velocityUnits::pct);
  RightFrontDrive.spin(vex::directionType::rev , (a1 - a3) , velocityUnits::pct);
  RightRearDrive.spin(vex::directionType::rev , (a1 - a3) , velocityUnits::pct);
}
void spinDriveMotorsC (double a1, double a3, double velo=100, bool noDrift=false){ //spinDriveMotors Custom
  int max = abs((int) a1) + abs((int) a3);
  LeftFrontDrive.spinFor((a3 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  LeftRearDrive.spinFor((a3 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  RightFrontDrive.spinFor((a3 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  RightRearDrive.spinFor((a3 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct); //add timing
}
void spinDriveMotorsRL (double r, double l, double velo=100, bool noDrift=true){ //spinDriveMotors Custom
  LeftFrontDrive.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  LeftRearDrive.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RightFrontDrive.spinFor(-r, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RightRearDrive.spinFor(-r, rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift); //add timing
}
void setDrivetrainStopping(){ //coast, brake, halt
  LeftRearDrive.setStopping(brake);
  LeftFrontDrive.setStopping(brake);
  RightRearDrive.setStopping(brake);
  RightFrontDrive.setStopping(brake);
  Forklift.setStopping(hold);
  ClampF.setStopping(hold);
  Bar.setStopping(hold);
  ClampB.setStopping(hold);
}