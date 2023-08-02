#include "vex.h"
#include "movements.h"
using namespace vex;

void pForkliftDown(){
  Forklift.spinFor(reverse, 500, deg, 100, vex::velocityUnits::pct);
}
void pForkliftUp2(){
  Forklift.spinFor(forward, 1250, deg, 100, vex::velocityUnits::pct);
}
void pForkliftDown2(bool noDrift=true){
  Forklift.spinFor(reverse, 1250, deg, 100, vex::velocityUnits::pct, noDrift);
}
void pForkliftUp(){
  Forklift.spinFor(forward, -.35*7*360, deg, 100, vex::velocityUnits::pct);
  ClampF.spinFor(forward, -360, deg, 100, vex::velocityUnits::pct);
}
// void autonLeft(){
//   //optional; face alliance mogo
//   //pForkliftUp2();
//   //spinDriveMotorsC(-.5,.5);// turn right
  
//   //optional
//   // face wall to go straight back into neutral mogo
//   Beyblade.spinFor(reverse, 2350, deg, 100, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(-3.5,.5, 50);// go back
//   pForkliftDown2(false);
//   spinDriveMotorsC(-.5,0, 20);// go back
//   Clamp.spinFor(forward, 240, deg, 100, vex::velocityUnits::pct);
//   Beyblade.spinFor(forward, 800, deg, 100, vex::velocityUnits::pct);
//   //pBeybladeUp();// small neutral mogo
//   //pBeybladeDown();
//   Beyblade.spinFor(forward, 700, deg, 100, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(1.8,-1.8, 40);// turn left
//   spinDriveMotorsC(1.2,0);// go front
//   spinDriveMotorsC(1.2,0,20);// go front
//   Forklift.spinFor(forward, 400, deg, 100, vex::velocityUnits::pct);
//   Forklift.spinFor(forward, 400, deg, 80, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(-3,0,30);// go back
//   spinDriveMotorsC(-2.5,-3, 40);// turn left

// }
// void autonRight(){
//   // face wall to go straight back into neutral mogo
//   Beyblade.spinFor(reverse, 2350, deg, 100, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(-3.5,0, 50);// go back
//   pForkliftDown2(false);
//   spinDriveMotorsC(-.5,0, 30);// go back
//   Clamp.spinFor(forward, 220, deg, 100, vex::velocityUnits::pct);
//   Beyblade.spinFor(forward, 1300, deg, 100, vex::velocityUnits::pct);
//   Beyblade.spinFor(forward, 200, deg, 100, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(-.8,.8, 60);// turn right
//   spinDriveMotorsC(2.5,0);// go front
//   spinDriveMotorsC(1,0,70);// go front
//   Forklift.spinFor(forward, 400, deg, 100, vex::velocityUnits::pct);
//   Forklift.spinFor(forward, 400, deg, 80, vex::velocityUnits::pct, false);
//   spinDriveMotorsC(1.5,0,30);// go back
//   spinDriveMotorsC(1,1, 40);// turn left
// }
//void prog(){
  // KEYNOTE assumed 13 in for inner and outer
  //  f1 = center to mogo center
  //  9 = center to mogo end
  //  b1 = center to mogo center 4bar
  //  b2 = center to mogo end 4bar
  //clamp down
  // [fk up]
  //turn lf 90 deg
  // [fk down]

  // NEUTRAL 1
  //forward push 64.2-(11.4+9) in
  //forward 64.2 in
  //back 30.8-9 in
  //turn right 90 deg
  //clamp up
  //turn right 180 deg
  //forward 17.6-9 in
  //clamp down
  //[fk in clamp up fk down]
  //back 17.6-9 in
  //turn 135 lf


  // NEUTRAL 2
  //forward 35sqrt(2)-13-9 in
  //forward 35sqrt(2) + 13 in
  //[clamp up]
  //back 13 in
  //turn 45 lf
  //forward 11.4+6 in
  //clamp down
  //fk up
  //back 11.4+6 in
  //turn rt 90 deg
  //4b down

  // NEUTRAL 3
  //back 35-9 in
  //turn left 90 deg
  //back 13 in
  //fk down
  //clamp up
  //forward 13 in
  //
