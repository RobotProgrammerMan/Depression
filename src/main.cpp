/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Tyni2                                                     */
/*    Created:      11/14/2023, 5:26:38 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// Setup
competition Competition; // Competition
brain Brain; // Brain
controller Controller1 = controller(); // Controller
motor TopLeft = motor(PORT1, ratio18_1, true); // Top Left Drive Motor
motor BottomLeft = motor(PORT9, ratio6_1, true); // Bottom Left Drive Motor
motor TopRight = motor(PORT2, ratio18_1, false); // Top Right Drive Motor
motor BottomRight = motor(PORT8, ratio6_1, false); // Bottom Right Drive Motor
motor ExtraLeft = motor(PORT16, ratio18_1, true);
motor ExtraRight = motor(PORT17, ratio18_1, false);
motor SpinnySpin = motor(PORT4, ratio6_1, false); // Flywheel Motor
digital_out wingPistonA(Brain.ThreeWirePort.C); // Wing
digital_out wingPistonB(Brain.ThreeWirePort.B); // Wing

// Variables
bool spin = false;

// Driving Commands
void SpinFlywheel() {
  if (spin == true) {
    SpinnySpin.spin(forward);
  } else {
    SpinnySpin.stop();
  }
}

void WingsETC() {
    wingPistonA.set(0);
    wingPistonB.set(0);
}

// Autonomous Commands
void Stop() {
  TopRight.stop();
  TopLeft.stop();
  BottomRight.stop();
  BottomLeft.stop();
  ExtraLeft.stop();
  ExtraRight.stop();
}

void Right() {
  TopRight.spin(reverse);
  TopLeft.spin(forward);
  BottomRight.spin(reverse);
  BottomLeft.spin(forward);
  ExtraLeft.spin(forward);
  ExtraRight.spin(reverse);
}

void Left() {
  TopRight.spin(forward);
  TopLeft.spin(reverse);
  BottomRight.spin(forward);
  BottomLeft.spin(reverse);
  ExtraLeft.spin(reverse);
  ExtraRight.spin(forward);
}

void Forward() {
  TopRight.spin(forward);
  TopLeft.spin(forward);
  BottomRight.spin(forward);
  BottomLeft.spin(forward);
  ExtraLeft.spin(forward);
  ExtraRight.spin(forward);
}

void Reverse() {
  TopRight.spin(reverse);
  TopLeft.spin(reverse);
  BottomRight.spin(reverse);
  BottomLeft.spin(reverse);
  ExtraLeft.spin(reverse);
  ExtraRight.spin(reverse);
}

void MoveBiatch(double moveNumber) {
  TopRight.spinFor(moveNumber, rev, false);
  TopLeft.spinFor(moveNumber, rev, false);
  BottomRight.spinFor(moveNumber, rev, false);
  TopLeft.spinFor(moveNumber, rev, false);
  ExtraLeft.spinFor(moveNumber, rev, false);
  ExtraRight.spinFor(moveNumber, rev, true);
}

void TurnBiatch(double turnNumber) {
  TopRight.spinFor(-turnNumber, rev, false);
  BottomRight.spinFor(-turnNumber, rev, false);
  TopLeft.spinFor(turnNumber, rev, false);
  BottomRight.spinFor(turnNumber, rev, false);
  ExtraLeft.spinFor(turnNumber, rev, false);
  ExtraRight.spinFor(-turnNumber, rev, true);
}


// Vex Issued Setup (DIY)
void pre_auton(void) {
  TopLeft.setBrake(brake);
  TopRight.setBrake(brake);
  BottomLeft.setBrake(brake);
  BottomRight.setBrake(brake);
  ExtraRight.setBrake(brake);
  ExtraLeft.setBrake(brake);

  TopLeft.setVelocity(50, percent);
  TopRight.setVelocity(50, percent);
  BottomLeft.setVelocity(50, percent);
  BottomRight.setVelocity(50, percent);
  ExtraRight.setVelocity(50, percent);
  ExtraLeft.setVelocity(50, percent);
  SpinnySpin.setVelocity(100, percent);

  wingPistonA.set(1);
  wingPistonB.set(1);
}

// AUTON, WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo
void autonomous(void) {
  Forward();
  wait(.4, sec);
  Stop();
  Right();
  wait(.4, sec);                                                                                                 
  Stop();
  TopLeft.setVelocity(25, percent);
  TopRight.setVelocity(25, percent);
  BottomLeft.setVelocity(25, percent);
  BottomRight.setVelocity(25, percent);
  ExtraLeft.setVelocity(25, percent);
  ExtraRight.setVelocity(25, percent);
  Reverse();
  wait(1.5, sec);
  Stop();
  spin = true;
  SpinFlywheel();
  wait(45, sec);
  TopLeft.setVelocity(100, percent);
  TopRight.setVelocity(100, percent);
  BottomLeft.setVelocity(100, percent);
  BottomRight.setVelocity(100, percent);
  ExtraLeft.setVelocity(100, percent);
  ExtraRight.setVelocity(100, percent);
  Right();
  wait(.65, sec);
  Stop();
  Forward();
  wait(2.6, sec);
  Stop();
  wait(.1, sec);
  Left();
  wait(.7, sec);
  Stop();
  Forward();
  wait(1, sec);
  Stop();
  Right();
  wait(.8, sec);
  Stop();
  wait(.1, sec);
  wingPistonA.set(0);
  wingPistonB.set(0);
  Forward();
  wait(1.5, sec);
  Stop();
  wingPistonA.set(1);
  wingPistonB.set(1);
  Reverse();
  wait(1, sec);
  Stop();
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
