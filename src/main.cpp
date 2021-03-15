// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10           
// ClawMotor            motor         2               
// ArmMotor             motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sajo                                             */
/*    Created:      Wed Mar 10 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

vex::controller::button openClaw = Controller1.ButtonL1;
vex::controller::button closeClaw = Controller1.ButtonL2;

vex::controller::button liftArm = Controller1.ButtonR1;
vex::controller::button dropArm = Controller1.ButtonR2;

void turnRobot() {
  if (Controller1.Axis1.position(percent) == 0) {
    Drivetrain.setTurnVelocity(0, percent);
  }

  if (Controller1.Axis1.position(percent) > 0) {
    Drivetrain.turn(right);
  } else {
    Drivetrain.turn(left);
  }
}

void driveRobot() {

  if (Controller1.Axis2.position(percent) == 0) {
    Drivetrain.stop();
  }

  if (Controller1.Axis2.position(percent) > 0) {
    Drivetrain.drive(forward);
  } else {
    Drivetrain.drive(reverse);
  }

}

void moveClaw() {
  if (openClaw.pressing()) {
    ClawMotor.spin(forward);
  } else if (closeClaw.pressing()) {
    ClawMotor.spin(reverse);
  } else {
    ClawMotor.stop();
  }
  
}

void moveArm() {
  if (liftArm.pressing()) {
    ArmMotor.spin(forward);
  } else if (dropArm.pressing()) {
    ArmMotor.spin(reverse);
  } else {
    ArmMotor.stop();
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Drivetrain.setDriveVelocity(50, percent);
  ClawMotor.setVelocity(50, percent);
  ArmMotor.setVelocity(50, percent);

  Drivetrain.setStopping(brake);
  ClawMotor.setStopping(hold);
  ArmMotor.setStopping(hold);

  Controller1.Axis1.changed(turnRobot);
  Controller1.Axis2.changed(driveRobot);

  openClaw.pressed(moveClaw);
  openClaw.released(moveClaw);
  closeClaw.pressed(moveClaw);
  closeClaw.released(moveClaw);

  liftArm.pressed(moveArm);
  liftArm.released(moveArm);
  dropArm.pressed(moveArm);
  dropArm.released(moveArm);

}