void autonL() {
	//position it so that it only has to go straight
	// left 35in up 7.5in
	//center of bot is nearly touching alliance or 35-7.5in from left wall
	//right 7.5 in and forward 64.2-9 in diagonal
	// 64.64in-9 forward
	spinDriveMotorsRL(-(45) / 13.35, -(45) / 13.35, 100);
	//clamp down
  vex::wait(.1,sec);
  spinDriveMotorsRL(-(4) / 13.35, -(4) / 13.35, 70, false);
	ClampB.spinFor(forward, 90, deg, 100, vex::velocityUnits::pct);
	// //right side back (64.2-46.8) left side back (64.2-46.8)+(64.64-64.2)/2
	// // HERE SHOULD BE STRAIGHT
	//vex::wait(.5,sec);
	// //clamp up
  spinDriveMotorsRL(12 / 13.35, 12 / 13.35, 100);
  vex::wait(.3,sec);
  Bar.spinFor(forward, 10*7, deg, 100, vex::velocityUnits::pct);
  //spinDriveMotorsRL(.35, -.35, 30);
  spinDriveMotorsRL((23.4*1.2) / 13.35, (23.4*1.2) / 13.35, 100);
  vex::wait(.3,sec);
  spinDriveMotorsRL(.4, -.4, 50);
  spinDriveMotorsRL((4) / 13.35, (4) / 13.35, 10);
  vex::wait(.3,sec);
  spinDriveMotorsRL((2) / 13.35, (2) / 13.35, 50, false);
  ClampF.spinFor(forward, 120, deg, 100, vex::velocityUnits::pct);
  vex::wait(.3,sec);
  spinDriveMotorsRL(-(13.5) / 13.35, -(13.5) / 13.35, 30);
  pForkliftUp();
  vex::wait(.2,sec);
  Forklift.spinFor(forward, .4*7*360, deg, 100, vex::velocityUnits::pct);
  spinDriveMotorsRL(.5, -.5, 50);
  spinDriveMotorsRL(23.4 / 13.35, 23.4 / 13.35, 100);
	//ClampF.spinFor(reverse, 180, deg, 100, vex::velocityUnits::pct);
	// //(46.8-35-9) back; middle of the 2,2 tile
	// spinDriveMotorsRL(-(46.8 - 35 - 9) / 13.35, -(46.8 - 35 - 9) / 13.35, 100);
	// //back 23.4sqrt(2) or 33.1 in
	// spinDriveMotorsRL(33.1 / 13.35, 33.1 / 13.35, 100);
	// //right 45 deg
	// spinDriveMotorsRL(.25, -.25, 100);
	// //forward 23.4-9
	// spinDriveMotorsRL((23.4 - 9) / 13.35, (23.4 - 9) / 13.35, 100);
	// //clamp down
	// ClampF.spinFor(forward, 180, deg, 100, vex::velocityUnits::pct);
	// //fk up
	// Forklift.spinFor(forward, 1250, deg, 100, vex::velocityUnits::pct);
	// //back 23.4-9
	// spinDriveMotorsRL((23.4 - 9) / 13.35, (23.4 - 9) / 13.35, 100);
	// //right 135 deg
	// spinDriveMotorsRL(.75, -.75, 100);
	// //back 23.4sqrt(2)
	// spinDriveMotorsRL(-33.1 / 13.35, -33.1 / 13.35, 100);
	// //left 45 deg
	// spinDriveMotorsRL(.5, -.5, 100);
	// //(46.8-35-9) back
	// spinDriveMotorsRL(-(46.8 - 35 - 9) / 13.35, -(46.8 - 35 - 9) / 13.35, 100);
	// //4Bar up
	// Bar.spinFor(reverse, 180, deg, 100, vex::velocityUnits::pct);
	// //right 180 deg
	// spinDriveMotorsRL(2, -2, 100);
}

void autonR() {
	//64.2 in forward
	spinDriveMotorsRL(-42/13.35,-42/13.35,100);
  vex::wait(.1,sec);
  spinDriveMotorsRL(-4/13.35,-4/13.35,40);
	//clamp down
	ClampB.spinFor(forward, 90, deg, 100, vex::velocityUnits::pct);
	// 5in buffer
	//(64.2-35-8.5-5 in) back
  //spinDriveMotorsRL(0/13.35,0/13.35,100);
  spinDriveMotorsRL(0/13.35,4/13.35,100);
	spinDriveMotorsRL(10/13.35,10/13.35,100);
  vex::wait(.2,sec);
  spinDriveMotorsRL(16/13.35,16/13.35,50);
  Bar.spinFor(forward, 15*7, deg, 100, vex::velocityUnits::pct);
  spinDriveMotorsRL(.7, -.7, 30);
  spinDriveMotorsRL(4/13.35,4/13.35,30);
  vex::wait(1,sec);
  ClampF.spinFor(forward, 120, deg, 100, vex::velocityUnits::pct);
  vex::wait(.3,sec);
  spinDriveMotorsRL(-(18) / 13.35, -(18) / 13.35, 30);
  pForkliftUp();
  vex::wait(.2,sec);
  Forklift.spinFor(forward, .4*7*360, deg, 100, vex::velocityUnits::pct, false);
  spinDriveMotorsRL(-(30) / 13.35, -(30) / 13.35, 50);
  spinDriveMotorsRL(.7 / 13.35, -(.7) / 13.35, 50);
}

void prog() {
 ClampF.spinFor(forward, 120, deg, 100, vex::velocityUnits::pct);
 vex::wait(.5,sec);
 pForkliftUp(); 
 vex::wait(.5,sec);
 //spinDriveMotorsRL(-5/13.35,-5/13.35,100,false);
 Forklift.spinFor(forward, -.35*1*360, deg, 100, vex::velocityUnits::pct, false);
 spinDriveMotorsRL(5/13.35,5/13.35,80);
 spinDriveMotorsRL(.75, -.75, 10);
 spinDriveMotorsRL(26/13.35,26/13.35,100);
 Forklift.spinFor(forward, .35*8*360, deg, 100, vex::velocityUnits::pct, false);
 ClampF.spinFor(forward, -120, deg, 100, vex::velocityUnits::pct, false);
 spinDriveMotorsRL(25/13.35,25/13.35,60);
 vex::wait(1,sec);
 ClampF.spinFor(forward, 120, deg, 100, vex::velocityUnits::pct, false);
 //ClampB.spinFor(forward, 90, deg, 100, vex::velocityUnits::pct);
 spinDriveMotorsRL(45/13.35,45/13.35,100);
}