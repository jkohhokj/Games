#include "vex.h"
#include <stdlib.h>
#include <stdio.h>
using namespace vex;
float kP = 0;
float kI = 0;
float kD = 0;
float TICK_CYCLE = .01;
// void prime(){
//   LeftT.setMaxTorque(.1, pct);
//   RightT.setMaxTorque(.1, pct);
//   RightD.setMaxTorque(.1, pct);
//   LeftD.setMaxTorque(.1, pct);
//   // RightD.spin(vex::directionType::fwd);
//   // LeftD.spin(vex::directionType::fwd);
//   // vex::wait(.2,sec);
//   // RightD.stop();
//   // LeftD.stop();
//   // RightD.spin(vex::directionType::rev);
//   // LeftD.spin(vex::directionType::rev);
//   // vex::wait(.2,sec);
//   // RightD.stop();
//   // LeftD.stop();
//   // LeftT.spin(vex::directionType::rev);
//   // RightT.spin(vex::directionType::rev);
//   // vex::wait(.2,sec);
//   // LeftT.stop();
//   // RightT.stop();

//   // LeftT.spin(vex::directionType::fwd);
//   // RightT.spin(vex::directionType::fwd);
//   // vex::wait(.2,sec);
//   // LeftT.stop();
//   // RightT.stop();

//   RightD.spin(vex::directionType::fwd);
//   LeftD.spin(vex::directionType::fwd);
//   LeftT.spin(vex::directionType::rev);
//   RightT.spin(vex::directionType::rev);
//   vex::wait(.1,sec);
//   RightD.stop();
//   LeftD.stop();
//   LeftT.stop();
//   RightT.stop();

//   LeftT.setMaxTorque(100, pct);
//   RightT.setMaxTorque(100, pct);
//   RightD.setMaxTorque(100, pct);
//   LeftD.setMaxTorque(100, pct);
// }
int * motorPos(bool ptoV=true){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  static int pos[8];
  int max = 8;
  // if (ptoV){
  //   max = 6;
  // }
  // else{
  //   max = 8;
  // }
  for (int i=0; i <max; i++){
    if (i == 0 or i == 2 or i == 3 or i == 5){
      pos[i] = EightM[i].position(deg);
    }
    else{
      pos[i] = -1*EightM[i].position(deg);
    }
    
    //printf("%d %d\n",i,pos[i]);
  }
  return pos;
}
int * motorVel(bool ptoV=true){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  static int vel[8];
  int max = 8;
  // if (ptoV){
  //   max = 6;
  // }
  // else{
  //   max = 8;
  // }
  for (int i=0; i <max; i++){
    vel[i] = EightM[i].velocity(pct);
    //printf("%d %d\n",i,vel[i]);
  }
  return vel;
}

int * motorEff(bool ptoV=true){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  static int vel[8];
  int max = 8;
  // if (ptoV){
  //   max = 6;
  // }
  // else{
  //   max = 8;
  // }
  for (int i=0; i <max; i++){
    vel[i] = EightM[i].efficiency(pct);
    //printf("%d %d\n",i,vel[i]);
  }
  return vel;
}

int microadj(){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  int max = 8;
  bool ptoV = true;
  float destR = 0;
  float destL = 0;
  float expectedR = 0;
  float expectedL = 0;
  if (ptoV){
    max = 6;
  }
  else{
    max = 8;
  }
  while(true){
    int * vels;
    int * poss;
    vels = motorVel();
    poss = motorPos();
    vex::wait(TICK_CYCLE,sec);
  }
  return 0;
  //l
}
vex::task caller() {
  return vex::task (microadj);
}
void prime(){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  for (int i=0; i<8; i++){
    EightM[i].setMaxTorque(.1,pct);
    EightM[i].spin(fwd);
    vex::wait(.05,sec);
    EightM[i].stop();
    EightM[i].setMaxTorque(100,pct);
  }
}

