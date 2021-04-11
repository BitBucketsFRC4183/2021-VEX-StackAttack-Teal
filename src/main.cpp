// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
//[Name]              [Type]       [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10           
// ClawMotor            motor         2               
// Vision3              vision        3               
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   Module:       main.cpp                                                  */
/*   Author:       C:\Users\Sajo                                             */
/*   Created:      Wed Mar 10 2021                                           */
/*   Description:  V5 project                                                */
/*                                                                           */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <iostream>
using namespace vex;
using namespace std;

competition Competition;

controller::axis turnAxis()
{
  return Controller1.Axis1;
}
controller::axis driveAxis()
{
  return Controller1.Axis3;
}

controller::button openClaw()
{
  return Controller1.ButtonL1;
}
controller::button closeClaw()
{
  return Controller1.ButtonL2;
}

controller::button liftArm()
{
  return Controller1.ButtonR1;
}
controller::button dropArm()
{
  return Controller1.ButtonR2;
}

controller::button spinIntake()
{
  return Controller1.ButtonA;
}
controller::button spinOuttake()
{
  return Controller1.ButtonY;
}

void setDriveVel(int vel)
{
  int realVel = abs(vel);

 	//Change the velocity to some value between the configured range
  int maxVel = 50;
  int minVel = 10;

 	// clamp realVel to between maxVel and minVel
  realVel = realVel > maxVel ? maxVel : (realVel < minVel ? minVel : realVel);

  Drivetrain.setDriveVelocity(realVel, percent);
}

void setTurnVel(int vel)
{
  int realVel = abs(vel);

 	//Change the velocity to some value between the configured range
  int maxVel = 30;
  int minVel = 1;

  realVel = realVel > maxVel ? maxVel : (realVel < minVel ? minVel : realVel);

  Drivetrain.setTurnVelocity(realVel, percent);
}

int moveDrivetrainTask()
{
  while (true)
  {
    int drivePos = driveAxis().position();
    int turnPos = turnAxis().position();

    setDriveVel(drivePos);
    setTurnVel(turnPos);

    if (drivePos == 0 && turnPos == 0)
    {
      Drivetrain.stop();
    }

   	/// driving
    if (drivePos > 0)
    {
      Drivetrain.drive(vex::forward);
    }
    else if (drivePos < 0)
    {
      Drivetrain.drive(vex::reverse);
    }
    else
    {
      Drivetrain.setDriveVelocity(0, percent);
    }

   	/// turning
    if (turnPos > 0)
    {
      Drivetrain.turn(vex::right);
    }
    else if (turnPos < 0)
    {
      Drivetrain.turn(vex::left);
    }
    else
    {
      Drivetrain.setTurnVelocity(0, percent);
    }

    wait(0.5, seconds);
  }
  return 0;
}

int moveClawTask()
{
  while (true)
  {
    if (openClaw().pressing())
    {
      ClawMotor.spin(vex::forward);
    }
    else if (closeClaw().pressing())
    {
      ClawMotor.spin(vex::reverse);
    }
    else
    {
      ClawMotor.stop();
    }

    wait(0.5, seconds);
  }
  return 0;
}

int moveArmTask()
{
  while (true)
  {
    if (liftArm().pressing())
    {
      ArmMotor.spin(vex::forward);
      SecondArmMotor.spin(vex::forward);
    }
    else if (dropArm().pressing())
    {
      ArmMotor.spin(vex::reverse);
      SecondArmMotor.spin(vex::reverse);
    }
    else
    {
      ArmMotor.stop();
      SecondArmMotor.stop();
    }

    wait(0.5, seconds);
  }
  return 0;
}

int intakeOuttakeWheelTask()
{
 	// motor 2 is reversed in the config, so they spin in the same direction here
  while (true)
  {
    if (spinIntake().pressing())
    {
      IntakeWheel1Motor.spin(vex::forward);
      IntakeWheel2Motor.spin(vex::forward);
    }
    else if (spinOuttake().pressing())
    {
      IntakeWheel1Motor.spin(vex::reverse);
      IntakeWheel2Motor.spin(vex::reverse);
    }
    else
    {
      IntakeWheel1Motor.stop();
      IntakeWheel2Motor.stop();
    }
  }
}

/////////////////

bool isGreenCube()
{
  Vision3.takeSnapshot(Vision3__SIG_3);
  bool isGreen = Vision3.objects[0].exists;
  return isGreen;
}

