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

int debugStuff() {
  while (true) {
    cout << "drive: ";
    cout << driveAxis().position() << endl;

    cout << "turn: ";
    cout << turnAxis().position() << endl;

    cout << "velocity: ";
    cout << Drivetrain.velocity(percent);
    cout << "% and ";
    cout << Drivetrain.velocity(rpm);
    cout << "rpm" << endl;

    cout << "power: ";
    cout << Drivetrain.power() << endl;

    cout << "----" << endl;

    wait (0.5, seconds);
  }
  return 0;
}

void setDriveVel(int vel) {
  int realVel = abs(vel);

  //Change the velocity to some value between the configured range
  int maxVel = 90;
  int minVel = 10;

  realVel = realVel > maxVel ? maxVel : (realVel < minVel ? minVel : realVel);

  Drivetrain.setDriveVelocity(realVel, percent);
}

void setTurnVel(int vel) {
  int realVel = abs(vel);

  //Change the velocity to some value between the configured range
  int maxVel = 90;
  int minVel = 10;

  realVel = realVel > maxVel ? maxVel : (realVel < minVel ? minVel : realVel);

  Drivetrain.setTurnVelocity(realVel, percent);
}

int moveDrivetrainTask() {
  while (true) {
    int drivePos = driveAxis().position();
    int turnPos = turnAxis().position();

    setDriveVel(drivePos);
    setTurnVel(turnPos);

    if (drivePos == 0 && turnPos == 0) {
      Drivetrain.stop();
    }

    /// driving
    if (drivePos > 0) {
      Drivetrain.drive(vex::forward);
    } else if (drivePos < 0) {
      Drivetrain.drive(vex::reverse);
    } else {
      Drivetrain.setDriveVelocity(0, percent);
    }

    /// turning
    if (turnPos > 0) {
      Drivetrain.turn(vex::right);
    } else if (turnPos < 0) {
      Drivetrain.turn(vex::left);
    } else {
      Drivetrain.setTurnVelocity(0, percent);
    }

    wait(0.5, seconds);
  }
  return 0;
}

int moveClawTask() {
  while (true) {
    if (openClaw().pressing()) {
      ClawMotor.spin(vex::forward);
    } else if (closeClaw().pressing()) {
      ClawMotor.spin(vex::reverse);
    } else {
      ClawMotor.stop();
    }

    wait(0.5, seconds);
  }
  return 0;
}

int moveArmTask() {
  while (true) {
    if (liftArm().pressing()) {
      ArmMotor.spin(vex::forward);
    } else if (dropArm().pressing()) {
      ArmMotor.spin(vex::reverse);
    } else {
      ArmMotor.stop();
    }

    wait(0.5, seconds);
  }
  return 0;
}

/////////////////

bool isGreenCube() {
  Vision3.takeSnapshot(Vision3__SIG_3);
  bool isGreen = Vision3.objects[0].exists;
  return isGreen;
}


////////////////
void teleopMode() {
  task drivetrainTask = task(moveDrivetrainTask);
  task clawTask = task(moveClawTask);
  task armTask = task(moveArmTask);

  // wait indefinitely
  waitUntil(false);

  // while (true) {
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
  // }
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

  task debugTask = task(debugStuff);

  autoMode();
  teleopMode();

  // Competition.autonomous(autoMode);
  // Competition.drivercontrol(teleopMode);
  
  return 0;
}