// int tempTASK(){
//   while (true){
//     int * vels;
//     vels = motorVel();
//   }
//   return 0;
// }
void spinDriveMotors (double a2, double a1, bool isUp=true){ //controls drivetrainmovement.
  LeftT.spin(vex::directionType::fwd , (a2 + a1) , velocityUnits::pct);
  LeftM.spin(vex::directionType::fwd , -(a2 + a1) , velocityUnits::pct);
  LeftD.spin(vex::directionType::fwd , (a2 + a1) , velocityUnits::pct);
  RightT.spin(vex::directionType::fwd , -(a2-a1) , velocityUnits::pct);
  RightM.spin(vex::directionType::fwd , (a2-a1) , velocityUnits::pct);
  RightD.spin(vex::directionType::fwd , -(a2-a1) , velocityUnits::pct);
  if(!isUp){
    LeftE.spin(vex::directionType::fwd , (a2 + a1) , velocityUnits::pct);
    RightE.spin(vex::directionType::fwd , -(a2-a1) , velocityUnits::pct);
  }
}

void spinDriveMotorsC (double a1, double a2, double velo=100, bool noDrift=false, bool ptoV=true){ //spinDriveMotors Custom
  int max = abs((int) a1) + abs((int) a2);
  LeftT.spinFor((a2 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  LeftM.spinFor((a2 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  LeftD.spinFor((a2 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  RightT.spinFor((a2 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  RightM.spinFor((a2 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  RightD.spinFor((a2 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct); //add timing
  if (!ptoV){
    LeftE.spinFor((a2 + a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
    RightE.spinFor((a2 - a1), rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
  }
}
void stopDrive(bool isUp=false){
  LeftT.stop();
  LeftM.stop();
  LeftD.stop();
  RightT.stop();
  RightM.stop();
  RightD.stop();
  if (!isUp){
    LeftE.stop();
    RightE.stop();
  }
}
void spinDriveMotorsV (int veloL, int veloR, double time, bool noDrift=false, bool ptoV=true){ //spinDriveMotors Custom
  //int max = abs((int) a1) + abs((int) a2);
  LeftT.spin(vex::directionType::fwd, veloL, vex::voltageUnits::volt);
  LeftM.spin(vex::directionType::rev, veloL, vex::voltageUnits::volt);
  LeftD.spin(vex::directionType::fwd, veloL, vex::voltageUnits::volt);
  RightT.spin(vex::directionType::rev, veloR, vex::voltageUnits::volt);
  RightM.spin(vex::directionType::fwd, veloR, vex::voltageUnits::volt);
  RightD.spin(vex::directionType::rev, veloR, vex::voltageUnits::volt);
  if (!ptoV){
    LeftE.spin(vex::directionType::fwd, veloL, vex::voltageUnits::volt);
    RightE.spin(vex::directionType::rev, veloR, vex::voltageUnits::volt);
  }
  //vex::wait(time,sec);
  stopDrive(ptoV);
}

void spinDriveMotorsRL (double r, double l, double velo=100, bool ptoV=false, bool noDrift=true){ //spinDriveMotors Custom
  if (!ptoV){
    LeftE.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
    RightE.spinFor(r, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  }
  LeftT.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RightT.spinFor(r, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  LeftM.spinFor(-l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RightM.spinFor(-r, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  LeftD.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RightD.spinFor(r, rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift); //add timing
}
void setDrivetrainStopping(brakeType stop=hold, bool isUp=true){ //coast, brake, halt
  LeftD.setStopping(stop);
  LeftM.setStopping(stop);
  LeftT.setStopping(stop);
  RightD.setStopping(stop);
  RightM.setStopping(stop);
  RightT.setStopping(stop);
  if (!isUp){
    LeftE.setStopping(stop);
    RightE.setStopping(stop);
  }
}
void reset(){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, RightT, RightM, RightD, LeftE, RightE};
  for (int i=0; i<8; i++){
    EightM[i].resetRotation();
    EightM[i].setRotation(0,deg);
    //printf("%d %f\n",i, EightM[i].position(deg));
  }
  //printf("reset: %f",LeftT.position(deg));
}
void preauton(){
  reset();
  // pto.set(true);
  Clamp1.set(false);
  Clamp2.set(false);
  Clamp3.set(false);
}
void autonR(){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  int leftPos = 750;
  int rightPos = 750;
  float leftTrav = 0;
  float rightTrav = 0;
  //spinDriveMotors(1200/360,-1200/360);
  while (leftTrav <= leftPos){
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftTrav-rightTrav)/2;//+(rightCur-leftCur);
    if (err < 0){
      RightT.spin(fwd,-100-err,pct);
      RightM.spin(fwd,100+err,pct);
      RightD.spin(fwd,-100-err,pct);
      // RightE.spin(fwd,-100-err,pct);
      LeftT.spin(fwd,100,pct);
      LeftM.spin(fwd,-100,pct);
      LeftD.spin(fwd,100,pct);
      // LeftE.spin(fwd,100,pct);  
    }
    else{
      LeftT.spin(fwd,100-err,pct);
      LeftM.spin(fwd,-100+err,pct);
      LeftD.spin(fwd,100-err,pct);
      // LeftE.spin(fwd,100-err,pct);
      RightT.spin(fwd,-100,pct);
      RightM.spin(fwd,100,pct);
      RightD.spin(fwd,-100,pct);
      // RightE.spin(fwd,-100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",LeftT.velocity(pct),RightT.velocity(pct));
  }
  //reset(); //drive forwards

  Clamp1.set(true);
  stopDrive(false);
  vex::wait(.05,sec);
  //clamp down

  leftPos = 400;
  rightPos = 400;
  //leftTrav = 0;
  //rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruh = motorPos();
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftTrav-rightTrav)/2;//+(rightCur-leftCur);;
    if (err > 0){
      RightT.spin(fwd,-(-100+err),pct);
      RightM.spin(fwd,-(100-err),pct);
      RightD.spin(fwd,-(-100+err),pct);
      // RightE.spin(fwd,-(-100+err),pct);
      LeftT.spin(fwd,-100,pct);
      LeftM.spin(fwd,100,pct);
      LeftD.spin(fwd,-100,pct);
      // LeftE.spin(fwd,-100,pct);  
    }
    else{
      LeftT.spin(fwd,-(100+err),pct);
      LeftM.spin(fwd,-(-100-err),pct);
      LeftD.spin(fwd,-(100+err),pct);
      // LeftE.spin(fwd,-(100+err),pct);
      RightT.spin(fwd,100,pct);
      RightM.spin(fwd,-100,pct);
      RightD.spin(fwd,100,pct);
      // RightE.spin(fwd,100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  printf("FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK");
  stopDrive();
  vex::wait(.1,sec);
  reset(); //drive backwards


  //spinDriveMotorsRL(180/360,-180/360);
  // LeftE.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // RightE.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // LeftT.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // RightT.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // LeftM.spinFor(1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // RightM.spinFor(1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // LeftD.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct, false);
  // RightD.spinFor(-1, rotationUnits::rev, 100, vex::velocityUnits::pct); //add timing
  leftPos = -135;
  rightPos = 135;
  leftTrav = 0;
  rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = ((-leftTrav-rightTrav/2));//+(-leftCur-rightCur))/2;
    //err = 0;
    printf("err: %f\n",err);
    if (err > 100 or err < -100){
      printf("fuck fuck fuck err: %f",err);
    }
    else if (err > 0){
      RightT.spin(fwd,-100+err,pct);
      RightM.spin(fwd,100-err,pct);
      RightD.spin(fwd,-100+err,pct);
      // RightE.spin(fwd,-100+err,pct);
      LeftT.spin(fwd,-100,pct);
      LeftM.spin(fwd,100,pct);
      LeftD.spin(fwd,-100,pct);
      // LeftE.spin(fwd,-100,pct);  
    }
    else{
      LeftT.spin(fwd,-(100+err),pct);
      LeftM.spin(fwd,-(-100-err),pct);
      LeftD.spin(fwd,-(100+err),pct);
      // LeftE.spin(fwd,-(100+err),pct);
      RightT.spin(fwd,-100,pct);
      RightM.spin(fwd,100,pct);
      RightD.spin(fwd,-100,pct);
      // RightE.spin(fwd,-100,pct);
    }
    vex::wait(.01,sec);
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  while (rightTrav <= rightPos){
    int * bruhPos = motorPos();
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    RightT.spin(fwd,-100,pct);
    RightM.spin(fwd,100,pct);
    RightD.spin(fwd,-100,pct);
    // RightE.spin(fwd,-100,pct);
    printf("right extra correction: %f\n",rightTrav);
  } 
  stopDrive(); //turn left
  vex::wait(.2,sec);
  reset();
  leftPos = -340;
  rightPos = -340;
  leftTrav = 0;
  rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruh = motorPos();
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftTrav-rightTrav)/10;//+(leftCur-rightCur))/2;
    if (err > 0){
      RightT.spin(fwd,-(-50+err),pct);
      RightM.spin(fwd,-(50-err),pct);
      RightD.spin(fwd,-(-50+err),pct);
      // RightE.spin(fwd,-(-100+err),pct);
      LeftT.spin(fwd,-50,pct);
      LeftM.spin(fwd,50,pct);
      LeftD.spin(fwd,-50,pct);
      // LeftE.spin(fwd,-100,pct);  
    }
    else{
      LeftT.spin(fwd,-(50+err),pct);
      LeftM.spin(fwd,-(-50-err),pct);
      LeftD.spin(fwd,-(50+err),pct);
      // LeftE.spin(fwd,-(100+err),pct);
      RightT.spin(fwd,50,pct);
      RightM.spin(fwd,-50,pct);
      RightD.spin(fwd,50,pct);
      // RightE.spin(fwd,100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  printf("FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK");
  Clamp2.set(true);
  Clamp3.set(true);
  stopDrive();
  vex::wait(.3,sec);
  reset(); //drive backwards
  printf("fuck"); 
  // set(false);
  LeftE.spinFor(reverse,1,rev);
  //vex::wait(.4,sec);
  //LeftE.stop();
  RightE.spin(fwd,100,pct);
  vex::wait(4,sec);
  RightE.stop();
}

void autonM(bool ptoV=false){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  int leftPos = 1300;
  int rightPos = 1300;
  float leftTrav = 0;
  float rightTrav = 0;
  //spinDriveMotors(1200/360,-1200/360);
  while (leftTrav <= leftPos){
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftCur-rightCur)*10;
    if (err < 0){
      RightT.spin(fwd,-100-err,pct);
      RightM.spin(fwd,100+err,pct);
      RightD.spin(fwd,-100-err,pct);
      RightE.spin(fwd,-100-err,pct);
      LeftT.spin(fwd,100,pct);
      LeftM.spin(fwd,-100,pct);
      LeftD.spin(fwd,100,pct);
      LeftE.spin(fwd,100,pct);  
    }
    else{
      LeftT.spin(fwd,100-err,pct);
      LeftM.spin(fwd,-100+err,pct);
      LeftD.spin(fwd,100-err,pct);
      LeftE.spin(fwd,100-err,pct);
      RightT.spin(fwd,-100,pct);
      RightM.spin(fwd,100,pct);
      RightD.spin(fwd,-100,pct);
      RightE.spin(fwd,-100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  //reset(); //drive forwards

  Clamp1.set(true);
  stopDrive(false);
  vex::wait(.05,sec);
  //clamp down

  //spinDriveMotorsRL(-720/360,-720/360);
  leftPos = 000;
  rightPos = 000;
  //leftTrav = 0;
  //rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruh = motorPos();
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = -(leftTrav-rightTrav);
    if (err < 0){
      RightT.spin(fwd,-100-err,pct);
      RightM.spin(fwd,100+err,pct);
      RightD.spin(fwd,-100-err,pct);
      RightE.spin(fwd,-100-err,pct);
      LeftT.spin(fwd,100,pct);
      LeftM.spin(fwd,-100,pct);
      LeftD.spin(fwd,100,pct);
      LeftE.spin(fwd,100,pct);  
    }
    else{
      LeftT.spin(fwd,100-err,pct);
      LeftM.spin(fwd,-100+err,pct);
      LeftD.spin(fwd,100-err,pct);
      LeftE.spin(fwd,100-err,pct);
      RightT.spin(fwd,-100,pct);
      RightM.spin(fwd,100,pct);
      RightD.spin(fwd,-100,pct);
      RightE.spin(fwd,-100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  printf("FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK");
  stopDrive();
  vex::wait(.1,sec);
  reset(); //drive backwards
}
void autonL(){
  vex::motor EightM[8] = {LeftT, LeftM, LeftD, LeftE, RightT, RightM, RightD, RightE};
  setDrivetrainStopping(hold,false);
  int leftPos = 900;
  int rightPos = 900;
  float leftTrav = 0;
  float rightTrav = 0;
  //spinDriveMotors(1200/360,-1200/360);
  while (leftTrav <= leftPos){
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftTrav-rightTrav)/2;//+(rightCur-leftCur);
    if (err < 0){
      RightT.spin(fwd,-100-err,pct);
      RightM.spin(fwd,100+err,pct);
      RightD.spin(fwd,-100-err,pct);
      // RightE.spin(fwd,-100-err,pct);
      LeftT.spin(fwd,100,pct);
      LeftM.spin(fwd,-100,pct);
      LeftD.spin(fwd,100,pct);
      // LeftE.spin(fwd,100,pct);  
    }
    else{
      LeftT.spin(fwd,100-err,pct);
      LeftM.spin(fwd,-100+err,pct);
      LeftD.spin(fwd,100-err,pct);
      // LeftE.spin(fwd,100-err,pct);
      RightT.spin(fwd,-100,pct);
      RightM.spin(fwd,100,pct);
      RightD.spin(fwd,-100,pct);
      // RightE.spin(fwd,-100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",LeftT.velocity(pct),RightT.velocity(pct));
  }
  //reset(); //drive forwards

  Clamp1.set(true);
  stopDrive();
  vex::wait(.05,sec);
  //clamp down

  leftPos = 0;
  rightPos = 0;
  //leftTrav = 0;
  //rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruh = motorPos();
    int * bruhPos = motorPos();
    int * bruhCur = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1]+bruhPos[2]+bruhPos[3])/4;
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    int leftCur = (bruhCur[0]+bruhCur[1]+bruhCur[2]+bruhCur[3])/4;
    int rightCur = (bruhCur[4]+bruhCur[5]+bruhCur[6]+bruhCur[7])/4;
    float err = (leftTrav-rightTrav)/2;//+(rightCur-leftCur);;
    if (err > 0){
      RightT.spin(fwd,-(-100+err),pct);
      RightM.spin(fwd,-(100-err),pct);
      RightD.spin(fwd,-(-100+err),pct);
      // RightE.spin(fwd,-(-100+err),pct);
      LeftT.spin(fwd,-100,pct);
      LeftM.spin(fwd,100,pct);
      LeftD.spin(fwd,-100,pct);
      // LeftE.spin(fwd,-100,pct);  
    }
    else{
      LeftT.spin(fwd,-(100+err),pct);
      LeftM.spin(fwd,-(-100-err),pct);
      LeftD.spin(fwd,-(100+err),pct);
      // LeftE.spin(fwd,-(100+err),pct);
      RightT.spin(fwd,100,pct);
      RightM.spin(fwd,-100,pct);
      RightD.spin(fwd,100,pct);
      // RightE.spin(fwd,100,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
  }
  printf("FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK");
  stopDrive();
  vex::wait(.1,sec);
  reset(); //drive backwards
}