////////////////
void teleopMode()
{
  task drivetrainTask = task(moveDrivetrainTask);
  task clawTask = task(moveClawTask);
  task armTask = task(moveArmTask);
  task intakeOuttakeTask = task(intakeOuttakeWheelTask);

 	// wait indefinitely
  waitUntil(false);
}

void intakeAutoCube()
{
  int currentSpikeCutoff = 10;

  IntakeWheel1Motor.spin(vex::reverse);
  IntakeWheel2Motor.spin(vex::reverse);

  int mCurrent = IntakeWheel1Motor.current();

  while (true)
  {
    int newMCurrent = IntakeWheel1Motor.current();
    if (newMCurrent >= mCurrent + currentSpikeCutoff)
    {
      IntakeWheel1Motor.spinFor(vex::reverse, 3, seconds); // waitForCompletion = false?
      IntakeWheel2Motor.spinFor(vex::reverse, 3, seconds); // waitForCompletion = false?

      return;
    }
    else
    {
      mCurrent = newMCurrent;
    }
  }
}

void autoMode()
{
  setDriveVel(50);
  setTurnVel(50);

 	////////////////// take out recycling	//////////////////
 	Drivetrain.driveFor(26, inches);
 	// outtake
  IntakeWheel1Motor.spin(vex::reverse);
  IntakeWheel2Motor.spin(vex::reverse);

  // wait for cube to outtkae
  wait(1, seconds);
  
  // backup to not hit cube and then stop motors
  Drivetrain.driveFor(reverse, 2, inches);
  IntakeWheel1Motor.stop();
  IntakeWheel2Motor.stop();

 	////////////////// walk the dog	//////////////////
 	// setup
  Drivetrain.turnFor(vex::right, 70, degrees);
  Drivetrain.driveFor(40, inches);

  // TEMP DRIVE TO HOME
  Drivetrain.turnFor(vex::right, 40, degrees);
  Drivetrain.driveFor(35, inches);

  return;

 	// // cross
  // Drivetrain.turnFor(vex::right, 30, degrees);
  // Drivetrain.driveFor(30, inches);
 	// // recover; turn left towards green and orange cube
  // Drivetrain.turnFor(vex::right, 30, degrees);

 	// ////////////////// set the table	//////////////////
 	// // setup 
  // Drivetrain.driveFor(20, inches);
  // // bottom cube first
  // Drivetrain.turnFor(vex::left, 65, degrees);
  // Drivetrain.driveFor(12, inches);

  
  // if (true) //isGreenCube()
  // {
  //   // push it off 
  //   IntakeWheel1Motor.spin(vex::reverse);
  //   IntakeWheel2Motor.spin(vex::reverse);
  //   Drivetrain.driveFor(11, inches);
  //   IntakeWheel1Motor.stop();
  //   IntakeWheel2Motor.stop();
  //   // backup
  //   Drivetrain.driveFor(reverse, 18, inches);
  //   // then go back to home
  //   Drivetrain.turnFor(vex::right, 150, degrees);
  //   Drivetrain.driveFor(32.5, inches);
  // }
  // else
  // {
  //  	// back up and go to top cube
  //   Drivetrain.driveFor(vex::reverse, 5, inches);
  //   Drivetrain.turnFor(vex::right, 90, degrees);
  //   Drivetrain.driveFor(6, inches);
  //   Drivetrain.turnFor(vex::left, 90, degrees);
  //  	// intake then go back to home
  //   Drivetrain.driveFor(2.5, inches);
  //   intakeAutoCube();
  //   Drivetrain.driveFor(vex::reverse, 5, inches);
  //   Drivetrain.turnFor(vex::right, 90, degrees);
  //   Drivetrain.driveFor(13, inches);
  // }
}

int debugStuff()
{
  while (true)
  {
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

   	// cout << "is there a green cube:";
   	// cout << isGreenCube() << endl;

    wait(0.5, seconds);
  }
  return 0;
}

int main()
{
 	// Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  ClawMotor.setVelocity(50, percent);
  ArmMotor.setVelocity(50, percent);
  SecondArmMotor.setVelocity(50, percent);
  IntakeWheel1Motor.setVelocity(50, percent);
  IntakeWheel2Motor.setVelocity(50, percent);

  Drivetrain.setStopping(brake);
  ClawMotor.setStopping(hold);
  ArmMotor.setStopping(hold);
  SecondArmMotor.setStopping(hold);
  IntakeWheel1Motor.setStopping(hold);
  IntakeWheel2Motor.setStopping(hold);

  task debugTask = task(debugStuff);

 	autoMode();
  // teleopMode();

 	// Competition.autonomous(autoMode);
 	// Competition.drivercontrol(teleopMode);

  return 0;
}