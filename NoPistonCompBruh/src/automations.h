#include "vex.h"
using namespace vex;
void prime(){
  vex::motor EightM[8] = {LT, LD, RT, RD, Conv, Bar, CF, CB};
  for (int i=0; i<8; i++){
    EightM[i].setMaxTorque(.1,pct);
    EightM[i].spin(fwd);
    vex::wait(.05,sec);
    EightM[i].stop();
    EightM[i].setMaxTorque(100,pct);
  }
}
void spinDriveMotors (double a2, double a1, bool isUp=true){ //controls drivetrainmovement.
  LT.spin(vex::directionType::fwd , (a2 + a1) , velocityUnits::pct);
  LD.spin(vex::directionType::fwd , (a2 + a1) , velocityUnits::pct);
  RT.spin(vex::directionType::fwd , (a2 - a1) , velocityUnits::pct);
  RD.spin(vex::directionType::fwd , (a2 - a1) , velocityUnits::pct);
}
void stopDrive(){
  vex::motor FourM[4] = {LT, LD, RT, RD};
  for (int i=0; i < 4; i++){
    FourM[i].stop();
  }
}
void spinDriveMotorsRL (double r, double l, double velo=100, bool noDrift=true){ //spinDriveMotors Custom
  LT.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  LD.spinFor(l, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RT.spinFor(r, rotationUnits::rev, velo, vex::velocityUnits::pct, false);
  RD.spinFor(r, rotationUnits::rev, velo, vex::velocityUnits::pct, noDrift);
}
void setDrivetrainStopping(brakeType stop=hold){ //coast, brake, halt
  vex::motor FourM[4] = {LT, LD, RT, RD};
  for (int i=0; i < 4; i++){
    FourM[i].setStopping(stop);
  }
}
void reset(){
  vex::motor FourM[4] = {LT,LD,RT,RD};
  for (int i=0; i<4; i++){
    FourM[i].resetRotation();
  }
}
void autonR(){
  setDrivetrainStopping(hold);
  spinDriveMotorsRL(750/360,750/360);
  CF.spin(reverse);
  stopDrive();
  vex::wait(.05,sec);
  spinDriveMotorsRL(-150/360,150/360);
  CF.stop();
  spinDriveMotorsRL(-300/360,-300/360);
  vex::wait(.5,sec);
  spinDriveMotorsRL(135/360,-135/360,30);
  spinDriveMotorsRL(-360/360,-360/360,false);
  vex::wait(.3,sec);
  stopDrive();
  CB.spin(fwd);
  vex::wait(1,sec);
  Conv.spin(fwd);
  CB.stop();
}
void autonL(){
  setDrivetrainStopping(hold);
  spinDriveMotorsRL(900/360,900/360);
  CF.spin(fwd);
  stopDrive();
  vex::wait(.05,sec);
  spinDriveMotorsRL(-150/360,150/360);
  CF.stop();
  spinDriveMotorsRL(-750/360,-750/360);
  vex::wait(.5,sec);
  Conv.spin(fwd);
}
int * motorPos(){
  vex::motor FourM[4] = {LT,LD,RT,RD};
  static int pos[4];
  for (int i=0; i < 4; i++){
    pos[i] = FourM[i].position(deg);
  }
  return pos;
}
int * motorEff(){
  vex::motor FourM[4] = {LT,LD,RT,RD};
  static int pos[4];
  for (int i=0; i < 4; i++){
    pos[i] = FourM[i].efficiency(pct);
  }
  return pos;
}
void autonRT(){
  vex::motor FourM[4] = {LT,LD,RT,RD};
  int leftPos = 750;
  int rightPos = 750;
  float leftTrav = 0;
  float rightTrav = 0;
  float leftEff = 0;
  float rightEff = 0;
  while (leftTrav <= leftPos){
    int * bruhPos = motorPos();
    int * bruhEff = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1])/2;
    rightTrav = (bruhPos[2]+bruhPos[3])/2;
    leftEff = (bruhEff[0]+bruhEff[1])/2;
    rightEff = (bruhEff[2]+bruhEff[3])/2;
    float err = (leftTrav-rightTrav)/10;
    if (err > 0){ //slow down left
      LT.spin(fwd,100-err,pct);
      LD.spin(fwd,100-err,pct);
      RT.spin(fwd,100,pct);
      RD.spin(fwd,100,pct);
    }
    else{ //slow down right
      LT.spin(fwd,100,pct);
      LD.spin(fwd,100,pct);
      RT.spin(fwd,100+err,pct);
      RD.spin(fwd,100+err,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",leftEff, rightEff);
  }
  //drive forwards

  CF.spin(reverse);
  stopDrive();
  vex::wait(.05,sec);
  //clamp down

  leftPos = 400;
  rightPos = 400;
  while (leftTrav >= leftPos){
    int * bruhPos = motorPos();
    int * bruhEff = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1])/2;
    rightTrav = (bruhPos[2]+bruhPos[3])/2;
    leftEff = (bruhEff[0]+bruhEff[1])/2;
    rightEff = (bruhEff[2]+bruhEff[3])/2;
    float err = -(leftTrav-rightTrav)/10;
    if (err > 0){ //slow down left
      LT.spin(fwd,100-err,pct);
      LD.spin(fwd,100-err,pct);
      RT.spin(fwd,100,pct);
      RD.spin(fwd,100,pct);
    }
    else{ //slow down right
      LT.spin(fwd,100,pct);
      LD.spin(fwd,100,pct);
      RT.spin(fwd,100+err,pct);
      RD.spin(fwd,100+err,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",leftEff, rightEff);
  }
  stopDrive();
  vex::wait(.1,sec);
  reset(); //drive backwards


  leftPos = -135;
  rightPos = 135;
  leftTrav = 0;
  rightTrav = 0;
  while (leftTrav >= leftPos){
    int * bruhPos = motorPos();
    int * bruhEff = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1])/2;
    rightTrav = (bruhPos[2]+bruhPos[3])/2;
    leftEff = (bruhEff[0]+bruhEff[1])/2;
    rightEff = (bruhEff[2]+bruhEff[3])/2;
    float err = -(leftTrav-rightTrav)/10;
    if (err > 0){ //slow down left
      LT.spin(fwd,100-err,pct);
      LD.spin(fwd,100-err,pct);
      RT.spin(fwd,100,pct);
      RD.spin(fwd,100,pct);
    }
    else{ //slow down right
      LT.spin(fwd,100,pct);
      LD.spin(fwd,100,pct);
      RT.spin(fwd,100+err,pct);
      RD.spin(fwd,100+err,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",leftEff, rightEff);
  }
  while (rightTrav <= rightPos){
    int * bruhPos = motorPos();
    rightTrav = (bruhPos[4]+bruhPos[5]+bruhPos[6]+bruhPos[7])/4;
    RT.spin(fwd,100,pct);
    RD.spin(fwd,100,pct);
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
    int * bruhPos = motorPos();
    int * bruhEff = motorEff();
    leftTrav = (bruhPos[0]+bruhPos[1])/2;
    rightTrav = (bruhPos[2]+bruhPos[3])/2;
    leftEff = (bruhEff[0]+bruhEff[1])/2;
    rightEff = (bruhEff[2]+bruhEff[3])/2;
    float err = -(leftTrav-rightTrav)/10;
    if (err > 0){ //slow down left
      LT.spin(fwd,100-err,pct);
      LD.spin(fwd,100-err,pct);
      RT.spin(fwd,100,pct);
      RD.spin(fwd,100,pct);
    }
    else{ //slow down right
      LT.spin(fwd,100,pct);
      LD.spin(fwd,100,pct);
      RT.spin(fwd,100+err,pct);
      RD.spin(fwd,100+err,pct);
    }
    printf("left %f right %f\n",leftTrav, rightTrav);
    printf("leftVel %f rightVel %f\n",leftEff, rightEff);
  }
  printf("FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK");
  CB.spin(reverse);
  stopDrive();
  vex::wait(.3,sec);
  reset(); //drive backwards
  printf("fuck"); 
  // set(false);
  Bar.spin(fwd,30,pct);
  Conv.spin(fwd,100,pct);
  vex::wait(1,sec);
  Bar.stop();
  vex::wait(4,sec);;
  Conv.stop();
}
