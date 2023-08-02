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
// LeftT                motor         10              
// LeftM                motor         11              
// LeftD                motor         7               
// RightT               motor         21              
// RightM               motor         4               
// RightD               motor         1               
// Clamp1               digital_out   A               
// Clamp2               digital_out   D               
// pto                  digital_out   C               
// RightE               motor         20              
// LeftE                motor         18              
// Clamp3               digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "automations.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
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
  preauton();
}

void autonomous(void) {
  //setDrivetrainStopping();
  //vex::task t = caller();

  //pto.set(false);
  autonL();
}

void usercontrol(void) {
  //broken ports: 9, 6
  vexcodeInit();
  setDrivetrainStopping(coast,true);
  LeftE.setStopping(hold);
  RightE.setStopping(hold);
  bool oldUp = false;
  bool oldRight = false;
  bool oldR1 = false;
  bool oldR2 = false;
  bool oldX = false;
  //bool ptoV = false; //on = 8m drive, off = 6m drive

  bool trackI = false;
  bool trackO = false;
  //Clamp = vex::pneumatics("A");
  RightE.setStopping(hold);
  LeftE.setStopping(hold);
  printf("\n\n\n\n");
  
  while (true){

    //Up = Track Conveyor Toggle In
    //Right = Track Converyor Toggle Out
    //L1, L2 = 4Bar
    //Right Joystick = Movement
    //R1 = Clamp1 Toggle
    //R2 = Clamp2 Toggle 
    //Y = lock
    //X = ptoV Toggle


    //old + new 
    //on + on = off
    //on + off = off
    //off + on = on
    //off + off = off
    double a1 = Controller1.Axis1.value()/1.28;
    //double a2 = Controller1.Axis2.value()/1.28;
    double a2 = Controller1.Axis3.value()/1.28;
    // double a4 = Controller1.Axis4.value();
    bool BarDown = Controller1.ButtonL2.pressing();
    bool BarUp = Controller1.ButtonL1.pressing();
    bool lock = Controller1.ButtonY.pressing();
    double avgEff = (LeftT.efficiency() + LeftM.efficiency() + LeftD.efficiency() + RightT.efficiency() + RightM.efficiency() + RightD.efficiency())/6;
    double avgTemp = (LeftT.temperature(celsius) + LeftM.temperature(celsius) + LeftD.temperature(celsius) + RightT.temperature(celsius) + RightM.temperature(celsius) + RightD.temperature(celsius))/6;
    double avgVelo = (LeftT.velocity(pct) + LeftM.velocity(pct) + LeftD.velocity(pct) + RightT.velocity(pct) + RightM.velocity(pct) + RightD.velocity(pct))/6;
    char panik[] = "";
    int max = 0;
    vex::task t = caller();
    t.stop();
    vex::motor SixM[6] = {LeftT, LeftM, LeftD, RightT, RightM, RightD};
    for (int i=0; i < 6; i++){
      if (SixM[i].temperature(celsius) > max){
        max = SixM[i].temperature(celsius);
      }
      if (SixM[i].temperature(celsius) > 50){
        std::strcat(panik, "HOT");
      }
    }
    bool ptoV = true;
    // bool ptoV = !pto.value();
    // if (Controller1.ButtonX.pressing()){ //toggles ptoV
    //   if (oldX == false){
    //     pto.set(!pto.value());
    //   }
    //   oldX = true;
    // }
    // else{
    //   oldX = false;
    // }
    //trackI = Controller1.ButtonR1.pressing();


    if (Controller1.ButtonUp.pressing()){ //toggles trackI
      if (oldUp == false){
        trackI = !trackI;
      }
      oldUp = true;
    }
    else{
      oldUp = false;
    }
    //trackI = Controller1.ButtonR1.pressing();

    if (Controller1.ButtonRight.pressing()){ //toggles trackO
      if (oldRight == false){
        trackO = !trackO;
      }
      oldRight = true;
    }
    else{
      oldRight = false;
    }
    //bool TrackO = Controller1.ButtonR2.pressing();

    if (Controller1.ButtonR2.pressing()){ //toggle clamp 2
      if (!oldR2){
        Clamp2.set(!Clamp2.value());
        Clamp3.set(!Clamp3.value());
      }
      oldR2 = true;
    }
    else{
      oldR2 = false;
    }
    //bool Clamp2t = Controller1.ButtonUp.pressing()

    if (Controller1.ButtonR1.pressing()){ //toggle clamp 1
      if (!oldR1){
        Clamp1.set(!Clamp1.value());
      }
      oldR1 = true;
    }
    else{
      oldR1 = false;
    }
    //braking
    
    if (!ptoV){
      RightE.setStopping(coast);
      LeftE.setStopping(coast);
    }
    else{
      RightE.setStopping(hold);
      LeftE.setStopping(hold);
    }
    if (lock){
      setDrivetrainStopping(hold, ptoV);
    }
    else{
      setDrivetrainStopping(coast, ptoV);
    }


    if (a2 != 0 or a1 != 0){
      spinDriveMotors(a2, a1, ptoV);
      printf("a1: %f a2: %f\n",a1, a2);
      motorPos();
      motorVel();
    }
    else if (Controller1.ButtonA.pressing()){ //6m forwards
      LeftT.spin(vex::directionType::fwd , 100, velocityUnits::pct);
      LeftM.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
      LeftD.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
      RightT.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
      RightM.spin(vex::directionType::fwd , 100, velocityUnits::pct);
      RightD.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
    }
    else{
      stopDrive(ptoV);
    }

    if (ptoV){
      if (trackI){
        RightE.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
      }
      else if (trackO){
        RightE.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
      }
      else{
        RightE.stop();
      }


      if (BarDown){
        LeftE.spin(vex::directionType::fwd , 100 , velocityUnits::pct);
      }
      else if (BarUp){
        LeftE.spin(vex::directionType::fwd , -100 , velocityUnits::pct);
      }
      else{
        LeftE.stop();
      }
    }

    //temp is 50, starts slowing down at 55
    Controller1.Screen.clearLine();
    if (ptoV){
      Controller1.Screen.print("U E%d V%d \nT%d M%d %s", (int) avgEff, (int) avgVelo, (int) avgTemp, (int) max, panik);
    }
    else{
      Controller1.Screen.print("D E%d V%d \nT%d M%d %s", (int) avgEff, (int) avgVelo, (int) avgTemp, (int) max, panik);
    }
    // if (cooldown <= 100){
    //   int lmao = LeftT.efficiency() + LeftM.efficiency() + LeftD.efficiency();
    //   int stupid = RightT.efficiency() + RightM.efficiency() + RightD.efficiency();
    //   if (LeftT.temperature() >= 130){
    //     printf("WARNING LeftT");
    //   }
    //    + LeftM.temperature() + LeftD.temperature();
    //   int stupid2 = RightT.temperature() + RightM.temperature() + RightD.temperature();
      
    //   for (int i=0; i<6; i++){

    //   }
    //   //add motorgroup and strings
    //   printf("Left: %d %d \nRight: %d %d\n", lmao, lmao2, stupid, stupid2);
    // }
    vex::wait(TICK_CYCLE,sec);
  }
}

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
