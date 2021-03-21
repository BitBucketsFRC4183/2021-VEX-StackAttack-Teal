// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10           
// ClawMotor            motor         2               
// Vision3              vision        3               
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
#include <iostream>

using namespace vex;
using namespace std;

competition Competition;

controller::axis turnAxis() {return Controller1.Axis1;}
controller::axis driveAxis() {return Controller1.Axis2;}

controller::button openClaw() {return Controller1.ButtonL1;}
controller::button closeClaw() {return Controller1.ButtonL2;}

controller::button liftArm() {return Controller1.ButtonR1;}
controller::button dropArm() {return Controller1.ButtonR2;}



void driveRobot() {
  cout << "drive: ";
  cout << driveAxis().position() << endl;
  
  if (driveAxis().position() == 0) {
    Drivetrain.setDriveVelocity(0, percent);
  } else {
    Drivetrain.setDriveVelocity(50, percent);
  }

  if (driveAxis().position() > 0) {
    Drivetrain.drive(vex::forward);
  } else {
    Drivetrain.drive(vex::reverse);
  }

}

void turnRobot() {
  cout << "turn: ";
  cout << turnAxis().position() << endl;

  if (turnAxis().position() == 0) {
    Drivetrain.setTurnVelocity(0, percent);
  } else {
    Drivetrain.setTurnVelocity(50, percent);
  }

  if (turnAxis().position() > 0) {
    Drivetrain.turn(vex::right);
  } else {
    Drivetrain.turn(vex::left);
  }
}


void moveClaw() {
  if (openClaw().pressing()) {
    ClawMotor.spin(vex::forward);
  } else if (closeClaw().pressing()) {
    ClawMotor.spin(vex::reverse);
  } else {
    ClawMotor.stop();
  }
}

void moveArm() {
  if (liftArm().pressing()) {
    ArmMotor.spin(vex::forward);
  } else if (dropArm().pressing()) {
    ArmMotor.spin(vex::reverse);
  } else {
    ArmMotor.stop();
  }
}

/////////////////

bool isGreenCube() {
  Vision3.takeSnapshot(Vision3__SIG_3);
  bool isGreen = Vision3.objects[0].exists;
  return isGreen;
}

/////////////////

void teleopMode() {
  while (true) {
    driveRobot();
    turnRobot();

    moveClaw();
    moveArm();

    wait(0.5, seconds);

    // cout << isGreenCube() << endl;

    // turnAxis().changed(turnRobot);
    // driveAxis().changed(driveRobot);

    // openClaw().pressed(moveClaw);
    // openClaw().released(moveClaw);
    // closeClaw().pressed(moveClaw);
    // closeClaw().released(moveClaw);

    // liftArm().pressed(moveArm);
    // liftArm().released(moveArm);
    // dropArm().pressed(moveArm);
    // dropArm().released(moveArm);
  }
}

void autoMode() {
  // setDriveVelocity();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  ClawMotor.setVelocity(50, percent);
  ArmMotor.setVelocity(50, percent);

  Drivetrain.setStopping(brake);
  ClawMotor.setStopping(hold);
  ArmMotor.setStopping(hold);

  teleopMode();
  autoMode();

  // Competition.autonomous(autoMode);
  // Competition.drivercontrol(teleopMode);
  
  return 0;
}



